#include "chatbot.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QScrollBar>
#include <QProcessEnvironment>

ChatbotDialog::ChatbotDialog(QWidget *parent)
    : QDialog(parent), manager(new QNetworkAccessManager(this))
{
    setWindowTitle("Chatbot");
    setMinimumSize(500, 400);

    chatView = new QTextEdit(this);
    chatView->setReadOnly(true);

    input = new QLineEdit(this);
    input->setPlaceholderText("Ecrivez votre message ici...");

    sendBtn = new QPushButton("Envoyer", this);
    clearBtn = new QPushButton("Effacer", this);

    connect(sendBtn, &QPushButton::clicked, this, &ChatbotDialog::onSendClicked);
    connect(clearBtn, &QPushButton::clicked, this, &ChatbotDialog::onClearClicked);
    connect(manager, &QNetworkAccessManager::finished, this, &ChatbotDialog::onNetworkReplyFinished);

    QHBoxLayout *controls = new QHBoxLayout;
    controls->addWidget(input);
    controls->addWidget(sendBtn);
    controls->addWidget(clearBtn);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chatView);
    layout->addLayout(controls);

    // Minimal greeting
    appendChatMessage("Bot", "Bonjour — je suis le chatbot. Posez une question (Cohere API).\n(Assurez-vous de configurer COHERE_API_KEY en variable d'environnement.)");
}

QString ChatbotDialog::cohereApiKey() const
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    // Read the key from the COHERE_API_KEY environment variable
    return env.value("Lq5tWwCzYa5WsQsKIVJIJgpfq7U13MjkNJ8sx1Ji");
}

void ChatbotDialog::appendChatMessage(const QString &who, const QString &text)
{
    chatView->append(QString("<b>%1:</b> %2").arg(who.toHtmlEscaped(), text.toHtmlEscaped()));
    QScrollBar *s = chatView->verticalScrollBar();
    if (s) s->setValue(s->maximum());
}

void ChatbotDialog::onClearClicked()
{
    chatView->clear();
}

void ChatbotDialog::onSendClicked()
{
    QString message = input->text().trimmed();
    if (message.isEmpty()) return;

    QString key = "Lq5tWwCzYa5WsQsKIVJIJgpfq7U13MjkNJ8sx1Ji";
    if (key.isEmpty()) {
        QMessageBox::warning(this, "API key manquante", "La variable d'environnement COHERE_API_KEY n'est pas définie. Définissez votre clé d'API Cohere avant d'utiliser le chatbot.");
        return;
    }

    // Append user message locally
    appendChatMessage("Vous", message);
    input->clear();
    sendBtn->setEnabled(false);

    // Use Cohere chat endpoint
    QUrl url("https://api.cohere.ai/v1/chat");
    QNetworkRequest req(url);
    req.setRawHeader("Authorization", QString("Bearer %1").arg(key).toUtf8());
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // Cohere prefers an explicit version header for some endpoints
    req.setRawHeader("Cohere-Version", "2022-12-06");

        QJsonObject body;
        // Model selection: allow override with COHERE_MODEL env var; provide a sane default
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        QString model = env.value("COHERE_MODEL");
        if (model.isEmpty()) {
            // Prefer a default that exists for most accounts; change this if your account uses another model
            model = QStringLiteral("command-a-03-2025");
        }
        body["model"] = model;
        // remember model so error handling can offer helpful suggestions
        lastModelUsed = model;
    body["message"] = message;
    body["max_tokens"] = 150;
    body["temperature"] = 0.6;

    QJsonDocument doc(body);
    QByteArray payload = doc.toJson();

    manager->post(req, payload);

    // Show a small waiting hint
    appendChatMessage("Bot", "Réponse en cours... (Cohere)");
}

void ChatbotDialog::onNetworkReplyFinished(QNetworkReply *reply)
{
    sendBtn->setEnabled(true);
    if (!reply) return;

    QByteArray data = reply->readAll();
    reply->deleteLater();

    QVariant statusAttr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    int statusCode = statusAttr.isValid() ? statusAttr.toInt() : -1;

    // If HTTP status indicates error (>=400) treat as network/server error
    if (statusCode >= 400) {
        QString bodyStr = QString::fromUtf8(data).trimmed();
        QString errMsg = QString("Erreur HTTP %1").arg(statusCode);
        // extract server message if any
        QJsonParseError se;
        QJsonDocument ser = QJsonDocument::fromJson(bodyStr.toUtf8(), &se);
        if (se.error == QJsonParseError::NoError && ser.isObject()) {
            QJsonObject o = ser.object();
            if (o.contains("message")) {
                QString serverMsg = o.value("message").toString();
                errMsg += QString(": %1").arg(serverMsg);
                if (serverMsg.contains("model '") && serverMsg.contains("not found")) {
                    errMsg += QString("\nConseil: le modèle '%1' n'est pas disponible pour votre compte. Définissez la variable d'environnement COHERE_MODEL pour un modèle accessible (ex: command-a-03-2025, command-r7b-12-2024).\n").arg(lastModelUsed);
                }
            } else {
                errMsg += QString("\nCorps: %1").arg(bodyStr);
            }
        } else {
            if (!bodyStr.isEmpty()) errMsg += QString("\nCorps: %1").arg(bodyStr);
        }
        appendChatMessage("Bot", errMsg);
        return;
    }

    if (reply->error() != QNetworkReply::NoError) {
        // Show detailed error including any HTTP status and body returned by the server
        QVariant statusAttr = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        int statusCode = statusAttr.isValid() ? statusAttr.toInt() : -1;
        QString bodyStr = QString::fromUtf8(data).trimmed();
        QString errMsg = QString("Erreur réseau: %1").arg(reply->errorString());
        if (statusCode != -1) errMsg += QString(" (HTTP %1)").arg(statusCode);
        // parse server body if JSON and extract the message field for better UX
        if (!bodyStr.isEmpty()) {
            QJsonParseError se;
            QJsonDocument ser = QJsonDocument::fromJson(bodyStr.toUtf8(), &se);
            if (se.error == QJsonParseError::NoError && ser.isObject()) {
                QJsonObject o = ser.object();
                if (o.contains("message")) {
                    QString serverMsg = o.value("message").toString();
                    errMsg += QString("\nErreur serveur: %1").arg(serverMsg);
                    // if model was not found, provide a friendly hint
                    if (serverMsg.contains("model '") && serverMsg.contains("not found")) {
                        errMsg += QString("\n\nConseil: le modèle utilisé ('%1') n'a pas été trouvé par l'API. Vérifiez la variable d'environnement COHERE_MODEL ou essayez 'command-a-03-2025' ou 'command-r7b-12-2024'.").arg(lastModelUsed);
                    }
                } else {
                    errMsg += QString("\nCorps du serveur: %1").arg(bodyStr);
                }
            } else {
                errMsg += QString("\nCorps du serveur: %1").arg(bodyStr);
            }
        }
        appendChatMessage("Bot", errMsg);
        return;
    }

    QJsonParseError parseError;
    QJsonDocument responseDoc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        appendChatMessage("Bot", QString("Réponse invalide: %1").arg(parseError.errorString()));
        return;
    }

    if (!responseDoc.isObject()) {
        appendChatMessage("Bot", "Réponse inattendue du serveur (format non-objet)");
        return;
    }

    QJsonObject obj = responseDoc.object();

    // Cohere responses can come in several forms depending on endpoint:
    // - 'generations' array (generate endpoint)
    // - 'message' object with 'content' array (chat endpoint)
    if (obj.contains("generations") && obj.value("generations").isArray()) {
        QJsonArray gens = obj.value("generations").toArray();
        if (!gens.isEmpty() && gens[0].isObject()) {
            QString text = gens[0].toObject().value("text").toString();
            // Remove the temporary 'Réponse en cours...' last bot message before adding final
            // We can't easily remove specific lines, so we simply append final response
            appendChatMessage("Bot", text.trimmed());
            return;
        }
    }

    // Chat endpoint returns 'message' -> { content: [ { type: 'text', text: '...' } ] }
    if (obj.contains("message") && obj.value("message").isObject()) {
        QJsonObject msg = obj.value("message").toObject();
        if (msg.contains("content") && msg.value("content").isArray()) {
            QJsonArray contents = msg.value("content").toArray();
            for (const QJsonValue &c : contents) {
                if (c.isObject()) {
                    QJsonObject co = c.toObject();
                    if (co.contains("text")) {
                        QString text = co.value("text").toString();
                        appendChatMessage("Bot", text.trimmed());
                        return;
                    }
                } else if (c.isString()) {
                    appendChatMessage("Bot", c.toString().trimmed());
                    return;
                }
            }
        }
    }

    // Fallback: try to read generic `text` field
    if (obj.contains("text")) {
        appendChatMessage("Bot", obj.value("text").toString().trimmed());
        return;
    }

    appendChatMessage("Bot", "Aucune réponse utile reçue.");
}

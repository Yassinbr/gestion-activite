#ifndef CHATBOT_H
#define CHATBOT_H

#include <QDialog>

class QTextEdit;
class QLineEdit;
class QPushButton;
class QNetworkAccessManager;
class QNetworkReply;

class ChatbotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatbotDialog(QWidget *parent = nullptr);

private slots:
    void onSendClicked();
    void onClearClicked();
    void onNetworkReplyFinished(QNetworkReply *reply);

private:
    QTextEdit *chatView;
    QLineEdit *input;
    QPushButton *sendBtn;
    QPushButton *clearBtn;
    QNetworkAccessManager *manager;

    // keep the last model used so we can show helpful errors if the server rejects it
    QString lastModelUsed;

    QString cohereApiKey() const;
    void appendChatMessage(const QString &who, const QString &text);
};

#endif // CHATBOT_H

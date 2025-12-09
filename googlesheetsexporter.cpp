#include "googlesheetsexporter.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QInputDialog>
#include <QDesktopServices>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QSettings>
#include <QDateTime>
#include <QApplication>
#include <QClipboard>
#include <QDebug>

GoogleSheetsExporter::GoogleSheetsExporter(QObject *parent)
    : QObject(parent)
    , networkManager(new QNetworkAccessManager(this))
    , tableWidgetSource(nullptr)
    , clientId("YOUR_CLIENT_ID")  // À remplacer par votre Client ID Google
    , clientSecret("YOUR_CLIENT_SECRET")  // À remplacer par votre Client Secret
    , redirectUri("urn:ietf:wg:oauth:2.0:oob")
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &GoogleSheetsExporter::onReponseReseau);
}

GoogleSheetsExporter::~GoogleSheetsExporter()
{
}

void GoogleSheetsExporter::exporterVersGoogleSheets(QTableWidget *tableWidget, const QString &spreadsheetId, const QString &sheetName)
{
    if (!tableWidget) {
        emit exportEchoue("TableWidget invalide");
        return;
    }

    if (tableWidget->rowCount() == 0) {
        emit exportEchoue("La table est vide. Aucune donnée à exporter.");
        return;
    }

    this->tableWidgetSource = tableWidget;
    this->spreadsheetId = spreadsheetId;
    this->sheetName = sheetName;

    // Vérifier si on a un token d'accès
    QString token = obtenirAccessToken();
    if (token.isEmpty()) {
        // Demander l'authentification
        demanderAuthentification();
    } else {
        this->accessToken = token;
        // Si pas de spreadsheet ID, en créer un nouveau
        if (spreadsheetId.isEmpty()) {
            creerSpreadsheet();
        } else {
            envoyerDonnees(spreadsheetId, sheetName);
        }
    }
}

void GoogleSheetsExporter::demanderAuthentification()
{
    // Pour simplifier, on demande le token directement à l'utilisateur
    // Dans une vraie application, il faudrait implémenter le flux OAuth 2.0 complet
    
    bool ok;
    QString token = QInputDialog::getText(
        nullptr,
        "Authentification Google Sheets",
        "Pour exporter vers Google Sheets, vous devez obtenir un token d'accès.\n\n"
        "1. Allez sur https://developers.google.com/oauthplayground/\n"
        "2. Sélectionnez 'Google Sheets API v4'\n"
        "3. Autorisez et copiez le 'Access token'\n"
        "4. Collez-le ici :\n\n"
        "Token d'accès:",
        QLineEdit::Normal,
        "",
        &ok
    );

    if (ok && !token.isEmpty()) {
        this->accessToken = token;
        // Sauvegarder le token (dans un fichier ou settings)
        QSettings settings;
        settings.setValue("google_sheets_access_token", token);
        
        if (spreadsheetId.isEmpty()) {
            creerSpreadsheet();
        } else {
            envoyerDonnees(spreadsheetId, sheetName);
        }
    } else {
        emit exportEchoue("Authentification annulée");
    }
}

void GoogleSheetsExporter::creerSpreadsheet()
{
    QJsonObject spreadsheet;
    QJsonObject properties;
    properties["title"] = "Fournisseurs - " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    
    QJsonObject sheet;
    QJsonObject sheetProperties;
    sheetProperties["title"] = sheetName;
    sheet["properties"] = sheetProperties;
    
    QJsonArray sheets;
    sheets.append(sheet);
    
    QJsonObject spreadsheetProperties;
    spreadsheetProperties["properties"] = properties;
    spreadsheetProperties["sheets"] = sheets;
    
    spreadsheet["properties"] = properties;
    spreadsheet["sheets"] = sheets;

    QJsonDocument doc(spreadsheet);
    QByteArray data = doc.toJson();

    QUrl requestUrl("https://sheets.googleapis.com/v4/spreadsheets");
    QNetworkRequest networkRequest;
    networkRequest.setUrl(requestUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkRequest.setRawHeader("Authorization", ("Bearer " + accessToken).toUtf8());

    QNetworkReply *reply = networkManager->post(networkRequest, data);
    Q_UNUSED(reply);
}

void GoogleSheetsExporter::envoyerDonnees(const QString &spreadsheetId, const QString &sheetName)
{
    if (spreadsheetId.isEmpty()) {
        emit exportEchoue("ID de spreadsheet invalide");
        return;
    }

    // Convertir le QTableWidget en JSON
    QJsonArray donnees = convertirTableWidgetEnJson(tableWidgetSource);

    // Créer la requête pour ajouter les valeurs (append)
    QString range = QUrl::toPercentEncoding(sheetName) + "!A1";
    QString url = QString("https://sheets.googleapis.com/v4/spreadsheets/%1/values/%2:append?valueInputOption=RAW&insertDataOption=OVERWRITE")
                  .arg(spreadsheetId)
                  .arg(range);

    QJsonObject requestBody;
    requestBody["values"] = donnees;
    requestBody["majorDimension"] = "ROWS";

    QJsonDocument doc(requestBody);
    QByteArray data = doc.toJson();

    QUrl requestUrl(url);
    QNetworkRequest networkRequest;
    networkRequest.setUrl(requestUrl);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    networkRequest.setRawHeader("Authorization", ("Bearer " + accessToken).toUtf8());

    QNetworkReply *reply = networkManager->post(networkRequest, data);
    Q_UNUSED(reply);
}

QJsonArray GoogleSheetsExporter::convertirTableWidgetEnJson(QTableWidget *tableWidget)
{
    QJsonArray lignes;

    // En-têtes
    QJsonArray enTetes;
    for (int col = 0; col < tableWidget->columnCount(); ++col) {
        QTableWidgetItem *header = tableWidget->horizontalHeaderItem(col);
        if (header) {
            enTetes.append(header->text());
        } else {
            enTetes.append(QString("Colonne %1").arg(col + 1));
        }
    }
    lignes.append(enTetes);

    // Données
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        QJsonArray ligne;
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            if (item) {
                ligne.append(item->text());
            } else {
                ligne.append("");
            }
        }
        lignes.append(ligne);
    }

    return lignes;
}

QString GoogleSheetsExporter::obtenirAccessToken()
{
    QSettings settings;
    return settings.value("google_sheets_access_token", "").toString();
}

void GoogleSheetsExporter::onReponseReseau(QNetworkReply *reply)
{
    if (!reply) {
        return;
    }

    QByteArray data = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();

    if (reply->error() != QNetworkReply::NoError) {
        QString erreur = QString("Erreur réseau: %1\n%2")
                        .arg(reply->errorString())
                        .arg(QString::fromUtf8(data));
        emit exportEchoue(erreur);
        reply->deleteLater();
        return;
    }

    // Si c'est une création de spreadsheet
    if (reply->url().toString().contains("/v4/spreadsheets") && !reply->url().toString().contains("/values")) {
        if (json.contains("spreadsheetId")) {
            QString newSpreadsheetId = json["spreadsheetId"].toString();
            this->spreadsheetId = newSpreadsheetId;
            
            // Copier l'URL dans le presse-papiers dès la création
            QString url = QString("https://docs.google.com/spreadsheets/d/%1").arg(newSpreadsheetId);
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(url);
            
            // Maintenant envoyer les données
            envoyerDonnees(newSpreadsheetId, sheetName);
        } else {
            emit exportEchoue("Impossible de créer le spreadsheet");
        }
    }
    // Si c'est un ajout de valeurs
    else if (reply->url().toString().contains("/values")) {
        if (json.contains("updates") || json.contains("spreadsheetId")) {
            QString url = QString("https://docs.google.com/spreadsheets/d/%1").arg(spreadsheetId);
            QString message = QString("✅ Données exportées avec succès vers Google Sheets!\n\n"
                                     "📊 Spreadsheet ID: %1\n"
                                     "🔗 URL: %2\n\n"
                                     "✂️ L'URL a été copiée dans le presse-papiers!\n"
                                     "Vous pouvez maintenant coller (Ctrl+V) l'URL dans votre navigateur.")
                             .arg(spreadsheetId)
                             .arg(url);
            
            // Copier l'URL dans le presse-papiers
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(url);
            
            emit exportReussi(message);
        } else {
            // Vérifier si c'est une erreur dans la réponse
            if (json.contains("error")) {
                QJsonObject error = json["error"].toObject();
                QString errorMsg = error["message"].toString();
                emit exportEchoue("Erreur Google Sheets: " + errorMsg);
            } else {
                emit exportEchoue("Impossible d'ajouter les données au spreadsheet. Réponse: " + QString::fromUtf8(data));
            }
        }
    }

    reply->deleteLater();
}


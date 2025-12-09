#ifndef GOOGLESHEETSEXPORTER_H
#define GOOGLESHEETSEXPORTER_H

#include <QObject>
#include <QString>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
class QTableWidget;
class QNetworkAccessManager;
class QJsonArray;
QT_END_NAMESPACE

class GoogleSheetsExporter : public QObject
{
    Q_OBJECT

public:
    explicit GoogleSheetsExporter(QObject *parent = nullptr);
    ~GoogleSheetsExporter();

    // Exporter le QTableWidget vers Google Sheets
    void exporterVersGoogleSheets(QTableWidget *tableWidget, const QString &spreadsheetId = "", const QString &sheetName = "Fournisseurs");

signals:
    void exportReussi(const QString &message);
    void exportEchoue(const QString &erreur);
    void authentificationRequise(const QString &url);

private slots:
    void onReponseReseau(QNetworkReply *reply);

private:
    void demanderAuthentification();
    void creerSpreadsheet();
    void envoyerDonnees(const QString &spreadsheetId, const QString &sheetName);
    QJsonArray convertirTableWidgetEnJson(QTableWidget *tableWidget);
    QString obtenirAccessToken(); // Pour stocker le token OAuth

    QNetworkAccessManager *networkManager;
    QTableWidget *tableWidgetSource;
    QString accessToken;
    QString spreadsheetId;
    QString sheetName;
    QString clientId;
    QString clientSecret;
    QString redirectUri;
};

#endif // GOOGLESHEETSEXPORTER_H

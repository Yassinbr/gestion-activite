#include "connection.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test = false;

    // ⚠️ IMPORTANT : Fermer d'abord toute connexion existante
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // Configuration selon votre source ODBC
    db.setDatabaseName("summerclub");  // Nom de votre source ODBC
    db.setUserName("gestion");               // Votre utilisateur Oracle
    db.setPassword("123");            // Votre mot de passe

    qDebug() << "🔌 Tentative de connexion à la source ODBC: Source_Projet2A";

    if (db.open()) {
        test = true;
        qDebug() << "✅ Connexion à Oracle réussie via ODBC!";
        qDebug() << "Driver:" << db.driverName();
        qDebug() << "Base de données:" << db.databaseName();

        // Tester immédiatement la connexion
        if (testerRequete()) {
            qDebug() << "✅ Test de requête réussi!";
        }
    } else {
        QString error = db.lastError().text();
        qDebug() << "❌ Erreur de connexion ODBC:" << error;

        QMessageBox::critical(nullptr, "Erreur Connexion ODBC",
                              "Impossible de se connecter via ODBC:\n" + error +
                                  "\n\nVérifiez que:\n" +
                                  "- La source ODBC 'Source_Projet2A' existe\n" +
                                  "- Oracle XE est démarré\n" +
                                  "- Le service OracleServiceXE est en cours");
    }

    return test;
}

bool Connection::testerRequete()
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qDebug() << "❌ Base non ouverte pour le test";
        return false;
    }

    QSqlQuery query;

    // ⚠️ IMPORTANT : Configurer la requête pour éviter les erreurs de séquence
    query.setForwardOnly(true);

    if (query.exec("SELECT 1 FROM DUAL")) {
        if (query.next()) {
            qDebug() << "✅ Requête TEST réussie - Oracle répond!";
            return true;
        }
    } else {
        QString error = query.lastError().text();
        qDebug() << "❌ Erreur requête TEST:" << error;
        qDebug() << "Détails Oracle:" << query.lastError().databaseText();
    }

    return false;
}

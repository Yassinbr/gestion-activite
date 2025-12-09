#include "connection.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection() {}

bool Connection::createconnect()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");   // Ton DSN Oracle ODBC
    db.setUserName("Yassin");                // Ton utilisateur Oracle
    db.setPassword("0000");                  // Ton mot de passe Oracle

    if (db.open()) {
        qDebug() << "Connexion réussie à Oracle !";
        return true;
    } else {
        qDebug() << "Erreur connexion Oracle :" << db.lastError().text();
        return false;
    }
}

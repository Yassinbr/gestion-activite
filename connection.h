#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

class Connection
{
public:
    Connection();
    bool createconnect();
    bool testerRequete();
};

#endif // CONNECTION_H

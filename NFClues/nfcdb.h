#ifndef NFCDB_H
#define NFCDB_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QtSql>
//Class used to pass the DB object around in the application
class NfcDb
{
public:
    NfcDb();
    QSqlDatabase getDB();
private:
    QSqlDatabase l_db;
};

#endif // NFCDB_H

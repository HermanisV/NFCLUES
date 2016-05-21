#include "nfcdb.h"

NfcDb::NfcDb()
{

}
//On initial call will create the databse connection,
//On rest of the calls will return the created on.
QSqlDatabase NfcDb::getDB()
{
    qDebug() << "In getDB";
    if (QSqlDatabase::contains("NFCLUESDB")) {
        qDebug() << "Connection allready created";
        l_db = QSqlDatabase::database("NFCLUESDB");
        l_db.setConnectOptions();
        if (l_db.isOpen()) l_db.close();
    }
    else{
        //Server and DB variables
        qDebug() << "Creating new connection";
        QString ServerName = "nfclues";
        QString DBName = "NFClues_DB";
        QString Login = "verhoher";
        QString Pass = "Vietejais3Brown";
        l_db = QSqlDatabase::addDatabase("QODBC3","NFCLUESDB");
        l_db.setConnectOptions();
        QString dsn = QString("Driver={SQL Server Native Client 11.0};Server=tcp:nfclues.database.windows.net,1433;Database=NFClues_DB;Uid=%1@nfclues;Pwd=%2;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;").arg(Login).arg(Pass);
        l_db.setDatabaseName(dsn);
    }
    return l_db;
}

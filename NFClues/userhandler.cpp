#include "userhandler.h"
#include "usermodel.h"
#include <QDebug>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QtCore>
#include <QtSql>
#include <QCryptographicHash>

UserHandler::UserHandler(QObject *parent) : QObject(parent)
{

}

int UserHandler::userId()
{
    return l_userId;
}

QString UserHandler::login()
{
    return l_login;
}

QString UserHandler::email()
{
    return l_email;
}

QString UserHandler::password()
{
    return l_password;
}

int UserHandler::points()
{
    return l_points;
}

int UserHandler::role()
{
    return l_role;
}

void UserHandler::setUserId(const int &userId)
{
    l_userId = userId;
}

void UserHandler::setLogin(const QString &login)
{
    l_login = login;
}

void UserHandler::setEmail(const QString &email)
{
    l_email = email;
}

void UserHandler::setPassword(const QString &password)
{
    l_password = password;
}

void UserHandler::setPoints(const int &points)
{
    l_points = points;
}

void UserHandler::setRole(const int &role)
{
    l_role = role;
}

void UserHandler::createNewUser()
{
    qDebug() << "In UserHandler.createNewUser";
    //Server and DB variables
    QString ServerName = "nfclues";
    QString DBName = "NFClues_DB";
    QString Login = "verhoher";
    QString Pass = "Vietejais3Brown";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3");

    db.setConnectOptions();
    QString dsn = QString("Driver={SQL Server Native Client 11.0};Server=tcp:nfclues.database.windows.net,1433;Database=NFClues_DB;Uid=%1@nfclues;Pwd=%2;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;").arg(Login).arg(Pass);
    db.setDatabaseName(dsn);
    if (db.open())
    {
      qDebug() << "DB connection opened.";
      QSqlQuery UserFetch;
      //Check for existing user under this email or login
      if (UserFetch.exec(QString("select * from users where login = %1 or email = %2").arg(l_login).arg(l_email)))
      {
          if (UserFetch.next())
          {
            qDebug() << "Email or Login is taken";
          }
          else
          {
            qDebug() << "No existing record found, inserting new";

            QString InsertQry = "insert into users values ((NEXT VALUE FOR user_seq),:login,:pass,:salt,:email,:points,:role,CURRENT_TIMESTAMP)";
            QSqlQuery NewUserInsert;
            NewUserInsert.prepare(InsertQry);
            NewUserInsert.bindValue(":login",l_login);
            NewUserInsert.bindValue(":pass",QString("%1").arg(QString(QCryptographicHash::hash(l_password.toUtf8(),QCryptographicHash::Sha1).toHex())));    //Method 2 - SHA-1 hash
            NewUserInsert.bindValue(":salt",123);   //Hash is not salted yet
            NewUserInsert.bindValue(":email",l_email);
            NewUserInsert.bindValue(":role",1);     //Role 1 is normal user

            if (NewUserInsert.exec())
            {
                qDebug() << "Inserted";
            }
            else
            {
              qDebug() << "Error happened - " << db.lastError().text();
            }
          }
      }
      else
      {

      }
      qDebug() << "Closing connection";
      db.close();
    }
    else
    {
      qDebug() << "Error happened - " << db.lastError().text();
    }
}

#include "userhandler.h"
#include <QDebug>
#include <QObject>
#include <QQuickItem>
#include <QString>
#include <QtCore>
#include <QtSql>
#include <QQmlContext>
#include <QErrorMessage>
#include <QCryptographicHash>

UserHandler::UserHandler(QObject *parent) : QObject(parent)
{
    connect(this,SIGNAL(gotError(QString)), this,SLOT(handleError(QString)));
    createDb();
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

QString UserHandler::errorString()
{
    return l_error;
}

void UserHandler::setUserId(const int &userId)
{
    if (l_userId == userId)
        return;
    l_userId = userId;
    emit userIdChanged();
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

    if (l_db.open())
    {
        qDebug() << "DB connection opened.";
        QSqlQuery UserFetch;
        //Check for existing user under this email or login
        QString user_query = QString("select * from users where login = '%1' or email = '%2'").arg(l_login).arg(l_email);
        qDebug() << "Querry "<< user_query;
        if (UserFetch.exec(user_query))
        {
            if (UserFetch.next()) {
                qDebug() << "Login taken";
                l_db.close();
                gotError("Email or Login is taken");
            }
            else
            {
                qDebug() << "No existing record found, inserting new";
                QString InsertQry = QString("insert into users values ((NEXT VALUE FOR user_seq),'%1',HASHBYTES( 'MD5','%2'),123,'%3',0,1,CURRENT_TIMESTAMP)").arg(l_login).arg(l_password).arg(l_email);
                QSqlQuery NewUserInsert;
                if (NewUserInsert.exec(InsertQry))
                {
                    qDebug() << "Inserted";
                    l_db.close();
                    if (getUserData(l_login))
                    {
                    qDebug() << "Got Logon data";
                    emit gotLogin();
                    qDebug() << "Back from loginUser";
                    return;
                    }
                }
                else
                {
                    qDebug() << "Error happened - " << l_db.lastError().text();
                    qDebug() << "Closing connection";
                    l_db.close();
                    gotError("Ooops, there seems to be a problem");
                }
            }
        }
        else
        {
            qDebug() << "Error happened - " << l_db.lastError().text();
            qDebug() << "Closing connection";
            l_db.close();
            gotError("Ooops, there seems to be a problem");
        }
    }
    else
    {
        qDebug() << "Error happened - " << l_db.lastError().text();
        qDebug() << "Closing connection";
        l_db.close();
        gotError("Ooops, there seems to be a problem");
    }
}

void UserHandler::loginUser(QString p_login, QString p_pass)
{
    qDebug() << "In UserHandler.loginUser";
    if (l_db.open())
    {
        qDebug() << "l_db connection opened.";
        QSqlQuery UserFetch;
        //Check for existing user under this login pass combination
        QString user_query = QString("select * from users where login = '%1' and PasswordHash = HASHBYTES( 'MD5','%2')").arg(p_login).arg(p_pass);
        if (UserFetch.exec(user_query))
        {
            if (UserFetch.next()) {
                qDebug() << "Login user found";
                qDebug() << "Password match";
                l_db.close();
                if (getUserData(p_login))
                {
                qDebug() << "Got Logon data";
                emit gotLogin();
                qDebug() << "Back from loginUser";
                return;
                }
            }
            //                }
            else
            {//PW don't match
                qDebug() << "Login and pass combination is incorrect";
                qDebug() << "Closing connection";
                l_db.close();
                gotError("Wrong login");
            }
        }
        else
        {
            qDebug() << "Error happened - " << l_db.lastError().text();
            qDebug() << "Closing connection";
            l_db.close();
            gotError("Ooops, there seems to be a problem");
        }
    }
    else
    {
        qDebug() << "Error happened - " << l_db.lastError().text();
        qDebug() << "Closing connection";
        l_db.close();
        gotError("Ooops, there seems to be a problem");
    }
}

bool UserHandler::getUserData(QString p_login)
{
    qDebug() << "In UserHandler.getUserData";
    if (l_db.open())
    {
        qDebug() << "DB connection opened.";
        QSqlQuery userFullFetch;
        //Fetch full user data by id
        QString user_query = QString("select * from users where login = '%1'").arg(p_login);
        qDebug() << "Querry "<< user_query;
        if (userFullFetch.exec(user_query))
        {
            if (userFullFetch.next()) {
                qDebug() << "User by id found";
                l_userId = userFullFetch.value(0).toInt();
                l_login  = userFullFetch.value(1).toString();
                l_email  = userFullFetch.value(4).toString();
                l_points = userFullFetch.value(5).toInt();
                l_role   = userFullFetch.value(6).toInt();

                qDebug() << "l_login "<< l_login;
                qDebug() << "l_userId "<< l_userId;
                qDebug() << "l_email "<< l_email;
                qDebug() << "l_points "<< l_points;
                qDebug() << "l_role "<< l_role;
                l_db.close();
                return true;
            }
            else{
                qDebug() << "User under login "<< p_login<< " was not found, or something went wrong";
                qDebug() << "Error happened - " << l_db.lastError().text();
                qDebug() << "Closing connection";
                l_db.close();
                gotError("Wrong login");
                return false;
            }
        }
        else
        {
            qDebug() << "Error happened - " << l_db.lastError().text();
            qDebug() << "Closing connection";
            l_db.close();
            gotError("Ooops, there seems to be a problem");
            return false;
        }
        return false;
    }
   return false;
}

    void UserHandler::handleError(QString p_error)
    {
        qDebug() << "Error happened";
        if (p_error == l_error)
        {
            return;
        }
        else
        {
            l_error = p_error;
            emit error();
        }
    }

    void UserHandler::createDb()
    {
        qDebug() << "In UserHandler.connectDb";
        //Server and DB variables
        QString ServerName = "nfclues";
        QString DBName = "NFClues_DB";
        QString Login = "verhoher";
        QString Pass = "Vietejais3Brown";
        l_db = QSqlDatabase::addDatabase("QODBC3");
        l_db.setConnectOptions();
        QString dsn = QString("Driver={SQL Server Native Client 11.0};Server=tcp:nfclues.database.windows.net,1433;Database=NFClues_DB;Uid=%1@nfclues;Pwd=%2;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;").arg(Login).arg(Pass);
        l_db.setDatabaseName(dsn);
    }

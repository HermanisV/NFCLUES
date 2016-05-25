#include "userhandler.h"
#include "leaderboarddata.h"
#include <QDebug>
#include <QObject>
#include <QString>
#include <QtSql>
#include <QErrorMessage>
#include <QtQml>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>
#include "qqml.h"
#include "nfcdb.h"
#include "main.cpp"

UserHandler::UserHandler(QObject *parent) : QObject(parent)
{
    connect(this,SIGNAL(gotError(QString)), this,SLOT(handleError(QString)));
    connect(this,SIGNAL(gotLogin()), this,SLOT(buildLeaderboard()));
    connect(this,SIGNAL(gotLogin()), this,SLOT(buildUsersAdventureTable()));
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

int UserHandler::place()
{
    return l_place;
}

QList<QObject *> UserHandler::leaderTable()
{
    return l_leaderTable;
}

QList<QObject *> UserHandler::usersAdventuresTable()
{
    return l_userAdventureTable;
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
    if (login == l_login)
    {
        return;
    }
    else
    {
        l_login = login;
    }
}

void UserHandler::setEmail(const QString &email)
{
    if (email == l_email)
    {
        return;
    }
    else
    {
        l_email = email;
    }
}

void UserHandler::setPassword(const QString &password)
{
    if (password == l_password)
    {
        return;
    }
    else
    {
        l_password = password;
    }
}

void UserHandler::setPoints(const int &points)
{
    if (points == l_points)
    {
        return;
    }
    else
    {
        l_points = points;
    }
}

void UserHandler::setRole(const int &role)
{
    if (role == l_role)
    {
        return;
    }
    else
    {
        l_role = role;
    }
}

void UserHandler::createNewUser()
{
    qDebug() << "In UserHandler.createNewUser";

    NfcDb DB;
    l_db = DB.getDB();
    if (l_db.open())
    {
        qDebug() << "DB connection opened.";
        QSqlQuery UserFetch(l_db);
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
                QSqlQuery NewUserInsert(l_db);
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
    NfcDb DB;
    l_db = DB.getDB();
    if (l_db.open())
    {
        qDebug() << "l_db connection opened.";
        QSqlQuery UserFetch(l_db);
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
    NfcDb DB;
    l_db = DB.getDB();
    if (l_db.open())
    {
        qDebug() << "DB connection opened.";
        QSqlQuery userFullFetch(l_db);
        //Fetch full user data by id
        QString user_query = QString("SELECT us.*, rowus.Place from users us,(SELECT ROW_NUMBER() OVER (ORDER BY points desc) AS Place, login,Points FROM users) rowus where rowus.Login = us.Login and   us.login = '%1'").arg(p_login);
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
                l_place  = userFullFetch.value(8).toInt();

                qDebug() << "l_login "<< l_login;
                qDebug() << "l_userId "<< l_userId;
                qDebug() << "l_email "<< l_email;
                qDebug() << "l_points "<< l_points;
                qDebug() << "l_role "<< l_role;
                qDebug() << "l_place "<< l_place;
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

void UserHandler::addAdventureToList(int p_adventureId, QString p_name, int p_award, int p_status, QString p_desc, QString p_clue)
{
    qDebug()<<"In UserHandler.addAdventureToList";
    l_userAdventureTable.append(new AdventureOnUserData(p_adventureId, p_name,p_award,p_status,p_desc,p_clue));
    emit usersAdventuresTableChanged();
}

//QVariant UserHandler::getAdventureRecord(int p_index)
//{
//    return QVariant::fromValue<AdventureOnUserData*>((l_userAdventureTable*)this->at(p_index));
//}
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

void UserHandler::buildLeaderboard()
{
    qDebug() << "In UserHandler.buildLeaderboard";
    NfcDb DB;
    l_db = DB.getDB();

    if (l_db.open())
    {
        qDebug() << "DB connection opened.";
        QSqlQuery leaderFetch(l_db);
        //Fetch data to be filled in  leaderboardData model
        QString leader_query = QString("SELECT rowus.place ,us.login,us.Points from users us,(SELECT ROW_NUMBER() OVER (ORDER BY points desc) AS place,login FROM users) rowus where rowus.Place < 101 and rowus.login = us.login order by rowus.Place asc, Points desc, login asc;");
        qDebug() << "Querry "<< leader_query;
        if (leaderFetch.exec(leader_query))
        {
            while (leaderFetch.next()) {
                l_leaderTable.append(new LeaderboardData(leaderFetch.value(0).toInt(), leaderFetch.value(1).toString(),leaderFetch.value(2).toInt()));
                 qDebug() << "Querry  got user: "<<leaderFetch.value(1).toString();
            }
            l_db.close();
        }
        else
        {
            qDebug() << "Error happened - " << l_db.lastError().text();
            qDebug() << "Closing connection";
            l_db.close();
            gotError("Ooops, there seems to be a problem");
        }
    }
    qDebug() << "Done fetching";
}

void UserHandler::buildUsersAdventureTable(int user_id)
{
    qDebug() << "In UserHandler.buildUsersAdventureTable";
    if (user_id == NULL) {
        user_id = l_userId;
    }
    NfcDb DB;
    l_db = DB.getDB();

    if (l_db.open())
    {
        qDebug() << "DB connection opened.";
        QSqlQuery adventureFetch(l_db);
        //Fetch data to be filled in  adventureOnUser model
        QString adventureQuery = QString("select Adventure_id,Name,Award,Status,Description,Clue from Adventures where Owner_id = %1;").arg(user_id);
        qDebug() << "Querry "<< adventureQuery;
        if (adventureFetch.exec(adventureQuery))
        {
            while (adventureFetch.next()) {
                l_userAdventureTable.append(new AdventureOnUserData(adventureFetch.value(0).toInt(), adventureFetch.value(1).toString(),adventureFetch.value(2).toInt(),adventureFetch.value(3).toInt(),adventureFetch.value(4).toString(),adventureFetch.value(5).toString()));
                 qDebug() << "Querry  got adventure: "<<adventureFetch.value(1).toString();
            }
            l_db.close();
        }
        else
        {
            qDebug() << "Error happened - " << l_db.lastError().text();
            qDebug() << "Closing connection";
            l_db.close();
            gotError("Ooops, there seems to be a problem");
        }
    }
    qDebug() << "Done fetching";
}

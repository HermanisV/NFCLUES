#include "adventurehandler.h"
#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QtDebug>
#include <QString>


AdventureHandler::AdventureHandler(QObject *parent) : QObject(parent)
{
    connect(this,SIGNAL(gotError(QString)), this,SLOT(handleError(QString)));
}

int AdventureHandler::adventureId()
{
    return l_adventureId;
}

int AdventureHandler::ownerId()
{
    return l_ownerId;
}

int AdventureHandler::tagId()
{
    return l_tagId;
}

QString AdventureHandler::name()
{
    return l_name;
}

QString AdventureHandler::desc()
{
    return l_desc;
}

QString AdventureHandler::clue()
{
    return l_clue;
}

int AdventureHandler::award()
{
    return l_award;
}

QString AdventureHandler::geoLat()
{
    return l_geoLat;
}

QString AdventureHandler::geoLong()
{
    return l_geoLong;
}

int AdventureHandler::status()
{
    return l_status;
}

void AdventureHandler::setAdventureId(const int &adventureId)
{
    if (adventureId == l_adventureId)
    {
        return;
    }
    else
    {
        l_adventureId = adventureId;
    }
}

void AdventureHandler::setOwnerId(const int &ownerId)
{
    if (ownerId == l_ownerId)
    {
        return;
    }
    else
    {
        l_ownerId = ownerId;
    }
}

void AdventureHandler::setTagId(const int &tagId)
{
    if (tagId == l_tagId)
    {
        return;
    }
    else
    {
        l_tagId = tagId;
    }

}

void AdventureHandler::setName(const QString &name)
{
    if (name == l_name)
    {
        return;
    }
    else
    {
        l_name = name;
    }
}

void AdventureHandler::setDesc(const QString &desc)
{
    if (desc == l_desc)
    {
        return;
    }
    else
    {
        l_desc = desc;
    }
}

void AdventureHandler::setClue(const QString &clue)
{
    if (clue == l_clue)
    {
        return;
    }
    else
    {
        l_clue = clue;
    }
}

void AdventureHandler::setAward(const int &award)
{
    if (award == l_award)
    {
        return;
    }
    else
    {
        l_award = award;
    }
}

void AdventureHandler::setGeoLat(const QString &geoLat)
{
    if (geoLat == l_geoLat)
    {
        return;
    }
    else
    {
        l_geoLat = geoLat;
    }
}

void AdventureHandler::setGeoLong(const QString &geoLong)
{
    if (geoLong == l_geoLong)
    {
        return;
    }
    else
    {
        l_geoLong = geoLong;
    }
}

void AdventureHandler::setStatus(const int &status)
{
    if (status == l_status)
    {
        return;
    }
    else
    {
        l_status = status;
    }
}

void AdventureHandler::createNewAdventure(const int ownerId)
{
    qDebug() << "In AdventureHandler.createNewAdventure";

    NfcDb DB;
    l_db = DB.getDB();
    if (l_db.open())
    {
        qDebug() << "DB connection opened.";
        QSqlQuery adventureFetch(l_db);
        //Check for existing user under this email or login
        QString adventureQuerry = QString("select ad.Adventure_id from adventures ad, Users us where ad.Name = '%1' and us.user_id = %2;").arg(l_name).arg(ownerId);
        qDebug() << "Querry "<< adventureQuerry;
        if (adventureFetch.exec(adventureQuerry))
        {
            if (adventureFetch.next()) {
                qDebug() << "Already an adventure with this name under this user";
                l_db.close();
                gotError("Sorry, you already have an adventure under this name");
            }
            else
            {
                qDebug() << "No existing record found, inserting new";
                //Get adventure_id for thios adventure and ctore it on this object
                QString advntSeqQuerry = "select (NEXT VALUE FOR adventure_seq) seq_no";
                if (adventureFetch.exec(advntSeqQuerry))
                {
                    if (adventureFetch.next()) {
                    setAdventureId(adventureFetch.value(0).toInt());
                    }
                }
                else
                {
                    qDebug() << "Error happened - " << l_db.lastError().text();
                    qDebug() << "Closing connection";
                    l_db.close();
                    gotError("Ooops, there seems to be a problem");
                }
                QString InsertQry = QString("insert into Adventures values (%1,%2,'','%3','%4','%5',%6,'','',1,CURRENT_TIMESTAMP);").arg(l_adventureId).arg(ownerId).arg(l_name).arg(l_desc).arg(l_clue).arg(l_award);
                qDebug() << "Insert: "<<InsertQry;
                QSqlQuery NewAdventureInsert(l_db);
                if (NewAdventureInsert.exec(InsertQry))
                {
                    qDebug() << "Inserted";
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

void AdventureHandler::getAdventureData(const int p_adventureId)
{
    qDebug() << "In AdventureHandler.getAdventureData";
    NfcDb DB;
    l_db = DB.getDB();
    if (l_db.open())
    {
        qDebug() << "DB connection opened.";
        QSqlQuery adventureFullFetch(l_db);
        //Fetch full user data by id
        QString adventureQuery = QString("select * from Adventures where Adventure_id = %1;").arg(p_adventureId);
        qDebug() << "Querry "<< adventureQuery;
        if (adventureFullFetch.exec(adventureQuery))
        {
            if (adventureFullFetch.next()) {
                qDebug() << "User by id found";
                l_adventureId = adventureFullFetch.value(0).toInt();
                l_ownerId = adventureFullFetch.value(1).toInt();
                l_tagId = adventureFullFetch.value(2).toInt();
                l_name = adventureFullFetch.value(3).toString();
                l_desc = adventureFullFetch.value(4).toString();
                l_clue = adventureFullFetch.value(5).toString();
                l_award = adventureFullFetch.value(5).toInt();
                l_geoLat = adventureFullFetch.value(6).toString();
                l_geoLong = adventureFullFetch.value(7).toString();
                l_status = adventureFullFetch.value(8).toInt();
                l_db.close();
                return;
            }
            else{
                qDebug() << "Adventure under ID "<< p_adventureId<< " was not found, or something went wrong";
                qDebug() << "Error happened - " << l_db.lastError().text();
                qDebug() << "Closing connection";
                l_db.close();
                gotError("Adventure wasn't found");
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

void AdventureHandler::handleError(QString p_error)
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

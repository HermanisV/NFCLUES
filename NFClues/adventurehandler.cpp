#include "adventurehandler.h"
#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QtDebug>
#include <stdlib.h>
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

double AdventureHandler::geoLat()
{
    return l_geoLat;
}

double AdventureHandler::geoLong()
{
    return l_geoLong;
}

QString AdventureHandler::errorString()
{
    return l_error;
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

void AdventureHandler::setGeoLat(const double &geoLat)
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

void AdventureHandler::setGeoLong(const double &geoLong)
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
    //validate input
    if (l_name == ""){
        gotError("Pleses spicify adventure name");
        return;
    }
    if (l_desc == ""){
        gotError("Pleses spicify adventure description");\
        return;
    }
    if (l_clue == ""){
        gotError("Pleses spicify adventure clue");\
        return;
    }
    if (l_award == 0 || l_award == NULL){
        gotError("Pleses spicify adventure award");\
        return;
    }


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
                    emit gotAdventure();
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
                l_geoLat = adventureFullFetch.value(6).toDouble();
                l_geoLong = adventureFullFetch.value(7).toDouble();
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

int AdventureHandler::getRandomTagId()
{
    qDebug() << "In AdventureHandler::getRandomTagId";
    NfcDb DB;
    l_db = DB.getDB();
    if (l_db.open())
    {
        qDebug() << "DB connection opened.";
        QSqlQuery tagIdChech(l_db);
        //Fetch full user data by id
        bool isTaken = true; //Value to check if this random tagid is already taken
        while (isTaken){
            int randomTagId = rand() % 9999999 + 1000000; //Get random Tag id that is 7 digits long
            QString tagIdQuery = QString("select count(Tag_id) from Adventures where Tag_id = %1;").arg(randomTagId);//Check Db if this Tag Id is taken, if is try another random
            qDebug() << "Querry "<< tagIdQuery;
            if (tagIdChech.exec(tagIdQuery))
            {
                if (tagIdChech.next()) {
                    if (tagIdChech.value(0).toInt() == 0){
                        qDebug()<< "Found unique Tag id as: "<<randomTagId;
                        isTaken = false;
                        return randomTagId;
                    }
                }
                else{
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
    }
}

void AdventureHandler::initAdventure(const int p_adventureId,const int p_tagId,const double p_lat,const double p_long)
{
    qDebug() << "In AdventureHandler::initAdventure";
    //Validate
    if (p_adventureId == NULL)
        gotError("No adventure ID Passed");
    if (p_tagId == NULL)
        gotError("No Tag_id passed");
    if (p_lat == NULL)
        gotError("No Lattitude passed");
    if (p_long == NULL)
        gotError("No Longituce passed");

    NfcDb DB;
    l_db = DB.getDB();
    if (l_db.open())    {
        qDebug() << "DB connection opened.";
        QSqlQuery validateFetch(l_db);
        //Fetch full user data by id
        QString validateQuerry = QString("select Adventure_id from Adventures where Tag_id = %1;").arg(p_tagId); //Check if this tag id isn''t assigned to an existing adventure
        qDebug() << "Querry "<< validateQuerry;
        if (validateFetch.exec(validateQuerry))
        {
            if (validateFetch.next()) {
                qDebug() << "Wrong Tag Id";
                qDebug() << "Closing connection";
                l_db.close();
                gotError("Ooops, there seems to be a problem");
            }
            else{
                qDebug() <<  "Tag Id Ok";                
                QString updateAdventure = QString("update adventures set Tag_id = %1,Long = %2,Lat = %3,Status = 2 where Adventure_id = %4;").arg(p_tagId).arg(p_long).arg(p_lat).arg(p_adventureId);
                qDebug() << "Update: "<<updateAdventure;
                QSqlQuery adventureInit(l_db);
                if (adventureInit.exec(updateAdventure))
                {
                    qDebug() << "Upadted";
                    l_db.close();
                    emit gotInit();
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
}

void AdventureHandler::buildAdventuresOnMap()
{
    qDebug() << "In buildAdventuresOnMap";
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

#include "adventurehandler.h"
#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QTextStream>
#include <QtDebug>
#include <QString>
#include <QStringList>
#include <QQmlContext>


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

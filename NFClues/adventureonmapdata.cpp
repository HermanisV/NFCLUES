#include "AdventureOnMapData.h"

#include <QString>
#include <QDebug>

AdventureOnMapData::AdventureOnMapData(QObject *parent)
    : QObject(parent)
{
}

AdventureOnMapData::AdventureOnMapData(const int &adventureId, const int &tagId, const QString &name, const QString &desc, const QString &clue, const int &award, const double &geoLat, const QString &geoLong, QObject *parent)
    : QObject(parent), l_adventureId(adventureId), l_tagId(tagId),l_name(name),l_desc(desc),l_clue(clue),l_award(award),l_geoLat(geoLat), l_geoLong(geoLong)
{

}

int AdventureOnMapData::adventureId() const
{
    return l_adventureId;
}

QString AdventureOnMapData::name() const
{
    return l_name;
}

QString AdventureOnMapData::desc()
{
    return l_desc;
}

QString AdventureOnMapData::clue()
{
    return l_clue;
}


int AdventureOnMapData::award() const
{
    return l_award;
}

void AdventureOnMapData::setAdventureId(const int &adventureId)
{
    if (adventureId != l_adventureId) {
        l_adventureId = adventureId;
        emit adventureIdChanged();
    }
}

void AdventureOnMapData::setTagId(const int &tagId)
{
    if (tagId != l_tagId) {
        l_tagId = tagId;
        emit tagIdChanged();
    }
}

void AdventureOnMapData::setName(const QString &name)
{
    if (name != l_name) {
        l_name = name;
        emit nameChanged();
    }
}

void AdventureOnMapData::setDesc(const QString &desc)
{
    if (desc != l_desc){
        l_desc = desc;
        emit descChanged();
    }
}

void AdventureOnMapData::setClue(const QString &clue)
{

    if (clue != l_clue){
        l_clue = clue;
        emit clueChanged();
    }
}


void AdventureOnMapData::setAward(const int &award)
{
    if (award != l_award) {
        l_award = award;
        emit awardChanged();
    }
}

void AdventureOnMapData::setGeoLat(const double &geoLat)
{
    if (geoLat != l_geoLat) {
        l_geoLat = geoLat;
        emit geoLatChanged();
    }
}

void AdventureOnMapData::setGeoLong(const double &geoLong)
{
    if (geoLong != l_geoLong) {
        l_geoLong = geoLong;
        emit geoLongChanged();
    }
}

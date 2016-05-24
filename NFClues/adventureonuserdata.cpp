#include "adventureonuserdata.h"

#include <QString>
#include <QDebug>

AdventureOnUserData::AdventureOnUserData(QObject *parent)
    : QObject(parent)
{
}

AdventureOnUserData::AdventureOnUserData(const int &adventureId, const QString &name,const int &award,const int &status, QObject *parent)
    : QObject(parent), l_adventureId(adventureId), l_name(name),l_award(award),l_status(status)
{
}

int AdventureOnUserData::adventureId() const
{
    return l_adventureId;
}

QString AdventureOnUserData::name() const
{
    return l_name;
}

int AdventureOnUserData::award() const
{
    return l_award;
}

int AdventureOnUserData::status() const
{
    return l_status;
}


void AdventureOnUserData::setAdventureId(const int &adventureId)
{
    if (adventureId != l_adventureId) {
        l_adventureId = adventureId;
        emit adventureIdChanged();
    }
}

void AdventureOnUserData::setName(const QString &name)
{
    if (name != l_name) {
        l_name = name;
        emit nameChanged();
    }
}

void AdventureOnUserData::setAward(const int &award)
{
    if (award != l_award) {
        l_award = award;
        emit awardChanged();
    }
}

void AdventureOnUserData::setStatus(const int &status)
{
    if (status != l_status) {
        l_status = status;
        emit statusChanged();
    }
}

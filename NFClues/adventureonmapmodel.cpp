#include "adventureonmapmodel.h"

AdventureOnMap::AdventureOnMap(const int &adventureId, const int &tagId, const QString &name, const QString &desc, const QString &clue, const int &award, const double &geoLat, const double &geoLong)
    : l_adventureId(adventureId), l_tagId(tagId),l_name(name),l_desc(desc),l_clue(clue),l_award(award),l_geoLat(geoLat), l_geoLong(geoLong)
{

}

int AdventureOnMap::adventureId() const
{
    return l_adventureId;
}

int AdventureOnMap::tagId() const
{
    return l_tagId;
}

QString AdventureOnMap::name() const
{
    return l_name;
}

QString AdventureOnMap::desc() const
{
    return l_desc;
}

QString AdventureOnMap::clue() const
{
    return l_clue;
}


int AdventureOnMap::award() const
{
    return l_award;
}

double AdventureOnMap::geoLat() const
{
    return l_geoLat;
}

double AdventureOnMap::geoLong() const
{
    return l_geoLong;
}

AdventureOnMapModel::AdventureOnMapModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void AdventureOnMapModel::addAdventureOnMap(const AdventureOnMap &AdventureOnMap)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    l_adventuresOnMap << AdventureOnMap;
    endInsertRows();
}

int AdventureOnMapModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return l_adventuresOnMap.count();
}

QVariant AdventureOnMapModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= l_adventuresOnMap.count())
        return QVariant();

    const AdventureOnMap &AdventureOnMap = l_adventuresOnMap[index.row()];
    switch(role)
    {
    case AdventureIdRole :
        return AdventureOnMap.adventureId();
        break;
    case TagIdRole :
        return AdventureOnMap.tagId();
        break;
    case NameRole :
        return AdventureOnMap.name();
        break;
    case DescRole :
        return AdventureOnMap.desc();
        break;
    case ClueRole :
        return AdventureOnMap.clue();
        break;
    case AwardRole :
        return AdventureOnMap.award();
        break;
    case GeoLatRole :
        return AdventureOnMap.geoLat();
        break;
    case GeoLongRole :
        return AdventureOnMap.geoLong();
        break;
    default :
        qDebug()<< "Invalid Role";
        return QVariant();
    }
}

QHash<int, QByteArray> AdventureOnMapModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[AdventureIdRole] = "adventureId";
    roles[TagIdRole] = "tagId";
    roles[NameRole] = "name";
    roles[DescRole] = "description";
    roles[ClueRole] = "clue";
    roles[AwardRole] = "award";
    roles[GeoLatRole] = "geoLat";
    roles[GeoLongRole] = "geoLong";
    return roles;
}

#ifndef ADVENTUREONMAPMODEL_H
#define ADVENTUREONMAPMODEL_H
#include <QString>
#include <QAbstractListModel>
#include <QStringList>
#include <QDebug>
class AdventureOnMap
{
public:
    AdventureOnMap(const int &adventureId, const int &tagId, const QString &name, const QString &desc, const QString &clue, const int &award, const double &geoLat, const double &geoLong);

    int     adventureId() const;
    int     tagId() const;
    QString name() const;
    QString desc() const;
    QString clue() const;
    int     award() const;
    double  geoLat() const;
    double geoLong() const;

private:
    int     l_adventureId;
    int     l_tagId;
    QString l_name;
    QString l_desc;
    QString l_clue;
    int     l_award;
    double  l_geoLat;
    double  l_geoLong;
};

class AdventureOnMapModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AdventureOnMapRoles {
        AdventureIdRole  = Qt::UserRole + 1,
        TagIdRole,
        NameRole,
        DescRole,
        ClueRole,
        AwardRole,
        GeoLatRole,
        GeoLongRole
    };

    AdventureOnMapModel(QObject *parent = 0);

    void addAdventureOnMap(const AdventureOnMap &AdventureOnMap);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<AdventureOnMap> l_adventuresOnMap;
};

#endif // ADVENTUREONMAPMODEL_H

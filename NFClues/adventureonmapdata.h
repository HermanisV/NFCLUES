#ifndef ADVENTUREONMAPDATA_H
#define ADVENTUREONMAPDATA_H

#include <QObject>
#include <QString>
#include <QDebug>

//Qbject used to build record for model
//To be passed through AdventureHandler::adventuresOnMap to be delefgated on map
class AdventureOnMapData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int adventureId READ adventureId WRITE setAdventureId NOTIFY adventureIdChanged)
    Q_PROPERTY(int tagId READ tagId WRITE setTagId NOTIFY tagIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY descChanged)
    Q_PROPERTY(int award READ award WRITE setAward NOTIFY awardChanged)
    Q_PROPERTY(QString clue READ clue WRITE setClue NOTIFY clueChanged)
    Q_PROPERTY(double geoLat READ geoLat WRITE setGeoLat NOTIFY geoLatChanged)
    Q_PROPERTY(double geoLong READ geoLong WRITE setGeoLong NOTIFY geoLongChanged)

public:
    AdventureOnMapData(QObject *parent=0);
    AdventureOnMapData(const int &adventureId, const int &tagId, const QString &name, const QString &desc, const QString &clue, const int &award, const double &geoLat, const double &geoLong, QObject *parent=0);
    //Getters
    int     adventureId() const;
    int     tagId() const;
    QString name() const;
    QString desc() const;
    QString clue() const;
    int     award() const;
    double  geoLat();
    double  geoLong();

    //Setters
    void setAdventureId(const int &adventureId);
    void setTagId(const int &tagId);
    void setName(const QString &name);
    void setDesc(const QString &desc);
    void setClue(const QString &clue);
    void setAward(const int &award);
    void setGeoLat(const double &geoLat);
    void setGeoLong(const double &geoLong);

signals:
    void adventureIdChanged();
    void tagIdChanged();
    void nameChanged();
    void descChanged();
    void clueChanged();
    void awardChanged();
    void geoLatChanged();
    void geoLongChanged();

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
#endif // ADVENTUREONMAPDATA_H

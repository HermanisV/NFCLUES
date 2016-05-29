#ifndef ADVENTUREHANDLER_H
#define ADVENTUREHANDLER_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QtDebug>
#include <QString>
#include "nfcdb.h"

/* This class is used for handling all Adventure related data
 * New adventure craetion
 * Creating model from your adventures
 * Initilizing adventures
 * Fetching adventurs
 * Completing adventurs
 */

class AdventureHandler : public QObject
{
    Q_OBJECT
public:
    explicit AdventureHandler(QObject *parent = 0);
    //Props
    Q_PROPERTY(int adventureId READ adventureId WRITE setAdventureId NOTIFY adventureIdChanged)
    Q_PROPERTY(int ownerId READ ownerId WRITE setOwnerId)
    Q_PROPERTY(int tagId READ tagId WRITE setTagId NOTIFY tagIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY descChanged)
    Q_PROPERTY(QString clue READ clue WRITE setClue NOTIFY clueChanged)
    Q_PROPERTY(int award READ award WRITE setAward NOTIFY awardChanged)
    Q_PROPERTY(double geoLat READ geoLat WRITE setGeoLat NOTIFY geoLatChanged)
    Q_PROPERTY(double geoLong READ geoLong WRITE setGeoLong NOTIFY geoLongChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY errorChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)

    //Getters
    int adventureId();
    int ownerId();
    int tagId();
    QString name();
    QString desc();
    QString clue();
    int award();
    double geoLat();
    double geoLong();
    QString errorString();
    int     status();

    //Setters
    void    setAdventureId(const int &adventureId);
    void    setOwnerId(const int &ownerId);
    void    setTagId(const int &tagId);
    void    setName(const QString &name);
    void    setDesc(const QString &desc);
    void    setClue(const QString &clue);
    void    setAward(const int &award);
    void    setGeoLat(const double &geoLat);
    void    setGeoLong(const double &geoLong);
    void    setStatus(const int &status);

    //Methods
    Q_INVOKABLE void  createNewAdventure(const int ownerId);
    Q_INVOKABLE void  getAdventureData(const int p_adventureId);
    //Signals
signals:
    void adventureIdChanged();
    void tagIdChanged();
    void nameChanged();
    void descChanged();
    void clueChanged();
    void awardChanged();
    void geoLatChanged();
    void geoLongChanged();
    void statusChanged();
    void gotError(QString);
    void gotAdventure();
    void error();\
    void errorChanged();
    //Slots
protected slots:
    void handleError(QString p_error);
private:
    //User data
    int l_adventureId;
    int l_ownerId;
    int l_tagId;
    QString l_name;
    QString l_desc;
    QString l_clue;
    int l_award;
    double l_geoLat;
    double l_geoLong;
    int     l_status;
    QString l_error;
    QSqlDatabase l_db;
    bool l_loading;

    void createDb();
};


#endif // ADVENTUREHANDLER_H

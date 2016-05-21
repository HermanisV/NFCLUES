#ifndef ADVENTUREHANDLER_H
#define ADVENTUREHANDLER_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QTextStream>
#include <QtDebug>
#include <QString>
#include <QStringList>
#include <QQmlContext>
#include "nfcdb.h"

/* This class is used for handling all Adventure related data
 * New adventure craetion
 * Listing your adventures
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
    Q_PROPERTY(QString geoLat READ geoLat WRITE setGeoLat NOTIFY geoLatChanged)
    Q_PROPERTY(QString geoLong READ geoLong WRITE setGeoLong NOTIFY geoLongChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)

    //Getters
    int adventureId();
    int ownerId();
    int tagId();
    QString name();
    QString desc();
    QString clue();
    int award();
    QString geoLat();
    QString geoLong();
    int     status();

    //Setters
    void    setAdventureId(const int &adventureId);
    void    setOwnerId(const int &ownerId);
    void    setTagId(const int &tagId);
    void    setName(const QString &name);
    void    setDesc(const QString &desc);
    void    setClue(const QString &clue);
    void    setAward(const int &award);
    void    setGeoLat(const QString &geoLat);
    void    setGeoLong(const QString &geoLong);
    void    setStatus(const int &status);

    //Methods
    //Q_INVOKABLE void  createNewAdventure();
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
    void error();

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
    QString l_geoLat;
    QString l_geoLong;
    int     l_status;
    QString l_error;
    QSqlDatabase l_db;

    void createDb();
};


#endif // ADVENTUREHANDLER_H

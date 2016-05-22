#ifndef ADVENTUREONUSERDATA_H
#define ADVENTUREONUSERDATA_H

#include <QObject>
#include <QString>
#include <QDebug>


//Qbject used to build record for model
//To be passed through delegate to render the Your Adventures table
class AdventureOnUserData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int adventureId READ adventureId WRITE setAdventureId NOTIFY adventureIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int award READ award WRITE setAward NOTIFY awardChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)

public:
    AdventureOnUserData(QObject *parent=0);
    AdventureOnUserData(const int &adventureId, const QString &name,const int &award,const int &status, QObject *parent=0);
    //Getters
    int     adventureId() const;
    QString name() const;
    int     award() const;
    int     status() const;

    //Setters
    void setAdventureId(const int &adventureId);
    void setName(const QString &name);
    void setAward(const int &award);
    void setStatus(const int &status);

signals:
    void adventureIdChanged();
    void nameChanged();
    void awardChanged();
    void statusChanged();

private:
    int     l_adventureId;
    QString l_name;
    int     l_award;
    int     l_status;
};


#endif // ADVENTUREONUSERDATA_H

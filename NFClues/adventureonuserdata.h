#ifndef ADVENTUREONUSERDATA_H
#define ADVENTUREONUSERDATA_H

#include <QObject>
#include <QString>
#include <QDebug>


//Qbject used to build record for model
//To be passed throthisAdventureInitugh delegate to render the Your Adventures table
class AdventureOnUserData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int adventureId READ adventureId WRITE setAdventureId NOTIFY adventureIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int award READ award WRITE setAward NOTIFY awardChanged)
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString desc READ desc WRITE setDesc NOTIFY descChanged)
    Q_PROPERTY(QString clue READ clue WRITE setClue NOTIFY clueChanged)

public:
    AdventureOnUserData(QObject *parent=0);
    AdventureOnUserData(const int &adventureId, const QString &name,const int &award,const int &status,const QString &desc, const QString &clue, QObject *parent=0);
    //Getters
    int     adventureId() const;
    QString name() const;
    int     award() const;
    int     status() const;
    QString desc();
    QString clue();

    //Setters
    void setAdventureId(const int &adventureId);
    void setName(const QString &name);
    void setAward(const int &award);
    void setStatus(const int &status);
    void setDesc(const QString &desc);
    void setClue(const QString &clue);

signals:
    void adventureIdChanged();
    void nameChanged();
    void awardChanged();
    void statusChanged();
    void descChanged();
    void clueChanged();

private:
    int     l_adventureId;
    QString l_name;
    int     l_award;
    int     l_status;
    QString l_desc;
    QString l_clue;
};


#endif // ADVENTUREONUSERDATA_H

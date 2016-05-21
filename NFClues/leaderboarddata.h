#ifndef LEADERBOARDDATA_H
#define LEADERBOARDDATA_H

#include <QObject>
#include <QString>
#include <QDebug>


//Qbject used to build record for model
//To be passed through delegate to render the Leaderboard table
class LeaderboardData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int place READ place WRITE setPlace NOTIFY placeChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(int points READ points WRITE setPoints NOTIFY pointsChanged)

public:
    LeaderboardData(QObject *parent=0);
    LeaderboardData(const int &place, const QString &login,const int &points, QObject *parent=0);
    //Getters
    int     place() const;
    QString login() const;
    int     points() const;

    //Setters
    void setPlace(const int &place);
    void setLogin(const QString &login);
    void setPoints(const int &points);

signals:
    void placeChanged();
    void loginChanged();
    void pointsChanged();

private:
    int     l_place;
    QString l_login;
    int     l_points;
};


#endif // LEADERBOARDDATA_H

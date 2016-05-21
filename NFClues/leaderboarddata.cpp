#include "leaderboarddata.h"

#include <QString>
#include <QDebug>

LeaderboardData::LeaderboardData(QObject *parent)
    : QObject(parent)
{
}

LeaderboardData::LeaderboardData(const int &place, const QString &login,const int &points, QObject *parent)
    : QObject(parent), l_place(place), l_login(login),l_points(points)
{
}

int LeaderboardData::place() const
{
    return l_place;
}

QString LeaderboardData::login() const
{
    return l_login;
}

int LeaderboardData::points() const
{
    return l_points;
}

void LeaderboardData::setPlace(const int &place)
{
    if (place != l_place) {
        l_place = place;
        emit placeChanged();
    }
}

void LeaderboardData::setLogin(const QString &login)
{
    if (login != l_login) {
        l_login = login;
        emit loginChanged();
    }
}

void LeaderboardData::setPoints(const int &points)
{
    if (points != l_points) {
        l_points = points;
        emit pointsChanged();
    }
}

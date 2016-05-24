#ifndef USERHANDLER_H
#define USERHANDLER_H
#include <QDebug>
#include <QObject>
#include <QString>
#include <QtSql>
#include <QErrorMessage>
#include <QtQml>
#include "qqml.h"
#include "leaderboarddata.h"
#include "adventureonuserdata.h"
#include "nfcdb.h"

/* This class is used for handling all user related data.
 * New user creaion
 * Login
 * Profile checking
 * Awarding points
 * Administration
 */

class UserHandler : public QObject
{
    Q_OBJECT
public:
    explicit UserHandler(QObject *parent = 0);
    //Props
    Q_PROPERTY(int userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString login READ login WRITE setLogin/* NOTIFY loginChanged*/)
    Q_PROPERTY(QString email READ email WRITE setEmail/* NOTIFY emailChanged*/)
    Q_PROPERTY(QString password READ password WRITE setPassword/* NOTIFY passwordChanged*/)
    Q_PROPERTY(int points READ points WRITE setPoints NOTIFY pointsChanged)
    Q_PROPERTY(int role READ role WRITE setRole/* NOTIFY roleChanged*/)
    Q_PROPERTY(QString errorString READ errorString/* NOTIFY ErrorChanged*/)
    Q_PROPERTY(int place READ place/* WRITE setPlace NOTIFY placeChanged*/)
    Q_PROPERTY(QList<QObject *> leaderTable READ leaderTable NOTIFY leaderTableChanged)
    Q_PROPERTY(QList<QObject *> usersAdventuresTable READ usersAdventuresTable NOTIFY usersAdventuresTableChanged)

    //Getters
    int     userId();
    QString login();
    QString email();
    QString password();
    int     points();
    int     role();
    QString errorString();
    int     place();
    QSqlDatabase db();
    QList<QObject *> leaderTable();
    QList<QObject *> usersAdventuresTable();

    //Setters
    void    setUserId(const int &userId);
    void    setLogin(const QString &login);
    void    setEmail(const QString &email);
    void    setPassword(const QString &password);
    void    setPoints(const int &points);
    void    setRole(const int &role);
    //Methods
    Q_INVOKABLE void  createNewUser();
    Q_INVOKABLE void  loginUser(QString p_login, QString p_pass);
    Q_INVOKABLE bool  getUserData(QString p_login);
    Q_INVOKABLE void  addAdventureToList(int p_adventureId, QString p_name, int p_award, int p_status);
    //Signals
signals:
    void userIdChanged();
    void pointsChanged();
    void leaderTableChanged();
    void usersAdventuresTableChanged();
    void gotLogin();
    void gotError(QString);
    void error();
    void startLoading();
    void endLoading();

    //Slots
protected slots:
    void handleError(QString p_error);
    void buildLeaderboard();
    void buildUsersAdventureTable(int user_id = NULL);

private:
    //User data
    int     l_userId;
    QString l_login;
    QString l_email;
    QString l_password;
    int     l_points;
    int     l_role;
    int     l_place;
    QString l_error;
    QSqlDatabase l_db;
    QList<QObject *>  l_leaderTable;
    QList<QObject *>  l_userAdventureTable;
    bool    l_loading;
};

#endif // USERHANDLER_H

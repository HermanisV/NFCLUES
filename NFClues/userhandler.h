#ifndef USERHANDLER_H
#define USERHANDLER_H
#include <QObject>
#include <QString>
#include <QtSql>
#include <QDebug>
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
    Q_PROPERTY(int place READ place WRITE setPlace NOTIFY placeChanged)
    Q_PROPERTY(QList<QObject *> leaderTable READ leaderTable NOTIFY leaderTableChanged)
    Q_PROPERTY(QList<QObject *> usersAdventuresTable READ usersAdventuresTable NOTIFY usersAdventuresTableChanged)
    Q_PROPERTY(QList<QObject *> usersDoneAdventuresTable READ usersDoneAdventuresTable NOTIFY usersDoneAdventuresTableChanged)

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
    QList<QObject *> usersDoneAdventuresTable();

    //Setters
    void    setUserId(const int &userId);
    void    setLogin(const QString &login);
    void    setEmail(const QString &email);
    void    setPassword(const QString &password);
    void    setPoints(const int &points);
    void    setRole(const int &role);
    void    setPlace(const int &place);
    //Methods
    //Registers new user
    Q_INVOKABLE void  createNewUser();
    //Validates if login and pasword are corect
    Q_INVOKABLE void  loginUser(QString p_login, QString p_pass);
    //Fetches and fills objects data with user under this login
    Q_INVOKABLE bool  getUserData(QString p_login);
    //Used to add the newley created adventure to the l_userAdventureTable, so it doesn't have to be build a new altogether
    Q_INVOKABLE void  addAdventureToList(int p_adventureId, QString p_name, int p_award, int p_status, QString p_desc, QString p_clue);
    //Used to add the newley completed adventure to the l_userDoneAdventureTable, so it doesn't have to be build a new altogether
    Q_INVOKABLE void  addDoneAdventureToList(int p_adventureId, QString p_name, int p_award, int p_status, QString p_desc, QString p_clue);
    //Used to delete advventure and all its related recods
    Q_INVOKABLE bool  deleteAdventure(int p_userId, int p_adventureId);

    //Signals
signals:
    void userIdChanged();
    void pointsChanged();
    void leaderTableChanged();
    void usersAdventuresTableChanged();
    void usersDoneAdventuresTableChanged();
    void gotLogin();
    void gotError(QString);
    void error();
    void startLoading();
    void endLoading();
    void deletedAdventure();
    void placeChanged();

    //Slots
protected slots:
    void handleError(QString p_error);
    void buildLeaderboard();
    void buildUsersAdventureTable(int user_id = NULL);
    void buildUsersDoneAdventuresTable(int user_id = NULL);
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
    QList<QObject *>  l_userDoneAdventureTable;
    bool    l_loading;
};

#endif // USERHANDLER_H

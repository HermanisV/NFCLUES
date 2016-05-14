#ifndef USERHANDLER_H
#define USERHANDLER_H

#include <QObject>
#include <QtCore>
#include <QtSql>
#include <QtDebug>
#include <QTextStream>
#include <QString>
#include <QStringList>


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
    Q_PROPERTY(int userId READ userId WRITE setUserId/* NOTIFY userIdChanged*/)
    Q_PROPERTY(QString login READ login WRITE setLogin/* NOTIFY loginChanged*/)
    Q_PROPERTY(QString email READ email WRITE setEmail/* NOTIFY emailChanged*/)
    Q_PROPERTY(QString password READ password WRITE setPassword/* NOTIFY passwordChanged*/)
    Q_PROPERTY(int points READ points WRITE setPoints/* NOTIFY pointsChanged*/)
    Q_PROPERTY(int role READ role WRITE setRole/* NOTIFY roleChanged*/)

    //Getters
    int     userId();
    QString login();
    QString email();
    QString password();
    int     points();
    int     role();

    //Setters
    void    setUserId(const int &userId);
    void    setLogin(const QString &login);
    void    setEmail(const QString &email);
    void    setPassword(const QString &password);
    void    setPoints(const int &points);
    void    setRole(const int &role);

    //Methods
    Q_INVOKABLE void    createNewUser();
    //Signals

    //Slots

signals:

private:
    int     l_userId;
    QString l_login;
    QString l_email;
    QString l_password;
    int     l_points;
    int     l_role;
};

#endif // USERHANDLER_H

#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QtCore>
#include <QtSql>

/* This class is used for handling all
 * user related data handling, passing it to DB,
 * validating it.*/

//User Data
class UserModelData : public QSharedData
{
public:
    UserModelData(){}
    UserModelData(const UserModelData &user)
        : QSharedData(user), user_id(user.user_id), login(user.login), email(user.email), password(user.password), points(user.points), role(user.role){}
    ~UserModelData(){}
    //Full data set coresponding current Users Table
    int     user_id;
    QString login;
    QString email;
    QString password;
    int     points;
    int     role;
};
//End User Data

class UserModel
{
public:
    UserModel();    
    UserModel(const int p_user_id, QString *p_login, QString *p_email, QString *p_password, int *p_points);
    UserModel &operator=(const UserModel &);
    ~UserModel();
    //Create new user
    void NewUser();


private:
    QSharedDataPointer<UserModelData> l_user;
};

#endif // USERMODEL_H

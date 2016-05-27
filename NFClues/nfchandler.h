#ifndef NFCHANDLER_H
#define NFCHANDLER_H

#include <QObject>
//#include <QNearFieldManager>
#include <QtSql>
#include <QDebug>
#include <QtQml>

/* This class is used for handling all tag related operations
 * writing tag
 * reading tag
 */
class NFCHandler : public QObject
{
    Q_OBJECT
public:
    explicit NFCHandler(QObject *parent = 0);
    Q_PROPERTY(int tagId READ tagId WRITE setTagId NOTIFY tagIdChanged)

    //Getters
    int     tagId();

    //Setters
    void    setTagId(const int &tagId);
signals:
    void tagIdChanged();
public slots:

private:
    //Tag data
    int     l_tagId;
};

#endif // NFCHANDLER_H

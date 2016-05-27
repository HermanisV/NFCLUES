#include "nfchandler.h"
#include <QObject>
#include <QNearFieldManager>
#include <QtSql>
#include <QDebug>
#include <QtQml>

NFCHandler::NFCHandler(QObject *parent) : QObject(parent)
{

}

int NFCHandler::tagId()
{
    return l_tagId;
}

void NFCHandler::setTagId(const int &tagId)
{
    if (l_tagId == tagId)
        return;
    l_tagId = tagId;
    emit tagIdChanged();
}

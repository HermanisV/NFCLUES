#include "system.h"
#include <QObject>
#include <QString>
#include <QSysInfo>
#include <QDebug>


System::System(QObject *parent) : QObject(parent)
{

}

QString System::getEnv()
{
    QSysInfo thisSystem;
    return thisSystem.kernelType();
}

#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QString>
#include <QSysInfo>

class System : public QObject
{
    Q_OBJECT
public:
    explicit System(QObject *parent = 0);    
    Q_INVOKABLE  QString getEnv();

signals:

public slots:
};

#endif // SYSTEM_H

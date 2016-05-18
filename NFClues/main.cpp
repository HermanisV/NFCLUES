#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QQmlContext>
#include "qqml.h"
#include "userhandler.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<UserHandler>("NFCUser",0,1,"HandleUser");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

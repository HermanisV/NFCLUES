#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QQmlContext>
#include <QtQuick/qquickview.h>
#include <QNetworkAccessManager>
#include "qqml.h"
#include "userhandler.h"
#include "adventurehandler.h"
#include "nfchandler.h"
#include  "system.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //UserHandler
    qmlRegisterType<UserHandler>("NFCUser",0,1,"HandleUser");
    //AdventureHandler
    qmlRegisterType<AdventureHandler>("NFCAdventure",0,1,"HandleAdventure");
    //TagHandler
    qmlRegisterType<NFCHandler>("NFCTag",0,1,"HandleTag");
    //TagHandler
    qmlRegisterType<System>("ThisSystem",0,1,"System");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

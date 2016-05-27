#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QStringList>
#include <QQmlContext>
#include <QtQuick/qquickview.h>
#include <QNetworkAccessManager>
#include <QQmlNetworkAccessManagerFactory>
#include <QtScript/qscriptengine.h>
#include <QtScript/QScriptValueIterator>
#include "qqml.h"
#include "userhandler.h"
#include "adventurehandler.h"
#include "nfchandler.h"
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

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

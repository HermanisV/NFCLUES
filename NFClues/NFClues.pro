TEMPLATE = app

QT += qml quick
QT += qml quick widgets
QT += core
QT       += network
QT += sql
android{
QT += androidextras
}
CONFIG += c++11

SOURCES += main.cpp \
    userhandler.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    userhandler.h

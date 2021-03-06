TEMPLATE = app

QT += qml quick
QT += qml quick widgets
QT += core
QT += positioning
QT += network
QT += nfc
QT += sql
QT += script
android{
QT += androidextras
}
CONFIG += c++11

SOURCES += main.cpp \
    userhandler.cpp \
    leaderboarddata.cpp \
    adventurehandler.cpp \
    nfcdb.cpp \
    adventureonuserdata.cpp \
    nfchandler.cpp \
    system.cpp \
    nfcnetwork.cpp \
    adventureonmapmodel.cpp \
    vibrator.cpp

RESOURCES += qml.qrc

OTHER_FILES += \
    main.qml \
    SideForm.qml \
    helper.js \
    Items/MapComponent.qml \
    Items/SeeAdventure.qml \
    Items/User.qml \
    Forms/CreateAdventures.qml \
    Forms/Register.qml \
    Forms/Login.qml \
    Views/Leaderboards.qml \
    Views/YourAdventures.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH2 = C:\NFClues_builds\

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    userhandler.h \
    leaderboarddata.h \
    adventurehandler.h \
    nfcdb.h \
    adventureonuserdata.h \
    nfchandler.h \
    system.h \
    nfcnetwork.h \
    adventureonmapmodel.h \
    vibrator.h

DISTFILES += \
    helper.js \
    Forms/NfcManualWrite.qml

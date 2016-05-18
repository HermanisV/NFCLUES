import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2

Item {
    id: itmSideForm
    width: Screen.width * 0.8
    height: flcmain.height
    //property alias btnCommit: btnCommit
    property string errorString
    property bool userOK: false

    Rectangle {
        anchors.fill: parent
        color: "lightgray"
        TabView {
            visible: !userOK
            width: Screen.width * 0.8
            height: flcmain.height
            id: newTabView
            Tab {
                title: "Register"
                Register { anchors.fill: parent }
            }

            Tab {
                title: "Login"
                Login { anchors.fill: parent }
            }
        }
        TabView {
            visible: userOK
            width: Screen.width * 0.8
            height: flcmain.height
            id: logTabView
            Tab {
                title: "User"
            }

            Tab {
                title: "Adventures"
            }

            Tab {
                title: "Leaderboards"
            }
        }
    }
}

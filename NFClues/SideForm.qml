import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2
import "Forms"
import "Views"
import "Items"

Item {
    id: itmSideForm
    width: Screen.width * 0.8
    height: flcmain.height
    //property alias btnCommit: btnCommit
    property string errorString

    Rectangle {
        anchors.fill: parent
        color: "lightgray"
        Loader { id: leaderboardLoader }
        TabView {
            visible: !mainUserHandle.userOK
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
            visible: mainUserHandle.userOK
            width: Screen.width * 0.8
            height: flcmain.height
            id: logTabView
            Tab {
                title: "User"
                User {
                   anchors.fill: parent
                   mainUserLogin  : mainUserHandle.login
                   mainUserPlace  : mainUserHandle.place
                   mainUserPoints : mainUserHandle.points
                }
            }

            Tab {
                title: "Create adventures"
                CreateAdventures{ anchors.fill: parent }
            }

            Tab {
                title: "Your Adventures"
                YourAdventures{ anchors.fill: parent }
            }

            Tab {
                title: "Leaderboards"
                Leaderboards{ anchors.fill: parent }
            }
        }
    }
}

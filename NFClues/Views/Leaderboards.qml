import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import NFCUser 0.1

Rectangle {
    property int mainUserid
    property int mainUserPlace
    property int mainUserPoints
    id: advMain
    width: Screen.width * 0.7
    height: Screen.height
    color: "lightgray"
    Text {
        id: lblYourAdvnts
        y: 45
        anchors.top: parent.top
        anchors.topMargin: 15
        text: qsTr("Top 100 adventurers: ")
        anchors.left: parent.left
        anchors.leftMargin: 65
        font.pixelSize: 42
    }
    Rectangle{
        id: rctLeaderboard
        width: parent.width * 0.9
        height: parent.height * 0.7
        color: "lightgray"
        anchors.top: parent.top
        anchors.topMargin: 65
        anchors.left: parent.left
        anchors.leftMargin: 65
        TableView {
            id:tblLeaders
            anchors.fill: parent
            model: mainUserHandle.leaderTable
            TableViewColumn {
                id: colView
                role: "place"
                title: "Place"
                width: 36
            }
            TableViewColumn {
                id: colLogin
                role: "login"
                title: "Username"
                width: 800
            }
            TableViewColumn {
                id: colPoints
                role: "points"
                title: "Points"
                width: 128
            }
        }
    }
}

import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Dialogs 1.2
import NFCUser 0.1

Flickable{
    signal closeForm()
    id: bigFlick
    width: Screen.width
    height: Screen.height
    contentHeight: Screen.height
    contentWidth: Screen.width + 1
    contentX: 1
    boundsBehavior: Flickable.OvershootBounds
    flickableDirection: Flickable.HorizontalFlick

    onFlickStarted: {
        console.log(horizontalVelocity)
        if (horizontalVelocity<=-700){
            closeForm()
        }
        else contentX = 1
    }
    Rectangle {
        id: advMain
        anchors.fill: parent
        color: "lightgray"
        Text {
            id: lblYourAdvnts
            anchors.top: parent.top
            anchors.topMargin: 15
            text: qsTr("Top 100 adventurers: ")
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            font.pixelSize: 32
        }
        Rectangle{
            id: rctLeaderboard
            width: parent.width * 0.8
            height: parent.height * 0.6
            color: "lightgray"
            anchors.top: lblYourAdvnts.bottom
            anchors.topMargin: 16
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            TableView {
                id:tblLeaders
                anchors.fill: parent
                model: mainUserHandle.leaderTable
                TableViewColumn {
                    id: colView
                    role: "place"
                    title: "Place"
                    width: rctLeaderboard.width * 0.099
                }
                TableViewColumn {
                    id: colLogin
                    role: "login"
                    title: "Username"
                    width: rctLeaderboard.width * 0.7
                }
                TableViewColumn {
                    id: colPoints
                    role: "points"
                    title: "Points"
                    width: rctLeaderboard.width * 0.199
                }
            }
            Button {
                id: cancelButton
                anchors.top: tblLeaders.bottom
                anchors.topMargin: 55
                width: parent.width * 0.24
                height: Screen.height * 0.05
                text: qsTr("Close")
                anchors.right: tblLeaders.right
                anchors.rightMargin: 0
                onClicked: closeForm()
            }
        }        
    }
}

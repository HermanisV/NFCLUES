import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1

Item {
    property int mainUserid
    property int mainUserPoints
    property string ownerUserLogin
    property string thisAdventureName
    property string thisAdventureDesc
    property string thisAdventureClue
    property int thisAdventureAward
    property int thisAdventureCompletedBy

    id: seeAdvMain
    width: Screen.width * 0.675
    height: Screen.height

    Rectangle {
        id: seeAdvRect
        color: "lightgray"
        anchors.fill: parent
        Flickable {
            anchors.left: parent.left
            anchors.leftMargin: 65
            clip: true
            height: parent.height
            contentHeight: seeAdvCols.height
            contentWidth: parent.width - anchors.leftMargin
            Column {
                id: seeAdvCols
                anchors.fill:parent
                anchors.margins: 5
                spacing: 12

                Text {
                    id: txtAdvName
                    text: thisAdventureName
                    font.bold: true
                    font.pixelSize: 28
                }
                Text {
                    id: txtAdvMadeBy
                    text: qsTr("Adventure by: " + ownerUserLogin)
                    font.pixelSize: 26
                }

                Text {
                    id: txtAdvDesc
                    text: thisAdventureDesc
                    font.pixelSize: 26
                }

                Text {
                    id: txtAdvClue
                    text: thisAdventureClue
                    font.pixelSize: 26
                }
                Rectangle {
                    width: parent.width
                    height: 26
                    Text {
                        id: txtCompletedBy
                        text: qsTr("This adventure has been completed by " + thisAdventureCompletedBy.toString() + " adventurers")
                        anchors.left: parent.left
                        font.pixelSize: 26
                    }

                    Text {
                        id: txtAdvWorth
                        text: qsTr("Worth " + thisAdventureAward.toString() + "pts")
                        anchors.right: parent.right
                        font.pixelSize: 26
                    }
                }
            }
        }
    }
}

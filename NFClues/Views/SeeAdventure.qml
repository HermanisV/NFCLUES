import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1

Flickable{
    signal closeForm()
    property string ownerUserLogin
    property string thisAdventureName
    property string thisAdventureDesc
    property string thisAdventureClue
    property int thisAdventureAward
    property int thisAdventureCompletedBy
    property int thisAdventureInit : 1

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
        id: seeAdvMain
        anchors.fill: parent
        color: "lightgray"
        Rectangle {
            id: seeAdvRect
            color: "lightgray"
            anchors.leftMargin: 136
            width: parent.width * 0.8
            height: parent.height * 0.7
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: parent.left
            Flickable {
                id: flickable1
                anchors.fill: parent
                clip: true
                contentHeight: seeAdvCols.height
                contentWidth: parent.width
                boundsBehavior: Flickable.StopAtBounds
                flickableDirection: Flickable.VerticalFlick
                Column {
                    id: seeAdvCols
                    width: parent.width
                    anchors.margins: 5
                    spacing: 16
                    Text {
                        id: txtAdvName
                        text: thisAdventureName
                        font.bold: true
                        font.pixelSize: 36
                    }
                    Text {
                        id: txtAdvMadeBy
                        text: qsTr("Adventure by: " + ownerUserLogin)
                        font.pixelSize: 26
                    }

                    Text {
                        text: "Description"
                        font.pixelSize: 32
                        font.bold: true
                    }

                    Text {
                        id: txtAdvDesc
                        text: thisAdventureDesc
                        font.pixelSize: 26
                    }

                    Text {
                        text: "Clue"
                        font.pixelSize: 32
                        font.bold: true
                    }

                    Text {
                        id: txtAdvClue
                        text: thisAdventureClue
                        font.pixelSize: 26
                    }

                    Rectangle {
                        width: parent.width
                        height: 26
                        color: "lightgray"
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

            RowLayout {
                id: btnRow
                anchors.top: seeAdvRect.bottom
                anchors.topMargin: 55
                width: seeAdvRect.width
                height: Screen.height * 0.05

                Button {
                    id: cancelButton
                    Layout.fillHeight: true
                    Layout.minimumWidth: parent.width * 0.24
                    text: qsTr("Cancel")
                    onClicked: closeForm()
                }

//                Button {
//                    id: editButton
//                    Layout.fillHeight: true
//                    Layout.minimumWidth: parent.width * 0.24
//                    text: qsTr("Edit")
//                    onClicked: {
//                        console.log("Clicked edit")
//                    }
//                }

                Button {
                    id: btnLogin
                    Layout.fillHeight: true
                    Layout.minimumWidth: parent.width * 0.75
                    text: qsTr("Initialise")
                    onClicked: {
                        console.log("Clicked init")
                    }
                }
            }
        }

    }
}

import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1

Flickable{
    signal closeForm()
    property string ownerUserLogin
    property int    thisAdventureId
    property string thisAdventureName
    property string thisAdventureDesc
    property string thisAdventureClue
    property int thisAdventureAward
    property int thisAdventureCompletedBy
    property bool canInit : false   //can it be initilised
    property bool isOwner : false   //is caller Owner
    property bool fromMap : false   //is it called form Map

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
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            width: parent.width * 0.8
            height: parent.height * 0.8
            anchors.top: parent.top
            anchors.topMargin: 16
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
                    spacing: 16
                    Text {
                        id: txtAdvName
                        text: thisAdventureName
                        font.bold: true
                        font.pointSize: 24
                        height: Screen.height * 0.065
                    }
                    Text {
                        id: txtAdvMadeBy
                        visible: !fromMap
                        text: qsTr("Adventure by: " + ownerUserLogin)
                        //font.pixelSize: 26
                        font.pointSize: 16
                    }

                    Text {
                        text: "Description"
                        font.pointSize: 18
                        font.bold: true
                    }

                    Text {
                        id: txtAdvDesc
                        text: "     "+ thisAdventureDesc
                        font.pointSize: 16
                    }

                    Text {
                        text: "Clue"
                        font.pointSize: 18
                        font.bold: true
                    }

                    Text {
                        id: txtAdvClue
                        text: "     "+ thisAdventureClue
                        font.pointSize: 16
                    }

                    Rectangle {
                        id: rectangle1
                        width: parent.width
                        height: 26
                        color: "lightgray"
                        Text {
                            id: txtCompletedBy
                            visible: !fromMap
                            text: qsTr("This adventure has been completed by " + thisAdventureCompletedBy.toString() + " adventurers")
                            anchors.left: parent.left
                            font.pointSize: 16
                        }

                        Text {
                            id: txtAdvWorth
                            text: qsTr("Worth " + thisAdventureAward.toString() + "pts")
                            anchors.top: txtCompletedBy.bottom
                            anchors.topMargin: 2
                            anchors.right: parent.right
                            font.pointSize: 16
                        }
                    }
                }
            }

            RowLayout {
                id: btnRow
                anchors.top: seeAdvRect.bottom
                anchors.topMargin: 16
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
                    id: btnInit
                    visible: canInit && isOwner
                    Layout.fillHeight: true
                    Layout.minimumWidth: parent.width * 0.75
                    text: qsTr("Initialise")
                    onClicked: {
                        console.log("Clicked init")
                        stackView.push({ item: Qt.resolvedUrl("../Items/InitAdventure.qml") ,
                                           properties: { "thisAdventureId"  : thisAdventureId}})
                        stackView.currentItem.closeForm.connect(stackView.backForm)
                    }
                }

                Button {
                    id: btnComplete
                    visible: (!(canInit && isOwner) && mainUserHandle.userOK)
                    Layout.fillHeight: true
                    Layout.minimumWidth: parent.width * 0.75
                    text: qsTr("Complete")
                    onClicked: {
                        console.log("Clicked complete")
                    }
                }
            }
        }

    }
}

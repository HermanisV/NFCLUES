import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2

Flickable{
    signal closeForm()
    id: bigFlick
    property variant adventureRecord

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
            text: qsTr("Your adventures: ")
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            font.pixelSize: 32
        }

        Rectangle{
            id: rctUsersAdventures
            width: parent.width * 0.8
            height: parent.height * 0.6
            color: "lightgray"
            anchors.top: lblYourAdvnts.bottom
            anchors.topMargin: 16
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            TableView {
                id:tblUsersAdventures
                anchors.fill: parent
                model: mainUserHandle.usersDoneAdventuresTable
                TableViewColumn {
                    id: colAdventure
                    role: "name"
                    title: "Adventure Name"
                    width: rctUsersAdventures.width * 0.9
                }
                TableViewColumn {
                    id: colAward
                    role: "award"
                    title: "Award"
                    width: rctUsersAdventures.width * 0.099
                }
                onClicked: {
                    console.log("clicked to see adventure " + currentRow)

                    ///Translate advnture status
                    var canInit
                    switch (model[currentRow].status) {
                    case 1:
                        canInit = true
                        break
                    case 2:
                        canInit = false
                        break
                    default:
                        console.log("Unsupported status!")
                    }
                    stackView.push({ item: Qt.resolvedUrl("../Views/SeeAdventure.qml") ,
                                       properties: { "ownerUserLogin"  : mainUserHandle.login,
                                           "thisAdventureName"  :   model[currentRow].name,
                                           "thisAdventureDesc"  :   model[currentRow].desc,
                                           "thisAdventureClue"  :   model[currentRow].clue,
                                           "thisAdventureAward" :   model[currentRow].award,
                                           "canInit"            :   canInit,
                                           "isOwner"            :   true,
                                           "thisAdventureId"    :   model[currentRow].adventureId}})
                    stackView.currentItem.closeForm.connect(stackView.backForm)
                }
            }

            Button {
                id: cancelButton
                anchors.top: rctUsersAdventures.bottom
                anchors.topMargin: 55
                width: parent.width * 0.24
                height: Screen.height * 0.05
                text: qsTr("Close")
                anchors.right: rctUsersAdventures.right
                anchors.rightMargin: 0
                onClicked: closeForm()
            }
        }
    }
}

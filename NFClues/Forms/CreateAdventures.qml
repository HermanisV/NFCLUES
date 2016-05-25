import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import NFCAdventure 0.1
Flickable{
    signal closeForm()
    signal createdAdventure()
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
        id: createAdvMain
        anchors.fill: parent
        color: "lightgray"

        Text {
            id: lblYourAdvnts
            anchors.top: parent.top
            anchors.topMargin: 15
            text: qsTr("Create an adventure")
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            font.pixelSize: 32
        }
        Rectangle {
            id: regFormRectl
            width: parent.width * 0.8
            height: parent.height * 0.6
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            color: "lightgray"
            anchors.top: lblYourAdvnts.bottom
            anchors.topMargin: 16

            Column {
                id: advntCols
                anchors.fill:parent
                anchors.margins: 5
                spacing: 12
                Rectangle{
                    id: rctnAdvntName
                    width: parent.width
                    height: advntName.height + 6
                    TextField {
                        id: advntName
                        width: parent.width
                        maximumLength: 64
                        anchors.fill: parent
                        font.pixelSize: 22
                        anchors.margins: 3
                        //verticalCenter: parent.verticalCenter
                        placeholderText: "Adventure name"
                    }
                }
                Rectangle{
                    id:rctAdvntDesc
                    width: parent.width
                    height: parent.height * 0.4
                    TextArea {
                        id: advntDesc
                        anchors.fill: parent
                        text: qsTr("Description")
                        font.pixelSize:22
                    }
                }
                Rectangle{
                    id:rctAdvntClue
                    width: parent.width
                    height: parent.height * 0.35
                    TextArea {
                        id: advntClue
                        anchors.fill: parent
                        text: qsTr("Clue")
                        font.pixelSize:22
                    }
                }
                Rectangle{
                    id:rctAdvntReward
                    width: parent.width
                    height: 35
                    color: "lightgray"
                    Label {
                        id: lblReward
                        height: parent.height
                        font.pixelSize: 32
                        text: qsTr("Reward")
                        verticalAlignment: Text.AlignVCenter
                        anchors.right: advntReward.left
                        anchors.rightMargin: 36
                    }
                    TextField {
                        id: advntReward
                        width: parent.width * 0.25
                        height: parent.height
                        anchors.rightMargin: 2
                        validator: IntValidator{}
                        placeholderText: "100"
                        anchors.right: lblPts.left
                        font.pixelSize:24
                    }
                    Label {
                        id: lblPts
                        height: parent.height + 4
                        font.pixelSize: 18
                        text: qsTr("pts")
                        verticalAlignment: Text.AlignBottom
                        anchors.right: parent.right
                    }
                }

            }
        }
        RowLayout {
            id: btnRow
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            anchors.top: regFormRectl.bottom
            anchors.topMargin: 55
            width: regFormRectl.width
            height: Screen.height * 0.05

            Button {
                id: cancelButton
                Layout.fillHeight: true
                Layout.minimumWidth: parent.width * 0.24
                text: qsTr("Cancel")
                onClicked: closeForm()
            }

            Button {
                id: clearButton
                Layout.fillHeight: true
                Layout.minimumWidth: parent.width * 0.24
                text: qsTr("Clear")
                onClicked: {
                    advntReward.text = ""
                    advntClue.text = ""
                    advntDesc.text = ""
                    advntName.text = ""
                }
            }

            Button {
                id: btnLogin
                Layout.fillHeight: true
                Layout.minimumWidth: parent.width * 0.5
                text: qsTr("Confirm")
                onClicked: {
                    console.log("Clicked confirm")
                    thisAdvendture.name  = advntName.text
                    thisAdvendture.desc  = advntDesc.text
                    thisAdvendture.clue  = advntClue.text
                    thisAdvendture.award = advntReward.text
                    thisAdvendture.createNewAdventure(mainUserHandle.userId)
                    mainUserHandle.addAdventureToList(thisAdvendture.adventureId, thisAdvendture.name, thisAdvendture.award, 1,thisAdvendture.desc, thisAdvendture.clue)
                    createdAdventure()
                }
            }
        }
    }
}

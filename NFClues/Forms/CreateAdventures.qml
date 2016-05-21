import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2


Rectangle {
    property int mainUserid
    property int mainUserPoints
    id: createAdvMain
    width: Screen.width * 0.7
    height: Screen.height
    color: "lightgray"

    Text {
        id: lblYourAdvnts
        y: 45
        anchors.top: parent.top
        anchors.topMargin: 15
        text: qsTr("Create an adventure")
        anchors.left: parent.left
        anchors.leftMargin: 65
        font.pixelSize: 32
    }
    Rectangle {
        id: regFormRectl
        width: parent.width * 0.9
        height: parent.height * 0.7
        color: "lightgray"
        anchors.top: parent.top
        anchors.topMargin: 65
        anchors.left: parent.left
        anchors.leftMargin: 65

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
                    //verticalCenter: parent.verticalCenter
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

    Button {
        id: btnRegUser
        x: regFormRectl.x
        y: parent.height * 0.8
        width: parent.width  * 0.9
        height: Screen.height * 0.05
        text: qsTr("Confirm")
        onClicked: {
            console.log("Clicked confirm")
        }
    }
}

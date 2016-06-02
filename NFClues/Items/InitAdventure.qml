import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1

Flickable{
    signal closeForm()
    property int    thisAdventureId

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
            id: initAdv
            color: "lightgray"
            width: parent.width * 0.8
            height: parent.height * 0.7
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            ColumnLayout {
                id: initTab
                spacing: 5
                width: parent.width
                height: parent.height * 0.6
                Rectangle{
                    id: tagRect
                    Layout.minimumWidth:parent.width
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                    Label {
                        id: tagIdLabel
                        font.pixelSize: 36
                        text: qsTr("Your tag Id")
                        anchors.verticalCenter: tagId.verticalCenter
                    }

                    TextField {
                        id: tagId
                        width: parent.width * 0.8
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        maximumLength: 40
                        font.pixelSize: 36
                        text:thisAdvendture.getRandomTagId()
                        validator: IntValidator{}
                        readOnly: true
                    }
                }

                Rectangle{
                    id: latRec
                    Layout.minimumWidth:parent.width
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                    Label {
                        id: latLabel
                        font.pixelSize: 36
                        text: qsTr("Adventure lattitude")
                        anchors.verticalCenter: tagLat.verticalCenter
                    }
                    TextField {
                        id: tagLat
                        maximumLength: 40
                        width: parent.width * 0.6
                        anchors.right: parent.right
                        Layout.minimumWidth:parent.width * 0.8
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        font.pixelSize: 36
                        placeholderText: "50.0000"
                        validator: DoubleValidator{}
                    }
                }


                Rectangle{
                    id: longRec
                    Layout.minimumWidth:parent.width
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                    Label {
                        id: longLabel
                        font.pixelSize: 36
                        text: qsTr("Adventure longitude")
                        anchors.verticalCenter: tagLong.verticalCenter
                    }
                    TextField {
                        id: tagLong
                        maximumLength: 40
                        width: parent.width * 0.6
                        anchors.right: parent.right
                        Layout.minimumWidth:parent.width * 0.8
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        font.pixelSize: 36
                        placeholderText: "50.0000"
                        validator: DoubleValidator{}
                    }
                }
            }

            RowLayout {
                id: btnRow
                anchors.top: initAdv.bottom
                anchors.topMargin: 55
                width: initAdv.width
                height: Screen.height * 0.05

                Button {
                    id: cancelButton
                    Layout.fillHeight: true
                    Layout.minimumWidth: parent.width * 0.24
                    text: qsTr("Cancel")
                    onClicked: closeForm()
                }
                Button {
                    id: btnLogin
                    Layout.fillHeight: true
                    Layout.minimumWidth: parent.width * 0.75
                    text: qsTr("Confirm")
                    onClicked: {
                        console.log("Clicked init")
                        thisAdvendture.initAdventure(thisAdventureId, tagId.text, tagLat.text, tagLong.text)
                        thisAdvendture.addAdventureOnMap(thisAdventureId)
                        closeForm()
                    }
                }
            }
        }
    }
}

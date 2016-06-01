import QtQuick 2.2
import QtQuick.Controls 1.2
import NFCTag 0.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2

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
        id: manualNfcWriteRect
        anchors.fill: parent
        color: "lightgray"
        Rectangle{
            id: manualTagRct
            width: parent.width * 0.8
            height: parent.height * 0.4
            color: "lightgray"
            anchors.top: manualNfcWriteRect.top
            anchors.topMargin: 16
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1

            TextField {
                id: tagidtext
                width: parent.width * 0.8
                height: Screen.height * 0.07
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.1
                font.pixelSize: 36
                validator: DoubleValidator{}
                maximumLength: 7
            }

            Label {
                id: yourTagLbl
                x: 0
                y: 52
                font.pixelSize: 36
                text: qsTr("Your Tag Id: ")
                anchors.right: tagidtext.left
                anchors.rightMargin: 0
                anchors.verticalCenter: tagidtext.verticalCenter
            }
        }

        RowLayout {
            id: btnRow
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            anchors.top: manualTagRct.bottom
            anchors.topMargin: 55
            width: manualTagRct.width
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
                    tagidtext.text = ""
                }
            }

            Button {
                id: btnLogin
                Layout.fillHeight: true
                Layout.minimumWidth: parent.width * 0.5
                text: qsTr("Confirm")
                onClicked: {                    
                    thisTag.addText(tagidtext.text)
                    if (thisTag.tagOk){
                        thisTag.startWriting()
                    }
                }
            }
        }
    }
}

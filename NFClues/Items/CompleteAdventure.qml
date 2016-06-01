import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtPositioning 5.2
import QtLocation 5.6
import QtQuick.Window 2.0

Rectangle{
    id: completeRct
    width: 400
    height: 170
    color: "transparent"
    Text {
        id: titleText
        text: "Complete Adventure!"
        anchors.top: parent.top
        anchors.topMargin: 16
        font.pointSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
    }

    TextField {
        id: completeTagText
        width: 230
        anchors.top: titleText.bottom
        anchors.topMargin: 24
        anchors.right: titleText.right
        anchors.rightMargin: 0
        font.pointSize: 16
        validator: IntValidator{}
        maximumLength: 7
    }

    Text {
        id: text1
        x: 50
        text: qsTr("Tag Id:")
        anchors.top: completeTagText.top
        anchors.topMargin: 0
        anchors.right: completeTagText.left
        anchors.rightMargin: 2
        anchors.verticalCenter: completeTagText.verticalCenter
        font.pointSize: 16
    }

    Button {
        id: accButton
        text: qsTr("Accept")
        width: titleText.width * 0.6
        anchors.top: completeTagText.bottom
        anchors.topMargin: 24
        anchors.right: titleText.right
        anchors.rightMargin: 0
    }

    Button {
        id: cancButton
        width: titleText.width * 0.3
        text: qsTr("Close")
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.left: titleText.left
        anchors.top: accButton.top
    }
}

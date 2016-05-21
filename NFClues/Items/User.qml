import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2


Rectangle {
    property string mainUserLogin
    property int mainUserPlace
    property int mainUserPoints
    id: usrOverview
    width: Screen.width * 0.7
    color: "lightgray"
        Rectangle{
            id: fillPic
            x: 70
            y: 55
            color: "Red"
            width: 80
            height: 80
            anchors.left: parent.left
            anchors.leftMargin: 65
            anchors.top: parent.top
            anchors.topMargin: 45
        }

        Text {
            id: usrLogin
            x: 151
            y: 45
            anchors.top: parent.top
            anchors.topMargin: 45
            text: mainUserLogin
            font.pixelSize: 42
        }

        Text {
            id: usrPoints
            x: 70
            y: 210
            text: (qsTr("Your points: ") + mainUserPoints)
            font.pixelSize: 36
        }

        Text {
            id: usrPlace
            x: 70
            y: 272
            text: (qsTr("Which places you: ") + mainUserPlace)
            font.pixelSize: 36
        }
}

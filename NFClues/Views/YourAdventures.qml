import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2


Rectangle {
    property int mainUserid
    property int mainUserPlace
    property int mainUserPoints
    id: advMain
    width: Screen.width * 0.7
    height: Screen.height
    color: "lightgray"

    Text {
        id: lblYourAdvnts
        y: 45
        anchors.top: parent.top
        anchors.topMargin: 41
        text: qsTr("Your adventures: ")
        anchors.left: parent.left
        anchors.leftMargin: 65
        font.pixelSize: 42
    }
    ListView{
        id:lstLeaders
    }
}

import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2


Flickable{
    signal closeForm()
    signal createdAdventure()
    property bool userOK: false
    property string mainUserLogin
    property int mainUserPlace
    property int mainUserPoints

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
        id: userMain
        anchors.fill: parent
        color: "lightgray"
    Rectangle {
        id: usrOverview
        width: parent.width * 0.8
        height: parent.height * 0.7
        color: "lightgray"
        anchors.top: parent.top
        anchors.topMargin: 16
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.1
        Rectangle{
            id: fillPic
            color: "Red"
            width: 160
            height: 160
        }
        Text {
            id: usrLogin
            text: mainUserLogin
            font.bold: true
            anchors.verticalCenter: fillPic.verticalCenter
            anchors.left: fillPic.right
            anchors.leftMargin: 32
            font.pixelSize: 42
        }
        ColumnLayout{
            id: userCols
            anchors.top: fillPic.bottom
            anchors.topMargin: 32

            Text {
                id: usrPoints
                text: (qsTr("Your points: ") + mainUserPoints)
                font.pixelSize: 36
            }

            Text {
                id: usrPlace
                text: (qsTr("Which places you: ") + mainUserPlace)
                font.pixelSize: 36
            }
        }
        Button {
            id: cancelButton
            anchors.top: usrOverview.bottom
            anchors.topMargin: 55
            width: parent.width * 0.24
            height: Screen.height * 0.05
            text: qsTr("Close")
            anchors.right: usrOverview.right
            anchors.rightMargin: 0
            onClicked: closeForm()
        }
    }
    }
}

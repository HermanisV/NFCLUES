import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("NFClues")
    //Props
    property string btnCommitMessage: "Loged On"
    property bool userOK: false

    visible: true
    width:  Screen.width
    height: Screen.height

    menuBar: MenuBar {
        id: mnbmainMenu
        Menu {            
            title: qsTr("File")
            MenuItem {

                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
    // Problem with determining proper height of flcmain
    // Since manuBare height cannot be read
    // so top of flcmain will be overlaid with mnbmainMenu, for now.
    // Take this into account when mapping in this element
    Flickable {
        id: flcmain
        //anchors.left: parent
        boundsBehavior: Flickable.StopAtBounds
        width:  Screen.width
        height: Screen.height
        contentHeight: Screen.height
        contentWidth: Screen.width * 1.75
        SideForm {
            x: Screen.width *0.95
            y: 0
            //btnCommit.onClicked: messageDialog.show(btnCommitMessage)
            //btnCommitText: "Login"
        }
    }
    MessageDialog {
        id: messageDialog
        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }


}

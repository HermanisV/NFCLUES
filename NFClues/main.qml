import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("NFClues")
    //Props
    property string btnCommitMessage: "Loged On"

    visible: true
    width:  Screen.width
    height: Screen.height

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Flickable {
        anchors.left: parent
        boundsBehavior: Flickable.StopAtBounds
        width:  Screen.width
        height: Screen.height
        contentHeight: Screen.height
        contentWidth: Screen.width * 1.75

        SideForm {
            x: Screen.width *0.95
            y: 0
            btnCommit.onClicked: messageDialog.show(btnCommitMessage)
            btnCommitText: "Login"
        }
    }
    MessageDialog {
        // @disable-check M16
        id: messageDialog
        //title: "Done"
        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }


}

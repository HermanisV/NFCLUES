import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2

Rectangle {
    id: logFormRectl
    width: Screen.width * 0.7
    color: "lightgray"
    ColumnLayout {
        id: loginTab
        width: 720
        height: parent.height * 0.2
        anchors.left: parent.left
        anchors.leftMargin: 65
        anchors.top: parent.top
        anchors.topMargin: 45
        TextField {
            id: logUserLogin
            Layout.fillWidth: true
            maximumLength: 40
            width: 420
            height: 35
            font.pixelSize: 36
            placeholderText: "Username"
        }

        TextField {
            id: logUserPassword
            Layout.fillWidth: true
            maximumLength: 40
            width: parent.width
            height: 35
            font.pixelSize: 36
            placeholderText: "Password"
            echoMode: TextInput.PasswordEchoOnEdit
        }
    }

    Button {
        id: btnLogUser
        x: loginTab.x
        y: parent.height * 0.7
        width: loginTab.width
        height: Screen.height * 0.05
        text: qsTr("Login")
        onClicked: {
            mainUserHandle.loginUser(logUserLogin.text,logUserPassword.text);
        }
    }
}

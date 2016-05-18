import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2

Rectangle {
    id: regFormRectl
    width: Screen.width * 0.5
    color: "lightgray"
    ColumnLayout {
        id: registerTab
        width: 720
        height: parent.height * 0.4
        anchors.left: parent.left
        anchors.leftMargin: 65
        anchors.top: parent.top
        anchors.topMargin: 45
        TextField {
            id: userLogin
            Layout.fillWidth: true
            maximumLength: 40
            width: 420
            height: 35
            font.pixelSize: 36
            placeholderText: "Username"
        }

        TextField {
            id: userEmail
            Layout.fillWidth: true
            maximumLength: 40
            width: parent.width
            height: 35
            font.pixelSize: 36
            placeholderText: "Email"
        }

        TextField {
            id: userPassword
            Layout.fillWidth: true
            maximumLength: 40
            width: parent.width
            height: 35
            font.pixelSize: 36
            placeholderText: "Password"
            echoMode: TextInput.PasswordEchoOnEdit
        }
        TextField {
            id: userPasswordRepeat
            Layout.fillWidth: true
            maximumLength: 40
            width: parent.width
            height: 35
            font.pixelSize: 36
            placeholderText: "Password again"
            echoMode: TextInput.PasswordEchoOnEdit
        }
    }

    Button {
        id: btnRegUser
        x: registerTab.x
        y: parent.height * 0.7
        width: registerTab.width
        height: Screen.height * 0.05
        text: qsTr("Register")
        onClicked: {
            mainUserHandle.login = userLogin.text
            mainUserHandle.email = userEmail.text
            mainUserHandle.password = userPassword.text
            mainUserHandle.createNewUser();
            console.log("back from create new user")
        }
    }
}

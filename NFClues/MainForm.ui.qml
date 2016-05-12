import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.2
import QtTest 1.1

Item {
    id: itmNewUser
    width: 360
    height: 480
    property alias txtPasswordRepeat: txtPasswordRepeat
    property alias btnNewUser: btnNewUser

    Rectangle {
        id: rctMain
        x: 0
        y: 0
        width: 380
        height: parent.height
        color: "lightgray"

        Rectangle {
            id: rctUserName
            x: 130
            y: 14
            width: 240
            height: 20
            color: "white"
            border.color: "black"
            border.width: 1

            TextInput {
                id: txtUserName
                maximumLength: 64
                autoScroll: true
                clip: true
                anchors {
                fill: parent
                leftMargin: 2
                topMargin: 2
                }
            }
        }

        Rectangle {
            id: rctEmail
            x: 130
            y: 40
            width: 240
            height: 20
            color: "white"
            border.color: "black"
            border.width: 1

            TextInput {
                id: txtEmail
                maximumLength: 64
                autoScroll: true
                clip: true
                anchors {
                fill: parent
                leftMargin: 2
                topMargin: 2
                }
            }
        }

        Rectangle {
            id: rctPasswrod
            x: 130
            y: 66
            width: 240
            height: 20
            color: "white"
            border.color: "black"
            border.width: 1

            TextInput {
                id: txtPassword
                echoMode: TextInput.Password
                maximumLength: 64
                autoScroll: true
                clip: true
                anchors {
                fill: parent
                leftMargin: 2
                topMargin: 2
                }
            }
        }

        Rectangle {
            id: rctPasswordRepeat
            x: 130
            y: 92
            width: 240
            height: 20
            color: "white"
            border.color: "black"
            border.width: 1

            TextInput {
                id: txtPasswordRepeat
                echoMode: TextInput.Password
                maximumLength: 64
                autoScroll: true
                clip: true
                anchors {
                fill: parent
                leftMargin: 2
                topMargin: 2
                }
                onTextChanged:  {
                    if (txtPasswordRepeat.text != txtPassword.text){
                        rctPasswordRepeat.color = 'red';
                    } else {
                        rctPasswordRepeat.color = 'white';
                    }
                }
            }
        }

        Label {
            id: lblUserName
            x: 19
            y: 16
            width: 58
            height: 16
            text: qsTr("User Name")
        }

        Label {
            id: lblEmail
            x: 19
            y: 42
            width: 58
            height: 16
            text: qsTr("Email")
        }

        Label {
            id: lblPassword
            x: 19
            y: 68
            width: 58
            height: 16
            text: qsTr("Password")
        }

        Label {
            id: lblPasswordRepeat
            x: 19
            y: 94
            width: 58
            height: 16
            text: "Password Repeat"
            wrapMode: Text.NoWrap
        }
        Button {
            id: btnNewUser
            x: 282
            y: 127
            text: qsTr("Create new user")
            enabled: true
        }
    }
}

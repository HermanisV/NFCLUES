import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2
Flickable{
    signal closeForm()
    signal gotLogin()
    property bool userOK: false

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
        id: logFormRectl
        anchors.fill: parent
        color: "lightgray"
        ColumnLayout {
            id: loginTab
            width: parent.width * 0.8
            spacing: 35
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            anchors.top: parent.top
            anchors.topMargin: 45
            TextField {
                id: logUserLogin
                Layout.fillWidth: true
                maximumLength: 40
                height: Screen.height * 0.07
                font.pixelSize: 36
                placeholderText: "Username"
            }

            TextField {
                id: logUserPassword
                Layout.fillWidth: true
                maximumLength: 40
                height: Screen.height * 0.07
                font.pixelSize: 36
                placeholderText: "Password"
                echoMode: TextInput.PasswordEchoOnEdit
            }
        }

        RowLayout {
            id: btnRow
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            anchors.top: loginTab.bottom
            anchors.topMargin: 55
            width: loginTab.width
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
                    logUserLogin.text = ""
                    logUserPassword.text = ""
                }
            }

            Button {
                id: btnLogin
                Layout.fillHeight: true
                Layout.minimumWidth: parent.width * 0.5
                text: qsTr("Login")
                onClicked: {
                    isLoading = true
                    mainUserHandle.loginUser(logUserLogin.text,logUserPassword.text);
                    if (mainUserHandle.userOK){
                        isLoading = false
                        gotLogin()
                    }
                    isLoading = false
                }
            }
        }
    }
}

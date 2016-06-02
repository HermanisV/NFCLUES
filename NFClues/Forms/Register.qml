import QtQuick 2.0
import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import NFCUser 0.1
import QtQuick.Dialogs 1.2

Flickable{
    signal closeForm()
    signal gotLogin()
    signal gotError()
    property bool userOK: false
    property string errorText

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

        id: regFormRectl
        width: Screen.width
        height: Screen.height
        color: "lightgray"
        ColumnLayout {
            id: registerTab
            width: parent.width * 0.8
            spacing: 35
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            anchors.top: parent.top
            anchors.topMargin: 45
            TextField {
                id: userLogin
                Layout.fillWidth: true
                maximumLength: 40
                height: Screen.height * 0.07
                font.pixelSize: 36
                placeholderText: "Username"
            }

            TextField {
                id: userEmail
                Layout.fillWidth: true
                maximumLength: 40
                width: parent.width
                height: Screen.height * 0.07
                font.pixelSize: 36
                placeholderText: "Email"
            }

            TextField {
                id: userPassword
                Layout.fillWidth: true
                maximumLength: 40
                width: parent.width
                height: Screen.height * 0.07
                font.pixelSize: 36
                placeholderText: "Password"
                echoMode: TextInput.Password
            }
            TextField {
                id: userPasswordRepeat
                Layout.fillWidth: true
                maximumLength: 40
                width: parent.width
                height: Screen.height * 0.07
                font.pixelSize: 36
                placeholderText: "Password again"
                echoMode: TextInput.Password
            }
        }
        RowLayout {
            id: btnRow
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.1
            anchors.top: registerTab.bottom
            anchors.topMargin: 55
            width: registerTab.width
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
                    userLogin.text = ""
                    userEmail.text = ""
                    userPassword.text = ""
                    userPasswordRepeat.text = ""
                }
            }

            Button {
                id: btnLogin
                Layout.fillHeight: true
                Layout.minimumWidth: parent.width * 0.5
                text: qsTr("Register")
                onClicked: {
                    if (userPassword.text != userPasswordRepeat.text){
                      errorDialog.showError("Passwords must match")
                    }
                    else{
                        mainUserHandle.login = userLogin.text
                        mainUserHandle.email = userEmail.text
                        mainUserHandle.password = userPassword.text
                        mainUserHandle.createNewUser();
                        if (mainUserHandle.userOK){
                            gotLogin()
                        }
                    }
                }
            }
        }
    }
}

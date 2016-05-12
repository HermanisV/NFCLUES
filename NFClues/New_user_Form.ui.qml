import QtQuick 2.4
import QtQuick.Window 2.0
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.2

Item {
    id: item1
    width: 400
    height: 400

    Rectangle {
        width: parent.width
        height: parent.height

        TextInput {
            id: txtUserName
            x: 84
            y: 8
            width: 80
            height: 20
            font.family: "Verdana"
            font.pixelSize: 12
        }

        TextInput {
            id: txtEmail
            x: 84
            y: 44
            width: 80
            height: 20
            font.pixelSize: 12
        }

        TextInput {
            id: txtPassword
            x: 84
            y: 77
            width: 80
            height: 20
            font.pixelSize: 12
        }

        TextInput {
            id: txtPasswordRepeat
            x: 84
            y: 109
            width: 80
            height: 20
            font.pixelSize: 12
        }
    }
}

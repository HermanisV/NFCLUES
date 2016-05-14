import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    width: Screen.width * 0.8
    height: Screen.height
    anchors.left: parent

    property string btnCommitText : "Login"
    property alias btnCommit: btnCommit

    Rectangle {
        id: rectangle1
        width: Screen.width * 0.8
        height: parent.height
        color: "lightgray"

        Button {
            id: btnCommit
            x: parent.width * 0.65
            y: parent.height *  0.75
            width: parent.width * 0.30
            height: parent.height * 0.10
            text: btnCommitText
        }

    }
}

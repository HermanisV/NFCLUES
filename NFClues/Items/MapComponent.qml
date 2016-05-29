import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.6
Map {
    //props
    property int lastX : -1
    property int lastY : -1
    property int pressX : -1
    property int pressY : -1
    property int threshold : 30
    property variant location: QtPositioning.coordinate( 59.93, 10.76)
    //Signals
    signal coordinatesCaptured(double latitude, double longitude)
    signal showPopupMenu(variant coordinate)
    id: map
    center: locationOslo
    zoomLevel: 13

    MouseArea {
        id: mouseArea
        property variant lastCoordinate
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onPressed : {
            map.lastX = mouse.x
            map.lastY = mouse.y
            map.pressX = mouse.x
            map.pressY = mouse.y
            lastCoordinate = map.toCoordinate(Qt.point(mouse.x, mouse.y))   //Translates to Lat Long
        }

        onPositionChanged: {
            if (mouse.button == Qt.LeftButton) {
                map.lastX = mouse.x
                map.lastY = mouse.y
            }
        }
        onPressAndHold:{
            if (Math.abs(map.pressX - mouse.x ) < map.threshold
                    && Math.abs(map.pressY - mouse.y ) < map.threshold) {
                showPopupMenu(lastCoordinate);  //Send popup up to Main and showmenu
            }
        }
    }
}

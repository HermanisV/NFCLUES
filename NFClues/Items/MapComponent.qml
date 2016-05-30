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
    property variant defaultLocation: QtPositioning.coordinate( 56.8965, 24.1436)
    property variant adventuresOnMapModel
    //Signals
    signal coordinatesCaptured(double latitude, double longitude)
    signal showPopupMenu(variant coordinate)
    id: map
    zoomLevel: 13
    center: defaultLocation

    //
    PositionSource {
        id: positionSource
        active: true
        updateInterval: 30000 // 30 sec
        onPositionChanged:  {
            var currentPosition = positionSource.position.coordinate
            map.center = currentPosition
        }
    }
    //
    //View for all adventures
    MapItemView {
        model:thisAdvendture.adventuresOnMap
        delegate: pointerDelegate
    }
    //Delegata for building pinters
    Component {
        id: pointerDelegate
        MapQuickItem {
            coordinate: QtPositioning.coordinate(50,50)
            //Anhors pointer right in the middle of bottom
            anchorPoint.x: image.width * 0.5
            anchorPoint.y: image.height

            sourceItem: Column {
                Image { id: image; source: "../Resources/marker.png" }
                Text { text: "wa waa"; font.bold: true }
            }
        }
    }
    MapQuickItem {
        coordinate: QtPositioning.coordinate(56.310,26.191406)
        //Anhors pointer right in the middle of bottom
        anchorPoint.x: image.width * 0.5
        anchorPoint.y: image.height

        sourceItem: Column {
            Image { id: image; source: "../Resources/marker.png" }
            Text { text: "wa waa"; font.bold: true }
        }
    }
    //Mouse area for all
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

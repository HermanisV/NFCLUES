import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.6

Rectangle {
    width: 360
    height: 640

    // [Initialize Plugin]
    Plugin {
        id: mapPlugin
        name: "osm"
    }

    // [Current Location]
    PositionSource {
        id: positionSource
        property variant lastSearchPosition: locationNfcHome
        active: true
        updateInterval: 120000 // 2 mins
        onPositionChanged:  {
            var currentPosition = positionSource.position.coordinate
            map.center = currentPosition
            var distance = currentPosition.distanceTo(lastSearchPosition)
            if (distance > 500) {
                // 500m from last performed pizza search
                lastSearchPosition = currentPosition
                searchModel.searchArea = QtPositioning.circle(currentPosition)
                searchModel.update()
            }
        }
    }

    property variant locationNfcHome: QtPositioning.coordinate( 56.941488, 24.060093)

    // [Places MapItemView]
    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin;
        center: locationNfcHome
        zoomLevel: 13

//        MapItemView {
//            model: searchModel
//            delegate: MapQuickItem {
//                coordinate: place.location.coordinate

//                anchorPoint.x: image.width * 0.5
//                anchorPoint.y: image.height

//                sourceItem: Column {
//                    Image { id: image; source: "/Items/marker.png" }
//                    Text { text: title; font.bold: true }
//                }
//            }
//        }
    }
}

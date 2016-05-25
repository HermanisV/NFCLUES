import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.6

//    PositionSource {
//        id: positionSource
//        property variant lastSearchPosition: locationOslo
//        active: true
//        updateInterval: 120000 // 2 mins
//        onPositionChanged:  {
//            var currentPosition = positionSource.position.coordinate
//            map.center = currentPosition
//            var distance = currentPosition.distanceTo(lastSearchPosition)
//            if (distance > 500) {
//                // 500m from last performed pizza search
//                lastSearchPosition = currentPosition
//                searchModel.searchArea = QtPositioning.circle(currentPosition)
//                searchModel.update()
//            }
//        }
//    }

Map {
    property variant locationOslo: QtPositioning.coordinate( 59.93, 10.76)
    id: map
    center: locationOslo
    zoomLevel: 13

    //        MapItemView {
    //            model: searchModel
    //            delegate: MapQuickItem {
    //                coordinate: place.location.coordinate

    //                anchorPoint.x: image.width * 0.5
    //                anchorPoint.y: image.height

    //                sourceItem: Column {
    //                    Image { id: image; source: "marker.png" }
    //                    Text { text: title; font.bold: true }
    //                }
    //            }
    //        }
}

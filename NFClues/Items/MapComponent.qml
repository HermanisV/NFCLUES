import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.6
import AdventureOnMap 0.1

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
    //View for all adventures
    MapItemView {
        model: thisAdvendture.adventuresOnMap
        delegate: MapQuickItem {
            coordinate: QtPositioning.coordinate(geoLat,geoLong)
            //Anhors pointer right in the middle of bottom
            anchorPoint.x: image.width * 0.5
            anchorPoint.y: image.height

            sourceItem: Column {
                Image {
                    id: image;
                    source: "../Resources/marker.png"
                }
                Text { text: name;
                        font.bold: true
                }
            }
            //On click area on top of pointer
            MouseArea{
                id: mapItemMouse
                height: image.height * 2
                width: image.width * 2
                onClicked: {                    
                    console.log("Clicked adventure " + adventureId)
                    ///Translate user role
                    var isAdmin
                    switch (mainUserHandle.role) {
                    case 1:
                        isAdmin = false
                        break
                    case 2:
                        isAdmin = true
                        break
                    default:
                        console.log("Unsupported status!")
                    }
                    //Open this adventures page
                    //Vibrator.vibrate(100)//currently crashing the app
                    stackView.push({ item: Qt.resolvedUrl("../Views/SeeAdventure.qml") ,
                                       properties: { "ownerUserLogin"  : "Login",
                                           "thisAdventureName"  :   name,
                                           "thisAdventureDesc"  :   description,
                                           "thisAdventureClue"  :   clue,
                                           "thisAdventureAward" :   award,
                                           "thisAdventureInit"  :   true,
                                           "isAdmin"            :   isAdmin,
                                           "fromMap"            :   true}})
                    stackView.currentItem.closeForm.connect(stackView.backForm)
                }
            }
        }
    }
    //Mouse area for all
    MapQuickItem{
        coordinate: positionSource.position.coordinate
        //Anhors pointer right in the middle of bottom
        anchorPoint.x: hereImage.width * 0.5
        anchorPoint.y: hereImage.height

        sourceItem: Column {
            Image {
                id: hereImage;
                source: "../Resources/android-logo.png"
            }
        }
    }

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
        onDoubleClicked:{
            if (Math.abs(map.pressX - mouse.x ) < map.threshold
                    && Math.abs(map.pressY - mouse.y ) < map.threshold) {
                showPopupMenu(lastCoordinate);  //Send popup up to Main and showmenu
            }
        }
    }
}

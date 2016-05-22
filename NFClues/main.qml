import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtPositioning 5.2
import QtLocation 5.6
import QtQuick.Window 2.0
import NFCUser 0.1
import QtQuick.Dialogs 1.2
import "Items"

ApplicationWindow {
    id: applicationWindow1
    title: qsTr("NFClues")
    //Props
    property string btnCommitMessage: "Loged On"
    property bool userOK: false

    visible: true
    width:  Screen.width
    height: Screen.height

    menuBar: MenuBar {
        id: mnbmainMenu
        Menu {
            title: qsTr("File")
            MenuItem {

                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
    //Map
    // Problem with determining proper height of flcmain
    // Since manuBare height cannot be read
    // so top of flcmain will be overlaid with mnbmainMenu, for now.
    // Take this into account when mapping in this element
    Flickable {
        id: flcmain
        boundsBehavior: Flickable.StopAtBounds
        width:  Screen.width
        height: Screen.height
        contentHeight: Screen.height
        contentWidth: Screen.width * 1.75
        Rectangle{
            x:Screen.width *0.95
            width: Screen.width * 0.75
            height: Screen.height
                SideForm {
                    id: sideformMain
                    anchors.fill: parent
                }
        }
        Rectangle {
            width: Screen.width *0.95
            height: Screen.height
            anchors.left: parent.left
            anchors.leftMargin: 0

            // [Initialize Plugin]
            Plugin {
                id: mapPlugin
                name: "osm"
            }
            //! [Places MapItemView]
            MapComponent{
                width: parent.width
                height: parent.height
            }

        }
    }
    HandleUser{
        id: mainUserHandle
        property bool userOK: false
        property bool loading: false
        onError: {
            console.log("There was an Error: " + errorString)
        }
        onGotLogin: {
            userOK = true
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: false
    }
}

//                onErrorChanged: {
//                    if (map.error != Map.NoError) {
//                        var title = qsTr("ProviderError");
//                        var message =  map.errorString + "<br/><br/><b>" + qsTr("Try to select other provider") + "</b>";
//                        if (map.error == Map.MissingRequiredParameterError)
//                            message += "<br/>" + qsTr("or see") + " \'mapviewer --help\' "
//                                    + qsTr("how to pass plugin parameters.");
//                        stackView.showMessage(title,message);
//                    }

//                MapItemView {
//                    model: placeSearchModel
//                    delegate: MapQuickItem {
//                        coordinate: model.type === PlaceSearchModel.PlaceResult ? place.location.coordinate : QtPositioning.coordinate()

//                        visible: model.type === PlaceSearchModel.PlaceResult

//                        anchorPoint.x: image.width * 0.28
//                        anchorPoint.y: image.height

//                        sourceItem: Image {
//                            id: image
//                            source: "resources/marker.png"
//                            MouseArea {
//                                anchors.fill: parent
//                                onClicked: stackView.showPlaceDatails(model.place,model.distance)
//                            }
//                        }
//                    }
//                }
//    MessageDialog {
//        id: messageDialog
//        function show(caption) {
//            messageDialog.text = caption;
//            messageDialog.open();
//        }
//    }

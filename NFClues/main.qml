import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtPositioning 5.2
import QtLocation 5.6
import QtQuick.Window 2.0
import NFCUser 0.1
import NFCAdventure 0.1
import QtQuick.Dialogs 1.2
import "Items"

ApplicationWindow {
    id: appWindow
    title: qsTr("NFClues")
    //Props
    property bool userOK: false
    property variant map
    //Methods
    function createMap()
    {
        var plugin
            plugin = Qt.createQmlObject ('import QtLocation 5.3; Plugin{ name:"osm"}', appWindow)
        if (map) {
            map.destroy()
        }

        map = mapComponent.createObject(page);
        map.plugin = plugin;
        map.maximumZoomLevel = 16.75       //higher then this and map wont load sometimes
        map.minimumZoomLevel = 3
        map.zoomLevel = (map.maximumZoomLevel - map.minimumZoomLevel)/2
    }

    visible: true
    width:  Screen.width
    height: Screen.height
    menuBar: mainMenu

    MainMenu{
        id: mainMenu
        Component.onCompleted: {
            console.log("compnonent complete")
            actionMenu.createMenu(userOK)
            console.log("creating map")
            createMap()
        }
        onSelectAction: {
            stackView.pop({tem:page,immediate: true})
            switch (action) {
            case "account":
                stackView.pop({item:page, immediate: true})
                stackView.push({ item: Qt.resolvedUrl("Items/User.qml") ,
                                   properties: {"mainUserLogin"  : mainUserHandle.login,
                                       "mainUserPlace"  : mainUserHandle.place,
                                       "mainUserPoints" : mainUserHandle.points}})
                stackView.currentItem.closeForm.connect(stackView.closeForm)
                break
            case "yourAdventures":
                stackView.pop({item:page, immediate: true})
                stackView.push({ item: Qt.resolvedUrl("Views/YourAdventures.qml")})
                stackView.currentItem.closeForm.connect(stackView.closeForm)
                break
            case "createAdventures":
                stackView.pop({item:page, immediate: true})
                stackView.push({ item: Qt.resolvedUrl("Forms/CreateAdventures.qml")})
                stackView.currentItem.closeForm.connect(stackView.closeForm)
                stackView.currentItem.createdAdventure.connect(stackView.openAdventures)
                break
            case "leaderboards":
                stackView.pop({item:page, immediate: true})
                stackView.push({ item: Qt.resolvedUrl("Views/Leaderboards.qml")})
                stackView.currentItem.closeForm.connect(stackView.closeForm)
                break
            case "register":
                stackView.pop({item:page, immediate: true})
                stackView.push({ item: Qt.resolvedUrl("Forms/Register.qml")})
                stackView.currentItem.closeForm.connect(stackView.closeForm)
                stackView.currentItem.gotLogin.connect(stackView.closeForm)
                break
            case "login":
                stackView.pop({item:page, immediate: true})
                stackView.push({ item: Qt.resolvedUrl("Forms/Login.qml")})
                stackView.currentItem.closeForm.connect(stackView.closeForm)
                stackView.currentItem.gotLogin.connect(stackView.closeForm)
                break
            default:
                console.log("Unsupported action!")
            }
        }
    }
    //APP's structure in stackview
    StackView {
        id: stackView
        anchors.fill: parent
        focus: true
        initialItem: Item {
            id: page
        }

        function backForm(backPage)
        {
            pop(backPage)
        }

        function closeForm()
        {
            pop(page)
        }
        function openAdventures()
        {
            stackView.pop({item:page, immediate: true})
            stackView.push({ item: Qt.resolvedUrl("Views/YourAdventures.qml")})
            stackView.currentItem.closeForm.connect(stackView.closeForm)
        }
    }

    //Map
    // Problem with determining proper height of flcmain
    // Since manuBare height cannot be read
    // so top of flcmain will be overlaid with mnbmainMenu, for now.
    // Take this into account when mapping in this element

    Component {
        id: mapComponent
        MapComponent{
            width: page.width
            height: page.height
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
            mainMenu.actionMenu.createMenu(userOK)
        }
    }
    HandleAdventure{
        id: thisAdvendture
        onError: {
            console.log("There was an Error: " + errorString)
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

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtPositioning 5.2
import QtLocation 5.6
import QtQuick.Window 2.0
import NFCTag 0.1
import NFCUser 0.1
import NFCAdventure 0.1
import QtQuick.Dialogs 1.2
import ThisSystem 0.1
import "helper.js" as Helper
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
        map.maximumZoomLevel = 17.5      //higher then this and map wont load tiles sometimes
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
            ////This is INIT
            console.log("compnonent complete")
            actionMenu.createMenu(userOK)
            console.log("Building adventure on MAP")
            thisAdvendture.buildAdventuresOnMap()
            console.log("creating map")
            createMap()
            console.log("Current env: " + thisSystem.getEnv())
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
            case "initTag":
                stackView.pop({item:page, immediate: true})
                stackView.push({ item: Qt.resolvedUrl("Forms/NfcManualWrite.qml")})
                stackView.currentItem.closeForm.connect(stackView.closeForm)
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
        //used to open adventure tab after creation of new adventure
        function openAdventures()
        {
            stackView.pop({item:page, immediate: true})
            stackView.push({ item: Qt.resolvedUrl("Views/YourAdventures.qml")})
            stackView.currentItem.closeForm.connect(stackView.closeForm)
        }
    }

    MapPopup {
        id: mapPopup

        function show(coordinate)
        {
            mapPopup.coordinate = coordinate
            mapPopup.update()
            mapPopup.popup()
        }
        onItemClicked: {
            stackView.pop(page)
            switch (item) {
            case "getCoordinate":
                map.coordinatesCaptured(coordinate.latitude, coordinate.longitude)
                break
            default:
                console.log("Unsupported operation")
            }
        }
    }
    //Map
    // Problem with determining proper height of mapComponent
    // Since manuBare height cannot be read
    // so top of mapComponent will be overlaid with mainMenu, for now.
    // Take this into account when mapping in this element
    Component {
        id: mapComponent
        MapComponent{
            width: page.width
            height: page.height

            onShowPopupMenu: {
                //Show Popup menu with passed current cordi
                mapPopup.show(coordinate)
            }
            onCoordinatesCaptured: {
                //Fills message to be passed for Coordinate view
                var text = "<b>" + qsTr("Latitude:") + "</b> " + Helper.roundNumber(latitude,4) + "<br/><b>" + qsTr("Longitude:") + "</b> " + Helper.roundNumber(longitude,4)
                showCordi.showCordi(text);
            }
        }
    }
    //Qobject from userhandler.h
    HandleUser{
        id: mainUserHandle
        property bool userOK: false
        property bool loading: false
        onError: {
            console.log("There was an Error: " + errorString)
            errorDialog.showError(errorString)
        }
        onGotLogin: {
            userOK = true
            mainMenu.actionMenu.createMenu(userOK)
        }
    }
    //QObject from adventurehandler.h
    HandleAdventure{
        id: thisAdvendture
        property bool adventureOk: false
        onError: {
            console.log("There was an Error: " + errorString)
            errorDialog.showError(errorString)
        }
        onGotAdventure: {
            adventureOk = true
        }
        onGotInit: {
            infoDialog.showInfo("Adventure initialized!")
        }
    }
    //QObject form nfchandler.h
    HandleTag{
        id: thisTag
        property bool tagOk: false
        onError: {
            errorDialog.showError(errorString)
        }
        onTagTextOk: {
            tagOk = true
        }
        onStartedLooking: {
            infoDialog.showInfo("Please place device on the Tag")
        }
        onFoundTarget: {
            infoDialog.autoClose()
        }
        onTagWritten: {
            infoDialog.showInfo("Tag has been written")
        }

    }

    System{
        id: thisSystem
    }

    MessageDialog {
        id: errorDialog
        function showError(caption) {
            errorDialog.text = caption;
            errorDialog.open();
        }
    }
    MessageDialog {
        id: showCordi
        function showCordi(caption) {
            errorDialog.text = caption;
            errorDialog.open();
        }
    }
    MessageDialog {
        id: infoDialog
        function showInfo(caption) {
            infoDialog.text = caption;
            infoDialog.open();
        }
        function autoClose(){
            infoDialog.close();
        }
    }

    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: false
    }
}

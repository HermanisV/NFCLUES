import QtQuick 2.5
import QtQuick.Controls 1.4
import QtLocation 5.6

MenuBar {
    property alias  actionMenu: actionMenu
    signal selectAction(string action);

    Menu {
        id: actionMenu
        title: qsTr("Action")
        function createMenu(isLogin){
            clear()
            if (isLogin){
                var item = addItem(qsTr("Account"));
                item.triggered.connect(function(){selectAction("account")})
                item = addItem(qsTr("Your adventures"));
                item.triggered.connect(function(){selectAction("yourAdventures")})
                item = addItem(qsTr("Create adventures"));
                item.triggered.connect(function(){selectAction("createAdventures")})
                item = addItem(qsTr("Leaderboards"));
                item.triggered.connect(function(){selectAction("leaderboards")})
            }
            else{
                var item2 = addItem(qsTr("Register"));
                item2.triggered.connect(function(){selectAction("register")})
                item2 = addItem(qsTr("Login"));
                item2.triggered.connect(function(){selectAction("login")})
            }
        }

        MenuItem {
            text: qsTr("Exit")
            onTriggered: Qt.quit();
        }
    }
}

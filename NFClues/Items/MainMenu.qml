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
            //Get this system, menu differs between Windows and android
            var sys = thisSystem.getEnv();
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
                if (sys.indexOf("win")>=0){
                var item2 = addItem(qsTr("Register"));
                item2.triggered.connect(function(){selectAction("register")})
                item2 = addItem(qsTr("Login"));
                item2.triggered.connect(function(){selectAction("login")})
                }
                else{
                    var item3 = addItem(qsTr("Writa a tag"));
                    item3.triggered.connect(function(){selectAction("initTag")})
                }
            }
        }

        MenuItem {
            text: qsTr("Exit")
            onTriggered: Qt.quit();
        }
    }
}

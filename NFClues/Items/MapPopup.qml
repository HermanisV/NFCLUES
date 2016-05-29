import QtQuick 2.5
import QtQuick.Controls 1.4

Menu {
    property variant coordinate
    signal itemClicked(string item)

    function update() {
        clear()
        addItem(qsTr("Get coordinate")).triggered.connect(function(){itemClicked("getCoordinate")})
    }
}

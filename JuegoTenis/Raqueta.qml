import QtQuick 2.15

Item {
    id: raqueta
    width   : 20
    height  : 100

    property alias color: rect_raqueta.color

    property int   up   : Qt.Key_Up
    property int   down : Qt.Key_Down

    Rectangle{
        id          : rect_raqueta
        anchors.fill: parent
        color       : "blue"
        border.color: Qt.darker(color)
        border.width: width / 10
    }
}

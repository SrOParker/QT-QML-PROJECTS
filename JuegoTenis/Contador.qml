import QtQuick 2.15

Item {
    id      : contador
    width   : 100
    height  : 60
    property int puntos: 0
    Rectangle{
        id          : rect_contador
        anchors.fill: parent
        color       : "#00000000"
        border.color: "green"
        border.width: 5
        Text{
            id      : contText
            x       : rect_contador.width  / 2 - width  / 2
            y       : rect_contador.height / 2 - height / 2
            text    : contador.puntos
            font.family: "Kalinga"
            font.pointSize   : 30
            font.bold        : true
            horizontalAlignment: horizontalAlignment
        }
    }
}

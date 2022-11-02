import QtQuick 2.15

Item {
    id      : contenedorCelda
    width   : 40
    height  : 25

    property alias colorCelda: rectanguloCelda.color
    signal clicked(colorCelda:color)
    Rectangle{
        id          : rectanguloCelda
        border.color: Qt.darker(color)
        border.width: 2
        anchors.fill: parent
    }

    MouseArea{
        anchors.fill: parent
        onClicked:
            contenedorCelda.clicked(contenedorCelda.colorCelda)
    }
}

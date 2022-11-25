import QtQuick


Item {
    id: boton
    width: 100
    height: 50

    property alias texto: textoBoton.text
    property color color: "#3574B3"
    property alias radius: rectanguloBoton.radius
    signal clicked()

    Rectangle {
        id: rectanguloBoton
        color: boton.color

        radius:  5

        anchors.fill: parent

        Text {
            id: textoBoton

            text: "Boton"

            font.pixelSize: boton.height / 4
            color: Qt.darker(parent.color)
            anchors.centerIn: parent
        }
    }

    MouseArea {
        id: mouseAreaBoton

        anchors.fill: parent

        onPressed: {
            rectanguloBoton.color = Qt.darker(boton.color)
        }

        onReleased: {
            rectanguloBoton.color = boton.color
        }

        onClicked: {
            boton.clicked()
        }
    }
}


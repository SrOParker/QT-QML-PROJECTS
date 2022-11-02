import QtQuick 2.0

Item {
    id:btn
    width: 100
    height: 50

    property alias textoMostrado: textoButton.text

    signal clicked()

    Rectangle{
        id          : boton

        y           : 5
        color       : "green"
        border.color: Qt.darker(color) //un borde del mismo color pero más oscuro
        border.width: 2
        width       : parent.width
        height      : 30

        Text{
            id               : textoButton
            text             : "Boton"
            anchors.fill     : parent
            anchors.centerIn : parent

        }
        MouseArea {
            anchors.fill    : parent
            onClicked:{
                btn.clicked()
                label.cantPresionesBoton++
            }

        }
    }
    Text{
        id:label
        property int cantPresionesBoton
        text: "Boton presionado " + cantPresionesBoton + " veces"
        anchors.horizontalCenter: parent.horizontalCenter
        y: (boton.y+boton.height+10)
        color: Qt.darker(boton.color)
    }
}

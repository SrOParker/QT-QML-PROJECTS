import QtQuick 2.0

Item {
    id:btn
    width: 100
    height: 50
    Rectangle{
        id          : boton
        x           : (parent.width - width) / 2
        y           : 5
        color       : "green"
        border.color: Qt.darker(color) //un borde del mismo color pero más oscuro
        border.width: 2
        width       : parent.width
        height      : 30

        Text{
            id      : textoBoton
            text    : "Boton"
        }
    }
}

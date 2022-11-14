import QtQuick

Item {
    id: item_campo
    property alias color: rectInput.color
    property alias label: nombreLabel.text
    property alias input: inputTe.text
    property alias visibleButton: botonBuscar.visible
    property alias nameButton: botonBuscar.texto
    height: campo1.height
    Rectangle{
        id:campo1
        width: agenda.width
        height: 20
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#00000000"
        Text{
            id: nombreLabel
            text: ""
            height: 20
            anchors.top: parent.top
            anchors.left: parent.left
            verticalAlignment: TextInput.AlignVCenter
            anchors.leftMargin: 5
        }
        Rectangle{
            id: rectInput
            width: agenda.width
            height: 45
            anchors.top: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            radius: 5
            TextInput{
                id: inputTe
                anchors.fill: parent
                verticalAlignment: TextInput.AlignVCenter
                anchors.leftMargin: 5
                font.pixelSize: 20
                anchors.top: nombreLabel.bottom
            }
        }
        BotonClass {

            id: botonBuscar
            anchors.right: parent.right
            anchors.top: rectInput.top
            anchors.bottom: rectInput.bottom
            texto:"button"
            color: Qt.darker(item_campo.color,0.9)
            onClicked: {
                calendario_dialogo.open();
            }
        }


    }
}

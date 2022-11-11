import QtQuick 2.15
import QtQuick.Window 2.15
import "https://gist.githubusercontent.com/marianocossio/3566cc0346678383335594dd2e0fccc2/raw/506b08a94d9b0e0f449527b6b3cf79963bc67ecb/" as BotonGitClass
Window {
    width: 640
    height: 480
    visible: true
    title: "Agenda SQL"

    Rectangle{
        id: agenda
        anchors.fill: parent
        anchors.margins: 5
        color:"#9994AB"
        Rectangle{
            width: agenda.width
            height: 20
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            color: "#9994AB"
            Text{
                id: nombreLabel
                text: "Nombre"
                height: 20
                anchors.top: parent.top
                anchors.left: parent.left
                verticalAlignment: TextInput.AlignVCenter
                anchors.leftMargin: 5
            }
            Rectangle{
                id: rectInput
                width: agenda.width
                height: 50
                anchors.top: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                border.color: "black"
                radius: 5
                TextInput{
                    id:nombre
                    anchors.fill: parent
                    verticalAlignment: TextInput.AlignVCenter
                    anchors.leftMargin: 5
                    anchors.top: nombreLabel.bottom
                }
            }
            BotonGitClass.Boton {
                id: botonBuscar
                anchors.right: parent.right
                anchors.top: rectInput.top
                texto:"BUSCAR"
                onClicked:{
                    Qt.quit();
                }
            }

        }

    }
}

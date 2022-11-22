//Enunciado de la practica --> git Mariano
//Enviar a --> clase001@itcloud-learning.com
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs


Window {
    id: win
    width: 640
    height: 480
    visible: true
    title: "Generador PDF desde plantillas"
    color: "#Bbeafb"
    Rectangle{
        id: firstContainer
        anchors{

            top: menubar.bottom
            bottom: parent.bottom
            left: parent.left
            right:parent.right
            margins: 5
        }
        color: Qt.darker(win.color, 1.2);
        ListView{
            id :listViewCampos
            anchors.centerIn: parent
            anchors.fill: parent
            clip: true
            spacing: 10
            delegate: Campo{
                label: modelData
                color: Qt.darker(firstContainer.color,1.1);

            }
        }
    }
    MenuBar{
        id: menubar
        anchors.right: parent.right
        anchors.left: parent.left

        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Open Template")


            }
            Action {
                id:exportAction
                text: qsTr("&Export as PDF")
                enabled: false

            }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }

        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")

            }
        }
    }




}

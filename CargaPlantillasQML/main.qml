//Enunciado de la practica --> git Mariano
//Enviar a --> clase001@itcloud-learning.com
import QtQuick
import QtQuick.Window
import QtQuick.Controls

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
            fill: parent
            margins: 5
        }
        color: Qt.darker(win.color, 1.2);
    }
    MenuBar{
        id: menubar
        anchors.right: parent.right
        anchors.left: parent.left

        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Open Template")
                onTriggered: win.openTemplate();

            }
            Action { text: qsTr("&Export as PDF") }
            MenuSeparator { }
            Action { text: qsTr("&Quit") }
        }

        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
                onTriggered: {console.log("help");}
            }
        }
    }

    function openTemplate(){
        console.log("Abriendo plantilla");
    }
}

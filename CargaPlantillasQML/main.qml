//Enunciado de la practica --> git Mariano
//Enviar a --> clase001@itcloud-learning.com
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs

import template.manager 1.0

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
                onTriggered: win.openTemplate();

            }
            Action {
                id:exportAction
                text: qsTr("&Export as PDF")
                enabled: false
                onTriggered: win.exportPDF();
            }
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

        fileDialog.open();

    }
    function exportPDF(){
        console.log("Exportar a pdf");
        fileDialog.exportarAPdf();
    }
    FileDialog{
        id:fileDialog
        onAccepted: {
            console.log(currentFile);

            templatemanager.openTemplate(currentFile);
            listViewCampos.model = templatemanager.getCampos();
            exportAction.enabled = true;
        }
    }
    TemplateManager{
        id: templatemanager
    }
}

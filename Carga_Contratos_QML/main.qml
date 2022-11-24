//Enunciado de la practica --> git Mariano
//Enviar a --> clase001@itcloud-learning.com
import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Dialogs

import Templatehandler.Interface 1.0


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
                onTriggered: {
                    dialog.open();
                }

            }
            Action {
                id:exportAction
                text: qsTr("&Export as PDF")
                enabled: false
                onTriggered: {

                   for (var i= 0 ; i < classHandler.cantidadCampos(); i++){
                       classHandler.completarCampo(listViewCampos.model[i], listViewCampos.contentItem.children[i].input);
                       //console.log(listViewCampos.model[i]);
                       //console.log(listViewCampos.contentItem.children[i].input);
                   }

                   classHandler.guardarPDF("Nuevo.pdf");
                }

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
    FileDialog{
        id: dialog

        onAccepted:{
            var url = dialog.selectedFile.toString();
            url = url.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            var cleanUrl = decodeURIComponent(url);
            classHandler.cargarTemplate(cleanUrl);

            listViewCampos.model = classHandler.obtenerCampos();
            exportAction.enabled = true;
        }
    }

    TemplateHandlerClass{
        id:classHandler
    }



}

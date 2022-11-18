import QtQuick
import QtQuick.Window
//own package
import MySerialPort
import QtQuick.Controls


ApplicationWindow {
    width: 740
    height: 580
    visible: true
    title: "SerialSender"
    color:"#BBBBBB"

    menuBar: MenuBar{
        Menu{
            title: "&Archivo"
            Menu{
                id      : menuPuertos
                title   : "&Puerto"
                ListView{
                    id:vistaPuertos
                    width: 50
                    height: 80
                    delegate: Rectangle{
                        id:delegate
                        width: parent.width
                        height: 20
                        Text{
                            id:nombrePuerto
                            text:modelData
                        }
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                comunicator.portName ="COM1";
                                comunicator.openPort();
                            }
                        }
                    }
                }
            }
            MenuSeparator{}
            MenuItem{
                text: "&Salir"
                onTriggered: {
                    Qt.quit();
                }
            }
        }
    }
    SerialComunicator{
        id: comunicator
        onPortNameChanged: {}
        onValueReceived: (value)=>{
            datoPuertoSerie.text +=  String.fromCharCode(value);
        }
    }
    Rectangle{
        id:container
        anchors.top: parent.top
        anchors.bottom:containerInputSender.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 20
        color: "white"
        radius: 10
        Text{
            id : datoPuertoSerie
            text: ""
            anchors.fill: parent
            anchors.margins: 20
        }
    }
    Rectangle{
        id: containerInputSender
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom:botonSend.top
        height: 30
        anchors.margins: 20
        color: "white"
        radius: 10
        TextInput{
            id:datosEnviados_textInput
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.topMargin: 7
            MouseArea{
                id: mouseAreaTextInput
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.IBeamCursor
                onClicked: {datosEnviados_textInput.focus = true;}
            }
        }
    }

    BotonClass{
        id:botonSend
        texto:"SEND"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        onClicked: {
            comunicator.sendString(datosEnviados_textInput.text);
        }
    }
    Component.onCompleted: {
        console.log("-----------") ;

        //generando menu de puertos
        var availablePorts = comunicator.listAvailablePorts();
        vistaPuertos.model = availablePorts;

    }
    Component.onDestruction: {
        comunicator.closePort();
    }


    Component{
        id: menuItemComponent
        MenuItem{

        }
    }

}

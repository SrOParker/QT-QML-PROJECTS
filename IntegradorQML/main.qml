import QtQuick 2.15
import QtQuick.Window 2.15
import manejador.interface 1.0
import QtQuick.Controls

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    MenuBar{
        id: menubar
        anchors.right: parent.right
        anchors.left: parent.left

        Menu {
            title: qsTr("&Resources")
            Action{
                text: "&Open Port1"
                onTriggered:{
                    manager.initPort("COM1");
                    buttonSignals.enabled = true;
                }
            }
            Action{
                text: "&Open Port2"
                onTriggered:{
                    manager.initPort("COM2");
                    buttonSignals.enabled = true;
                }
            }
            Action{
                text: "&Open Port3"
                onTriggered:{
                    manager.initPort("COM3");
                    buttonSignals.enabled = true;
                }
            }

            MenuSeparator { }

            Action {
                text: qsTr("&Quit")
                onTriggered:{
                    Qt.quit();
                }
            }
        }

    }


    ListView {
        id:botonera
        width: parent.width
        height: 40
        anchors.left: buttonSignals.right
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60

        orientation: ListView.Horizontal
        //model: {}
        delegate: Button{
            id:buttonGenerated
            width: 90
            height: 40
            text: modelData

            onClicked: {
                startbtn.visible = true;
                stopbtn.visible = true;
                stopbtn.enabled = false;
                signalCurrent.visible = true;

                manager.writeText("AT+SIGNAL="+text);
            }
        }
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        onModelChanged: {
            //click here select a signal
        }
    }

    Button{
        id: buttonSignals
        width: 110
        height: 40
        text: "Generate Signals"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.leftMargin: 20
        enabled: false

        onClicked: {
            botonera.model = manager.getSignalsString();


        }
    }
    Button{
        id: signalCurrent
        width: 110
        height: 40
        text: "Current Signal"
        anchors.left: parent.left
        anchors.bottom: buttonSignals.top
        anchors.margins: 20
        anchors.bottomMargin: 2
        anchors.leftMargin: 20
        visible: false
        onClicked: {
            manager.writeText("AT+CURR");
            manager.setReadVariable(1);
            console.log(manager.getCurrentSignalClean());

        }
    }

    Button{
        id:startbtn
        width: 110
        height: 40
        text: "Start"
        anchors.right: parent.right
        anchors.bottom: stopbtn.top
        anchors.rightMargin: 20
        anchors.bottomMargin: 2
        visible: false
    }
    Button{
        id:stopbtn
        width: 110
        height: 40
        text: "Stop"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        visible:false
    }


    ManagerInterface{
        id: manager
    }

}


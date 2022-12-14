import QtQuick 2.15
import QtQuick.Window 2.15
import manejador.interface 1.0
import QtQuick.Controls
//import manejador.canvas

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Integrador QML")
    color: "#424C44"
    property color colorBotones: "#839788"
    property real xpos  : 0
    property real ypos  : 0
    property real nexty : 0
    property real nextx : 0
    property real pY    : 0
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
            palette{
                buttonText: "#424c44"
            }
            background: Rectangle{
                    anchors.fill: parent
                    radius: 2
                    anchors.margins: 2
                    color:"#eee0cb"
                }

            onClicked: {
                startbtn.visible = true;
                stopbtn.visible = true;
                stopbtn.enabled = false;
                signalCurrent.visible = true;

                manager.writeText("AT+SIGNAL="+text);
            }
        }
        //highlight: Rectangle { color: "lightsteelblue"; radius: 2 }
        onModelChanged: {
            //click here select a signal
        }
    }

    Button{
        id: buttonSignals
        width: 110
        height: 40
        text: "GENERATE SIGNALS"

        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.leftMargin: 20
        enabled: false
        palette{
            buttonText: "#bfd7ea"
        }
        background: Rectangle{
                anchors.fill: parent
                radius: 2
                anchors.margins: 2
                color:window.colorBotones
            }
        onClicked: {
            botonera.model = manager.getSignalsString();


        }
    }
    Text{
        id:textcurrent
        width: 110
        height:40
        font.pixelSize: 20
        text:""
        anchors.bottom: signalCurrent.top
    }
    Button{
        id: signalCurrent
        width: 110
        height: 40
        text: "CURRENT SIGNAL"
        anchors.left: parent.left
        anchors.bottom: buttonSignals.top
        anchors.margins: 20
        anchors.bottomMargin: 2
        anchors.leftMargin: 20
        visible: false
        palette{
            buttonText: "#bfd7ea"
        }
        background: Rectangle{
                anchors.fill: parent
                radius: 2
                anchors.margins: 2
                color:window.colorBotones
            }
        onClicked: {
            manager.writeText("AT+CURR");
            manager.setReadVariable(1);
            textcurrent.text = manager.getCurrentSignal();
            timer.start();

        }
    }
    Timer{
        id:timer
        interval: 500
        running: false
        repeat: false
        onTriggered: {
            textcurrent.text = "";
        }


    }
    Button{
        id:startbtn
        width: 110
        height: 40
        text: "START"
        anchors.right: parent.right
        anchors.bottom: stopbtn.top
        anchors.rightMargin: 20
        anchors.bottomMargin: 2
        visible: false
        palette{
            buttonText: "#bfd7ea"
        }
        background: Rectangle{
                anchors.fill: parent
                radius: 2
                anchors.margins: 2
                color:window.colorBotones
            }
        onClicked: {
            manager.writeText("AT+START");
            stopbtn.enabled  = true;
            startbtn.enabled = false;
            //for(var i=0; botonera.model.length;i++){
            //    botonera.itemAtIndex(i).enabled = false;
            //}


        }
    }
    Button{
        id:stopbtn
        width: 110
        height: 40
        text: "STOP"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        visible:false
        palette{
            buttonText: "#bfd7ea"
        }
        background: Rectangle{
                anchors.fill: parent
                radius: 2
                anchors.margins: 2
                color:window.colorBotones
            }
        onClicked: {
            manager.writeText("AT+STOP");
            stopbtn.enabled  = false;
            startbtn.enabled = true;
            //for(var i=0; botonera.model.length;i++){
            //    botonera.itemAtIndex(i).enabled = true;
            //}
        }
    }
    Canvas{
        id: canvas
        width: parent.width
        y: 100
        height: 300
        anchors.margins: 100
        onPaint: {
                window.ypos = window.pY * 20;
                window.xpos ++;
                var ctx = getContext('2d');
                ctx.strokeStyle = "#b9bcaa";
                ctx.lineWidth = 1;
                ctx.beginPath();
                ctx.moveTo(window.xpos, window.ypos);
                ctx.lineTo(window.nextx,window.nexty);
                ctx.stroke();

                window.nexty = window.ypos;
                window.nextx = window.xpos;

        }
    }

    ManagerInterface{
        id: manager
        onSignalDataEmited: (dato)=>{
                                window.pY = dato;
                                //console.log(window.pY);
                                canvas.requestPaint();
                            }

    }


}


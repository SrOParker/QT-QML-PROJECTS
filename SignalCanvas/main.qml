import QtQuick 2.15
import QtQuick.Window 2.15
import projectSignal.readhandler 2.0
Window {
    id: view
    width: 1000
    height: 300
    minimumWidth: 1000
    maximumHeight: 300
    minimumHeight: 300
    maximumWidth: 1000
    visible: true
    title: "SignalCanvas"

    Rectangle{
        id: ventana
        width: parent.width / 2
        height: 200
        anchors.centerIn: parent
        anchors.margins: 5
        border.color: "black"
        border.width: 3

        property real xpos : 0
        property real ypos : 0
        property real nexty: 0
        property real nextx: 0
        Canvas{
            id: canvasElement
            anchors.fill: parent
            onPaint: {
                if(ventana.xpos === 500){
                    tiempo.stop();
                    textButt.text ="Start";
                }
                ventana.ypos = readHandler.read();
                ventana.xpos ++;
                ventana.ypos = ventana.ypos * 30;
                var ctx = getContext('2d');
                ctx.strokeStyle = "red";
                ctx.lineWidth = 3;
                ctx.beginPath();
                ctx.moveTo(ventana.xpos, ventana.ypos);
                ctx.lineTo(ventana.nextx,ventana.nexty);
                ctx.stroke();

                ventana.nexty = ventana.ypos;
                ventana.nextx = ventana.xpos;
            }
            function clear_canvas() {
                        var ctx = getContext("2d");
                        ctx.reset();
                        canvasElement.requestPaint();
                    }
        }

        Rectangle{
            id : buttonStartSignal
            width: 100
            height: 50
            color: "lightblue"
            border.color: Qt.darker(color)
            border.width: 2

            anchors.left: canvasElement.right
            anchors.leftMargin: 50
            anchors.verticalCenter: canvasElement.verticalCenter
            Text{
                id: textButt
                text: "Start"
                anchors.centerIn: parent
                font.pointSize: 12
            }
            MouseArea{
                id: areabuttonstart
                anchors.fill: parent
                onClicked: {
                    if(!readHandler.archiveOpened()){
                        canvasElement.clear_canvas();
                        readHandler.open("C:\\Users\\iamsr\\OneDrive\\Documentos\\Workspaces\\QT-GIT\\QT-QML-PROJECTS\\SignalCanvas\\signal.txt");
                        textButt.text = "Stop";

                        tiempo.start();
                    }else{
                        readHandler.close();
                        tiempo.stop();
                        textButt.text = "Start";
                    }
                }
            }
        }
    }

    ReadHandler{
        id: readHandler
    }
    Timer{
        id: tiempo
        interval: 10
        repeat: true
        running: false
        onTriggered: {
            canvasElement.requestPaint();
        }
    }
}

import QtQuick 2.15
import QtQuick.Window 2.15

import archivemanager.receiver.interface
Window {
    id: view
    width: 1000
    height: 300
    minimumWidth: 1000
    maximumHeight: 300
    minimumHeight: 300
    maximumWidth: 1000
    visible: true
    title: "ECG"

    property real pY:0
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
                    ventana.ypos = view.pY * 100;//0.2084;//receiverData.getDataAt(0.2084);////////
                    ventana.xpos ++;
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


            }

        }
        ReceiverData{
            id: receiverData
            onDataReceived: (data)=>{
                for(var i=0; i<data.length;i++){
                    view.pY = data[i];
                    console.log(view.pY);
                    canvasElement.requestPaint();
                }
            }
        }
    }




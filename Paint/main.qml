import QtQuick 2.15
import QtQuick.Window 2.15
import paint.fileHandler 1.5


Window {
    width   : 640
    height  : 480
    visible : true
    title   : "Paint"
    id      : view
    Rectangle{
        id: ventana
        anchors.fill: parent
        anchors.centerIn: parent
        width: parent.width

        Rectangle{
            id: rect_color
            anchors.horizontalCenter: ventana.horizontalCenter
            height: 50
            width :  200
            anchors.top: parent.top
            ListView{
                id      : colores
                width   : parent.width
                height  : parent.height
                spacing : 5
                anchors.top             : parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                orientation: ListView.Horizontal

                property color colorPincel

                model: ["#aa0000","#00aa00","#0000aa","#505050"]
                clip : false
                delegate: Rectangle{
                    id      : pincel
                    width   : parent.height
                    height  : parent.height

                    required property color modelData
                    color: modelData
                    border{
                        color: Qt.darker(color)
                        width: 2
                    }
                    MouseArea{
                        id:areaColor
                        anchors.fill: parent
                        onClicked: {
                            colores.colorPincel = pincel.modelData;
                            //console.log("Color seleccionado: " + colores.colorPincel);
                        }
                    }
                }
            }

        }
        Rectangle{
            id          : contenedorCanvas
            color       : "white"
            border.color: "black"
            border.width: 4
            width       : ventana.width - 10

            anchors{
                horizontalCenter: ventana.horizontalCenter
                top     : rect_color.bottom
                right   : ventana.right
                //left    : ventana.left
                bottom  : botonGuardar.top
                margins : 5
            }
            Canvas{
                id:canvaselement
                anchors.fill: parent

                property color color: colores.colorPincel
                property real ultimoX
                property real ultimoY
                onPaint: {
                    var ctx = getContext('2d');
                    ctx.strokeStyle = canvaselement.color;
                    ctx.lineWidth = 3;
                    ctx.beginPath();
                    ctx.moveTo(ultimoX, ultimoY);
                    ctx.lineTo(areaCanvas.mouseX,areaCanvas.mouseY);
                    ultimoX = areaCanvas.mouseX;
                    ultimoY = areaCanvas.mouseY;
                    ctx.stroke();
                    if (archiveHandler.archiveOpened()){
                        archiveHandler.escribir(ultimoX, ultimoY);
                    }

                }
            }
            MouseArea{
                id: areaCanvas
                anchors.fill: parent

                onPressed: {
                    canvaselement.ultimoX = mouseX;
                    canvaselement.ultimoY = mouseY;
                    //console.log("Datos: x: " + canvaselement.ultimoX + " ||| y: " + canvaselement.ultimoY);
                }
                onPositionChanged: {
                    //console.log("Presion: x: " + canvaselement.ultimoX + " ||| y: " + canvaselement.ultimoY);
                    //console.log("Mouse: x: " + mouseX + " ||| y: " + mouseY);
                    canvaselement.requestPaint();
                }
            }
        }
        Rectangle{
            id: botonGuardar
            color : "#913284"
            //color: botonGuardar.containsMouse ? "red" : "#913284"
            width : 100
            height: 50
            border{
                color: Qt.darker(color)
                width: 2
            }
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.margins: 5
            Text{
                id: textoBot
                text: "Save"
                font.pointSize: 12
                anchors.centerIn: parent
            }
            MouseArea{
                id: areaGuardar
                anchors.fill: parent
                onClicked: {
                    canvaselement.grabToImage((result)=>{result.saveToFile("dibujo.png");});
                    timerBot.start();
                }

            }

        }
        Rectangle{
            id          : botonRecord
            width       : 50
            height      : 50
            color       : "red"
            border.color: Qt.darker(color)
            border.width: 2
            radius      : 50

            anchors.left    : botonGuardar.right
            anchors.bottom  : parent.bottom
            anchors.margins : 5
            Text{
                id  : botRec
                font.pointSize: 12
                anchors.centerIn: parent
                text: "REC"
            }
            MouseArea{
                id: areaRec
                anchors.fill: parent
                onClicked: {
                    if (!archiveHandler.archiveOpened()){
                        archiveHandler.abrirArchivo("trackMouse.txt");
                        botRec.text = "STOP";
                    }else{
                        archiveHandler.cerrarArchivo();
                        botRec.text = "REC";
                    }


                }
            }
        }
    }
    Timer{
        id      : timerBot
        interval: 1000
        running : false
        repeat  : true
        onTriggered: {
            botonGuardar.color = (botonGuardar.color == "#913284" ? "#218224" : "#913284");
        }
    }
    FileHandler{
        id: archiveHandler
    }


}

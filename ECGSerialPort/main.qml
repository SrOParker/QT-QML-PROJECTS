import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs

import ArchiveManager.Interface 1.0

Window {
    width: 640
    height:100
    visible: true
    title: qsTr("Interface ECG SERIAL PORT")

    Button{
        id : botn
        anchors.centerIn: parent
        texto: "START"
        onClicked: {
            manager.resetPositionRec();
            manager.readFromTXT("ECG.txt");
            manager.startSerialCom("ECG.txt", "COM3", 500, 115200);
            //timer.start()
        }
    }

    ArchiveManager{
        id: manager
        onStarted: {
            timer.start();
        }
        onStopped: {
            timer.stop();
        }
    }

    Timer{
        id:timer
        interval:20
        repeat: true
        onTriggered: {
            tiempo.tiempoTranscurrido += 0.1;
        }
    }
    Text{
        id:tiempo
        property real tiempoTranscurrido:0
        text: tiempoTranscurrido
        width: 100
        height: 50
        font.pixelSize: 30
        anchors.right: parent.right
        anchors.top:parent.top
        anchors.topMargin: 20

    }

}

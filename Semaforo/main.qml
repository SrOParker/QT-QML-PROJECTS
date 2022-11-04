import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Rectangle{
        id      : semaforo
        width   : height / 2
        height  : parent.height / 2

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top             : parent.top
        anchors.topMargin       : 10
        border.color            : "black"
        border.width            : 2
        color                   : "#AAAAAA"
        state                   : "rojoArribaVerdeAbajo"
        states:[
            State {
                name: "rojoArribaVerdeAbajo"
                PropertyChanges {
                    target: luz1
                    color : "green"
                }
                PropertyChanges {
                    target: luz2;
                    color : "red"
                }
            },
            State {
                name: "verdeArribaRojoAbajo"
                PropertyChanges {
                    target: luz1
                    color : "red"
                }
                PropertyChanges {
                    target: luz2
                    color : "green"
                }
            }
        ]
        transitions:[
            Transition{
                from: "rojoArribaVerdeAbajo"
                to  : "verdeArribaRojoAbajo"

                ColorAnimation {
                    target      :luz1
                    properties  : "color"
                    duration    : 500
                }

                ColorAnimation {
                    target      : luz2
                    properties  : "color"
                    duration    : 500
                }
            },

            Transition{
                from: "verdeArribaRojoAbajo"
                to  : "rojoArribaVerdeAbajo"

                ColorAnimation {
                    target      :luz1
                    properties  : "color"
                    duration    : 500
                }

                ColorAnimation {
                    target      : luz2
                    properties  : "color"
                    duration    : 500
                }
            }
        ]
        Rectangle{
            id                      : luz1
            color                   : "red"
            width                   : parent.width / 1.5
            height                  : parent.width / 1.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top             : parent.top
            anchors.topMargin       : height / 4
            radius                  : width  / 2
            border.color            : Qt.darker(color)
            border.width            : 2

        }
        Rectangle{
            id                      : luz2
            color                   : "green"
            width                   : parent.width / 1.5
            height                  : parent.width / 1.5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom          : parent.bottom
            anchors.bottomMargin    : height / 4
            radius                  : width  / 2
            border.color            : Qt.darker(color)
            border.width            : 2

        }
        Rectangle{
            id                      : button
            width                   : semaforo.width
            height                  : 50
            anchors.horizontalCenter: parent.horizontalCenter
            y                       : semaforo.y + semaforo.height + 5
            color                   : "#402020"

            Text{
                id                      : textButton
                color                   : "white"
                font.family             : "impact"
                font.pixelSize          : 25
                text                    : "Cambiar"
                anchors.verticalCenter  : parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            MouseArea{
                anchors.fill    : parent
                onClicked       : {
                    label.text = "EstadoCambiado";
                    temporizadorSingleShot.start();
                    semaforo.state = (semaforo.state === "rojoArribaVerdeAbajo") ? semaforo.state = "verdeArribaRojoAbajo" : semaforo.state = "rojoArribaVerdeAbajo";

                    //if (semaforo.state === "rojoArribaVerdeAbajo"){
                    //    semaforo.state = "verdeArribaRojoAbajo";
                    //}else{
                    //    semaforo.state = "rojoArribaVerdeAbajo";
                    //}
                }
            }
        }
        Text{
            id                          : label
            text                        : ""
            color                       : "black"
            y                           : semaforo.height + button.height + 20 + 20
            font.pixelSize              : 15
            font.family                 : "Calibri"
            anchors.horizontalCenter    : parent.horizontalCenter
        }
        Timer{
            id          : temporizadorSingleShot
            interval    : 2000
            running     : false
            repeat      : false
            onTriggered : {
                label.text=""

            }
        }
    }
}

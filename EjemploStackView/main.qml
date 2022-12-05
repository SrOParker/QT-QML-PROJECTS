import QtQuick
import QtQuick.Window
import QtQuick.Controls
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    StackView{
        id: stack

        initialItem: firstPage

        anchors.fill: parent
    }
    Component{
        id: firstPage
        Rectangle{

            Text{
                id:texto1
                text: "Esta es la primera página"
            }
            Rectangle{
                id:bot
                width: 30
                height: 20
                color: "#A2A2A2"
                x:50
                y:50
                Text{
                    id: textoBot
                    text: "Boton"
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stack.push(secondPage);
                    }
                }
            }
        }
    }
    Component{
        id: secondPage
        Rectangle{

            Text{
                id:texto2
                text: "Esta es la segunda página"
            }
            Rectangle{
                id:boto
                width: 30
                height: 20
                color: "#A2A2A2"
                x:50
                y:50
                Text{
                    id: textoBoto
                    text: "Siguiente"
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stack.push(thirdPage);
                    }
                }
            }
        }
    }
    Component{
        id: thirdPage
        Rectangle{

            Text{
                id:texto3
                text: "Esta es la tercera página"
            }
            Rectangle{
                id:boto3
                width: 30
                height: 20
                color: "#A2A2A2"
                x:50
                y:50
                Text{
                    id: textoBoto3
                    text: "Página anterior"
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stack.pop();
                    }
                }
            }
            Rectangle{
                id:boto33
                width: 30
                height: 20
                color: "#A2A2A2"
                x:105
                y:50
                Text{
                    id: textoBoto33
                    text: "Pagina principal"
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        stack.pop();
                        stack.pop();
                    }
                }
            }
        }
    }
}

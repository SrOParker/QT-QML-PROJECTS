import QtQuick 2.15
import QtQuick.Window 2.15
import Qt.labs.folderlistmodel 2.15

import itcloud.claseprueba

Window {
    id      : ventana
    width   : 640
    height  : 480
    visible : true
    title   : qsTr("Memerizador")

    //Metodo 1 de cargar imagen con conexion c++ qml (Fondo de pantalla)
    Image{
        id          : primerImg
        source      : "image://provisorDeImagenes/img/fondo.jpg"
        anchors.fill: parent
    }



    ListView{
        id                          : lista
        anchors.fill                : parent
        anchors.margins             : 20
        spacing                     : 5
        model                       : FolderListModel{
                        id              : modelo
                        nameFilters     : ["*.jpg", "*.jpeg"]
                        showDirs        : false
        }
        clip                        : true
        delegate                    : delegado
        highlight                   : resaltado
        focus                       : true
        highlightFollowsCurrentItem : false
        Component{
            id : delegado
            Item{
                id      : itemdelegado
                width   : lista.width
                height  : ventana.height/5
                required property int index
                required property var fileName
                Rectangle{
                   id              : recta
                   width           : parent.width/3
                   height          : parent.height
                   anchors.centerIn: parent
                   border.color    : Qt.darker(color)
                   border.width    : 2
                   Image{
                       id               : imagendelegado
                       source           : "image://provisorDeImagenes/" + itemdelegado.fileName
                       anchors.fill     : parent
                       fillMode         : Image.PreserveAspectFit
                       anchors.margins  : 5


                   }
                }
                MouseArea{
                    id          : mousearea_delegado
                    anchors.fill: parent
                    onClicked   : {
                        lista.currentIndex = itemdelegado.index;
                        //Desde c++ desde clase objetoprueba en otro hilo
                        objetodeprueba.imprimirStringPorConsola(itemdelegado.fileName);

                        parent.state = "expandido";
                    }
                }
                states:[
                    State{
                        name:"expandido"
                        PropertyChanges {
                            target: itemdelegado
                            height: ventana.height
                        }
                    }
                ]
            }
        }
        Component{
            id : resaltado
            Rectangle{
                width   : ListView.view ? ListView.view.width : 0
                height  : ventana.height/5
                color   : "#00900000"
                border.color: "#904040"
                border.width: 7
                radius: 50
                y       : ListView.view ? ListView.view.currentItem.y : 0

                Behavior on y{
                    SpringAnimation {
                        spring :0.5
                        damping: 0.1
                    }
                }
            }
        }
        ClaseDePrueba{
            id: objetodeprueba

        }

    }





    //EJEMPLO DE VECTOR LISTA CON LIST ELEMENT
    //Column{
    //    spacing : 5
    //    Repeater{
    //        id      : repeater
    //        model   : ListModel{
    //            id : lista
    //            ListElement{
    //                nombre          : "Lunes"
    //                colorElemento   : "yellow"
    //            }
    //            ListElement{
    //                nombre          : "Martes"
    //                colorElemento   : "lightblue"
    //            }
    //            ListElement{
    //                nombre          : "Miércoles"
    //                colorElemento   : "lightgreen"
    //            }
    //            ListElement{
    //                nombre          : "Jueves"
    //                colorElemento   : "#995555"
    //            }
    //            ListElement{
    //                nombre          : "Viernes"
    //                colorElemento   : "grey"
    //            }
    //            ListElement{
    //                nombre          : "Sábado"
    //                colorElemento   : "red"
    //            }
    //            ListElement{
    //                nombre          : "Domingo"
    //                colorElemento   : "purple"
    //            }
    //        }
    //        delegate:Rectangle{
    //            required property var colorElemento
    //            required property var nombre
    //            id      : rect_delegado
    //            width   : 100
    //            height  : 50
    //            color   : colorElemento
    //            border.color: Qt.darker(colorElemento)
    //            border.width: 4
    //            Text{
    //                id              : textElement
    //                anchors.centerIn: parent
    //                text            : nombre
    //                color: Qt.darker(colorElemento)
    //                font.family: "impact"
    //            }
    //            MouseArea{
    //                anchors.fill: parent
    //                onClicked: {
    //                    console.log(rect_delegado.index);
    //                }
    //            }
    //        }
    //    }
    //}




    //EJEMPLO DE VECTOR LISTA CON REPEATER NUMERICO
    //Column{
    //    spacing : 5
    //    // Forma de hacer un vector array de cosas
    //    Repeater{
    //        model   : 100
    //        delegate: Rectangle{
    //            id          : rect_delegado
    //            required property int index
    //            width       : 50
    //            height      : 20
    //            color       : "lightblue"
    //            border.color: Qt.darker(color)
    //            border.width: 2
    //            Text {
    //                id              : texto_delegado
    //                text            : rect_delegado.index
    //                anchors.centerIn: parent
    //            }
    //        }
    //    }
    //}

    //EJEMPLO DE VECTOR LISTA CON REPEATER ARRAY DE STRINGS
    //Column{
    //    spacing : 5
    //    Repeater{
    //        model   : ["Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"]
    //        delegate: Rectangle{
    //            id          : rect_delegado
    //            required property int index
    //            required property var modelData
    //            width       : 100
    //            height      : 50
    //            color       : "lightblue"
    //            border.color: Qt.darker(color)
    //            border.width: 2
    //            Text{
    //                id              : text_delegado
    //                anchors.centerIn: parent
    //                text            : index + " " + modelData
    //            }
    //            MouseArea{
    //                anchors.fill: parent
    //                onClicked: {
    //                    rect_delegado.color = "red";
    //                    console.log(index + " " + modelData);
    //                }
    //            }
    //        }
    //    }
    //}
}



























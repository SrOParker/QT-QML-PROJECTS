import QtQuick
import QtQuick.Window

Window {
    id: ventana
    width: 640
    height: 480
    minimumHeight: 480
    minimumWidth: 640
    color: "cadetblue"
    visible: true
    title: "Primer Proyecto QML"
    //RECTANGULO CON TEXTO DENTRO
    Rectangle{
        id: rectangulo
        width: parent.width / 2
        height: parent.height / 4
        x: (parent.width - width) / 2
        y: (parent.height - height) / 4
        color: "#602020"
        radius: 10
        border.color: "green"
        border.width: 4
        Text{
            id:text_rect
            text: "Dentro del rectángulo"
            color: "white"
            x: 10
            y: 10
        }
        MouseArea {
            id: areaMouseRectangulo
            anchors.fill: parent
            onClicked: imagenHombrecito.visible = !imagenHombrecito.visible
        }
    }
    //IMAGEN DEL HOMBRECITO
    Rectangle{
        id: imagenHombrecito


        width:  100
        height: 70
        border.color: "red"//--
        x: (ventana.width -  width)  / 2
        y: (ventana.height - height) - 100
        Image{
            id: hombrecito
            source: "https://cms-assets.tutsplus.com/cdn-cgi/image/width=600/uploads/users/358/posts/26263/image/09-clothes.png"
            anchors.fill: parent
        }
    }
    //TEXTO QUE CAMBIA CON PULSACIONES
    Text {
        id: texto
        property int presionesEspacio
        text: "Apretaste espacio " + presionesEspacio + " veces."
        Keys.onSpacePressed: presionesEspacio++
        Keys.onEscapePressed: presionesEspacio = 0
        Keys.onPressed: function(event) {
            if(event.key === Qt.Key_A){
                presionesEspacio+=10
            }else if (event.key === Qt.Key_R){
                rotation+=10
            }
        }
        focus: true
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        elide: Text.ElideMiddle

        font.pixelSize: 25 // font.pointSize:25
        font.family: "Courier"
        x: (ventana.width - width) / 2
        y: (ventana.height - height) / 2

        MouseArea {
            anchors.fill: parent
            onClicked: texto.focus = true
        }
    }
    //RECTANGULO QUE CONTIENE INPUT TEXT
    Rectangle{
        id: rectangle_input_text
        color: "#DDDDDD"
        width: parent.width * 0.5
        height: 20
        x: (parent.width -width) / 2
        y: imagenHombrecito.y + imagenHombrecito.height + 20
        TextInput {
            id: inputtext
            text: "Escriba aqui"
            anchors.fill: parent
            horizontalAlignment: TextInput.AlignHCenter
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    inputtext.text  = ""
                    inputtext.focus = true

                }

            }
            Keys.onPressed: (event)=>{
                                    if ((event.key === Qt.Key_Enter) || (event.key === Qt.Key_Return)){
                                        text_rect.text = inputtext.text
                                    }
                                 }

        }
    }
    //BOTON ITEM CREADO POR NOSOTROS
    Button{
        x: (parent.width - width) / 2
        y: imagenHombrecito.y + imagenHombrecito.height + 40
        textoMostrado: "Haz click"
        width : 100
        height: 50

        onClicked: text_rect.text = "Boton Presionado"
    }
}


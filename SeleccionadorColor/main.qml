import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id      : ventanaPrincipal
    width   : 640
    height  : 480
    visible : true
    title   : qsTr("Seleccionador de color")

    Rectangle{
        anchors.fill    : parent

        Rectangle{
                id          : rec_image
                width       : 144
                height      : 100
                //border.color: "red"
                //border.width: 2
            Image {
                id              : hombrecito
                source          : "/img/hombrecito.jpg"
                scale           : ventanaPrincipal.width / (10 * width)
                anchors.fill    : parent

            }

        }

        Text {
            id               : textoCambiante
            text             : "Seleccione un color"
            color            : "black"
            anchors.centerIn : parent
            font.pointSize   : 30
            font.bold        : true
        }

        Grid {
            id                  : colorPicker

            anchors.left        : parent.left
            anchors.bottom      : parent.bottom
            anchors.leftMargin  : 10
            anchors.bottomMargin: 10

            rows                : 2
            columns             : 3
            spacing             : 2 //espacio para todos lados

            Celda{
                colorCelda: 'blue'
                onClicked: (colorRecibido)=>{textoCambiante.color = colorRecibido}
            }
            Celda{
                colorCelda: 'darkkhaki'
                onClicked: (colorRecibido)=>{textoCambiante.color = colorRecibido}
            }
            Celda{
                colorCelda: 'green'
                onClicked: (colorRecibido)=>{textoCambiante.color = colorRecibido}
            }
            Celda{
                colorCelda: 'lightcoral'
                onClicked: (colorRecibido)=>{textoCambiante.color = colorRecibido}
            }
            Celda{
                colorCelda: 'maroon'
                onClicked: (colorRecibido)=>{textoCambiante.color = colorRecibido}
            }
            Celda{
                colorCelda: 'mediumvioletred'
                onClicked: (colorRecibido)=>{textoCambiante.color = colorRecibido}
            }

        }

        //Movement && collision
        Keys.onPressed  : (event) =>{
                            switch(event.key){

                                case Qt.Key_Left:
                                    rec_image.x -= 5
                                    hombrecito.mirror = true
                                    break;
                                case Qt.Key_Right:
                                    rec_image.x += 5
                                    hombrecito.mirror = false
                                    break;
                                case Qt.Key_Up:
                                    rec_image.y -= 5
                                    break;
                                case Qt.Key_Down:
                                    rec_image.y += 5
                                    break;
                            }
                            if ((rec_image.mapToItem(colorPicker, rec_image.x, rec_image.y).y > 272 &&
                                rec_image.mapToItem(colorPicker, rec_image.x, rec_image.y).y < ventanaPrincipal.height) &&
                                (rec_image.mapToItem(colorPicker, rec_image.x, rec_image.y).x > -160 &&
                                 rec_image.mapToItem(colorPicker, rec_image.x, rec_image.y).x < 140 )){
                                textoCambiante.text = "Estas sobre el grid"

                            }else {
                                textoCambiante.text =   rec_image.mapToItem(colorPicker, rec_image.x, rec_image.y).x +
                                                        " , " +
                                                        rec_image.mapToItem(colorPicker, rec_image.x, rec_image.y).y;
                            }
                        }
        focus           : true
    }
}

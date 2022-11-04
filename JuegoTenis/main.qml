import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width   : 640
    height  : 480
    visible : true
    title   : qsTr("Juego de Tennis")

    Rectangle{
        id              : cancha
        color           : "#9DB577"
        anchors.fill    : parent
        property color nuevoColor: "#9DB577"

        Contador{
            id  : contador1
            x   : (parent.width / 2) - (width/2) - 50
            y   : 15

        }
        Contador{
            id  : contador2
            x   : (parent.width / 2) - (width/2) + 50
            y   : 15
        }
        //Definición Jugadores
        Raqueta{
            id                  : player1
            color               : "#7796B5"
            anchors.left        : parent.left
            anchors.leftMargin  : 5
            width               : cancha.width / 50
            height              : cancha.height / 3
            up                  : Qt.Key_W
            down                : Qt.Key_S

        }
        Raqueta{
            id                  : player2
            color               : "#772225"
            anchors.right       : parent.right
            anchors.rightMargin : 5
            width               : cancha.width / 50
            height              : cancha.height / 3
        }
        //Controles
        focus: true
        Keys.onPressed: (event) => {
                            switch(event.key){
                                case player1.up:
                                    player1.y -= 10
                                    break;
                                case player1.down:
                                    player1.y += 10
                                    break;
                                case player2.up:
                                    player2.y -= 10
                                    break;
                                case player2.down:
                                    player2.y += 10
                                    break;
                                case Qt.Key_H:
                                    ball.nuevoX = ball.nuevoX + 300
                                    animacion_en_X.start();
                                    break;
                                default:
                                    break;
                            }
                        }
        Image{
            id      : ball
            source  : "ball.png"
            x       : 18
            y       : 0
            width   : parent.width / 10
            height  : parent.height/ 7.5


            property int nuevoX     : 0
            property int nuevoY     : 0
            property int nuevoAngulo: 0
            NumberAnimation on x{
                id      : animacion_en_X
                to      : ball.nuevoX

                duration: 1000
            }
            NumberAnimation on y{
                id      : animacion_en_Y
                to      : ball.nuevoY

                duration: 1000
            }
            RotationAnimation on rotation {
                id: animationRotation
                to: ball.nuevoAngulo
                duration: 200
            }
        }

        ColorAnimation on color{
            id      :animacioncolor
            to      : cancha.nuevoColor
            duration: 1000
        }
    }

    Timer{
        id       : clock
        interval : 1020
        running  : true
        repeat   : true

        onTriggered: {
            if (ball.nuevoX === 0+18){
                ball.nuevoX = cancha.width - (ball.width + (ball.width/3.75));
                ball.nuevoY = Math.random() * cancha.height - ball.height;
                ball.nuevoAngulo = 90 + Math.atan((ball.nuevoY - ball.y) / (ball.nuevoX - ball.x)) * (180 / Math.PI);
                cancha.nuevoColor = "#9DB577";
                if (((ball.y < player1.y)&&((ball.y+ball.height)<player1.y))||((ball.y>player1.height+player1.y))){

                    contador2.puntos++;
                }
            }else{
                ball.nuevoX = 0+18;
                ball.nuevoY = Math.random() * cancha.height - ball.height;
                ball.nuevoAngulo = -90 + Math.atan((ball.nuevoY - ball.y) / (ball.nuevoX - ball.x)) * (180 / Math.PI);
                cancha.nuevoColor = "#9DB544";
                if (((ball.y < player2.y)&&((ball.y+ball.height)<player2.y))||((ball.y>player2.height+player2.y))){

                    contador1.puntos++;
                }
            }
            animacion_en_X.start();
            animacion_en_Y.start();
            animationRotation.start();
            animacioncolor.start()
        }
    }
}

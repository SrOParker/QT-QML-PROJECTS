import QtQuick 2.15
import QtQuick.Window 2.15


Window {
    width: 640
    height: 480
    visible: true
    title: "HTML"


    Rectangle{
        id : marco
        anchors.fill: parent

        ListView{
            id: vista
            anchors.fill: parent
            delegate: delegado
            clip: true
            //model: modelData

        }
        Component{
            id:delegado

            Rectangle{
                width: marco.width
                height: marco.height/2
                border.color: "black"
                border.width: 3
                Image{
                    id:imagen
                    source: modelData.link
                    width: parent.width/3
                    height: parent.height/1.4
                    y: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.PreserveAspectFit
                }
                Rectangle{
                    id:contenedorTexto
                    height: imagen.height/4
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: imagen.bottom
                    Text{
                        id:textimg
                        text: modelData.title
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.bottom: image.bottom
                        anchors.bottomMargin: 10

                    }
                }



            }
        }

        Component.onCompleted: {
            cargar();

        }
        function cargar(){ //peticion js para recoger un objeto externo de internet
            var httpRequest = new XMLHttpRequest();
            httpRequest.onreadystatechange = function (){
                if (httpRequest.readyState == httpRequest.HEADERS_RECEIVED ){
                    console.log('Header recibed.');
                }else if(httpRequest.readyState == httpRequest.DONE){
                    var json = JSON.parse(httpRequest.responseText.toString());
                    console.log('Pag cargada');
                    vista.model = json.items;
                }
            }
            httpRequest.open("GET","https://gist.githubusercontent.com/marianocossio/9ac38eae535b5734811bff1df7922b01/raw/94ad54e689623f3c65cc8e0fc162287642550eaf/");
            httpRequest.send();

        }



    }
}



//dibujo de imagen desde internet
//Rectangle{
//    id : marco
//    anchors.fill: parent
//    Image{
//        id:imagen
//        source: "https://upload.wikimedia.org/wikipedia/commons/thumb/0/0b/Qt_logo_2016.svg/2560px-Qt_logo_2016.svg.png"
//        anchors.fill:parent
//        fillMode: Image.PreserveAspectFit
//    }
//}


// cargo codigo de boton
//import "https://gist.githubusercontent.com/marianocossio/3566cc0346678383335594dd2e0fccc2/raw/506b08a94d9b0e0f449527b6b3cf79963bc67ecb/" as BotonGitClass
//Loader{
//    id      : lectorEXT
//    source  : "https://gist.githubusercontent.com/marianocossio/66f2b61fa1509f300cfcb275025ddcff/raw/da1a08d7d243d0a1a099a1600d9e653a16ad8669/main.qml"
//    anchors.centerIn: parent
//}
//BotonGitClass.Boton{
//    id:botonSalir
//    texto:"salir"
//    anchors.verticalCenter: parent.verticalCenter
//    anchors.right: parent.right
//    onClicked:{
//        Qt.quit();
//    }
//}

import QtQuick
import QtQuick.Window
import QtQuick.LocalStorage

Window {
    width: 640
    height: 480
    visible: true
    title: "Agenda"

    Rectangle{
        id      : contenedor
        width   : 100
        height  : 100
        color   : "#704040"
        radius  : 5
        property var dB
        Text{
            id                  : textContenedor
            anchors.centerIn    : parent
            text                : Math.round(parent.x) + " , " + Math.round(parent.y)
            font.pointSize      : 10
            horizontalAlignment : Text.AlignHCenter
            color               : Qt.lighter(contenedor.color)
        }
        MouseArea{
            id          : mAreaContenedor
            anchors.fill: parent
            drag.target : parent

        }
        Component.onCompleted:{
            inicializarDB();
            leerPosicion();
        }
        Component.onDestruction: {
            guardarPosDB();
        }
        function inicializarDB(){
            dB = LocalStorage.openDatabaseSync("C:\\Users\\aurec\\Documents\\Laure\\QT GIT\\QT-QML-PROJECTS\\SQL\\PersistenciaPosicion", "1.0", "base de datos para guardar posiciones del dragable",20);
            dB.transaction(function(transac){
                console.log("Creando tabla");
                transac.executeSql("CREATE TABLE IF NOT EXISTS data(name Text, value Text)");
            });
        }
        function guardarPosDB(){
            console.log("Guardando posicion en DB");
            if(!dB){
                return;
            }else{
                dB.transaction(function(tranc){
                    var resultado = tranc.executeSql("select * from data where name = 'posRect'");
                    var obj = {
                        x : contenedor.x,
                        y : contenedor.y
                    };
                    if(resultado.rows.length === 1){
                        console.log("Ya existen los datos. Se actualizan los datos de la tabla");
                        resultado = tranc.executeSql("update data set value = ? where name = 'posRect'", [JSON.stringify(obj)]);
                    }else{
                        console.log("Los datos todavia no existen. Se crea valor en la tabla");
                        resultado = tranc.executeSql("insert into data values (?,?)", [ 'posRect' , [JSON.stringify(obj)] ] );
                    }
                });
            }
        }
        function leerPosicion(){
            console.log("Leyendo la posicion guardada");
            if(!dB){
                return;
            }else{
                dB.transaction(function (transac){
                    console.log("Leyendo de la base de datos");
                    var result = transac.executeSql("select * from data where name = 'posRect'");
                    console.log(result.rows.length);
                    if (result.rows.length === 1){
                        var valor = result.rows[0].value;
                        var objJS = JSON.parse(valor);
                        contenedor.x = objJS.x;
                        contenedor.y = objJS.y;
                    }
                });
            }
        }
    }
}

import QtQuick
import QtQuick.Window
import QtQuick.Controls //dialogos
import QtQuick.LocalStorage
Window {
    id: view
    width: 640
    height: 480
    visible: true
    title: "Agenda SQL"
    color: "#003000"
    maximumHeight: 480
    maximumWidth: 640
    minimumHeight: 480
    minimumWidth: 640
    property var    db
    property alias  colorAg: agenda.color
    Rectangle{
        id: agenda
        anchors.fill: parent
        anchors.margins: 5
        color:"#AAddAA"
        CampoInput{
            id:nombre
            label: "Nombre *"
            width: parent.width

            color: Qt.darker(view.colorAg, 1.2)
            visibleButton: false

        }
        CampoInput{
            id:tlf
            label: "Teléfono *"
            width: parent.width
            color: Qt.darker(view.colorAg, 1.2)
            visibleButton: false
            y: 65

        }
        CampoInput{
            id:fechaSeleccionable
            label:"Fecha Nacimiento *"
            width: parent.width
            color: Qt.darker(view.colorAg, 1.2)
            y: 65 * 2
            visibleButton: false
            clickeable: false
            onCampoSeleccionado: {
                calendario_dialogo.open();
            }
        }
        CampoInput{
            id: archivoFoto
            label: "Foto"
            width: parent.width
            color: Qt.darker(view.colorAg, 1.2)
            //visibleButton: false

            onBotonPressed: { console.log("no implementado");}
            nameButton: "SELECCIONAR"
            y: 65 * 3
        }
        BotonClass{
            id: btnGuardar
            texto: "GUARDAR"
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 5
            color: Qt.darker(parent.color)
            onClicked: {
                var datos = [nombre.input, tlf.input, fechaSeleccionable.input, archivoFoto.input];
                if(nombre.input != "" && tlf.input!="" && fechaSeleccionable.input!=""){
                    agenda.guardarDatos(datos);
                }else{
                    console.log("No es posible guardar, rellenar campos obligatorios");
                }

            }
        }
        BotonClass{
            id: btnBuscar
            texto:"BUSCAR"
            anchors.bottom: parent.bottom
            anchors.right:btnGuardar.left
            anchors.margins: 5
            color: Qt.darker(parent.color)
            onClicked: {
                agenda.buscarDatos(nombre.input);
            }
        }
        BotonClass{
            id: btnClear
            texto:"CLEAR"
            anchors.bottom: btnGuardar.top
            anchors.right:  btnGuardar.right
            anchors.bottomMargin: 5
            color: Qt.darker(parent.color)
            onClicked: {
                nombre.input = "";
                tlf.input = "";
                fechaSeleccionable.input = "";
                archivoFoto.input = "";
            }
        }
        BotonClass{
            id: btnDefault
            texto:"DEFAULT POS"
            anchors.bottom: btnBuscar.top
            anchors.left:  btnBuscar.left
            anchors.bottomMargin: 5
            color: Qt.darker(parent.color)
            onClicked: {
                nombre.y = 0;
                tlf.y =65;
                fechaSeleccionable.y= 65*2;
                archivoFoto.y = 65*3;
            }
        }
        Rectangle{
            id: contenedorImagen
            anchors.right: btnBuscar.left
            anchors.left: parent.left
            height: 130
            anchors.margins: 5
            anchors.bottom: parent.bottom
            border.color: Qt.darker(parent.color)
            border.width: 3
            color:"#00000000"
            Text{
                id: textoImagenPlaceHolder
                anchors.centerIn: parent
                font.pixelSize: 50
                font.family: "Papyrus"
                text: "No Image"
            }
            Image{
                id: fotoSeleccionada
                anchors.margins: 3
                anchors.fill: parent
                source: archivoFoto.input
                fillMode: Image.PreserveAspectCrop
            }
        }
        Rectangle{
            id:mensajeGuia
            anchors.left: contenedorImagen.right
            anchors.bottom: btnDefault.top
            anchors.margins: 20
            anchors.right: btnClear.right
            Text{
                id:mensaje
                text:""
                anchors.centerIn: parent
                font.pixelSize: 15
            }
        }

        Dialog{
            id: calendario_dialogo
            height: 300
            width: 300
            background: Rectangle{
                color: calendario.color
                radius: 5
            }
            anchors.centerIn: parent
            Calendario{
                id:calendario
                color: Qt.darker(view.colorAg, 0.9)
                anchors.fill: parent

                onFechaseleccionada: (dia, mes, anyo) => {
                    print(dia + "/" + mes + "/" + anyo);
                    fechaSeleccionable.input = (dia<10?"0":"")+dia + "/" + (mes<10?"0":"")+mes + "/" + anyo;
                    calendario_dialogo.close();
                }
            }
        }
        Component.onCompleted:{
            inicializarDB();
            leerPosiciones();
        }
        Component.onDestruction: {
            guardarPosiciones();
        }
        function inicializarDB(){
            db = LocalStorage.openDatabaseSync("agenda.sql", "1.0", "base de datos de la agenda", 10000);
            db.transaction(function(transaction){
                console.log("Creando tabla");
                transaction.executeSql("CREATE TABLE IF NOT EXISTS agenda(nombre TEXT, telefono TEXT, birthday DATE, foto TEXT); ");
                //transaction.executeSql("CREATE TABLE IF NOT EXISTS pos(nombre TEXT, coordenadas TEXT); ");
                //"{'x':'123','y':'565'}"
                transaction.executeSql("CREATE TABLE IF NOT EXISTS posiciones(nombre TEXT, coordenadas TEXT); ");

            });
        }
        function guardarDatos(arraydatos){
            print("Guardando contacto ...");

            if(!db){
                print("DB inexistente.");
                return;
            }
            db.transaction(function (transaction){
                var resultado = transaction.executeSql("INSERT INTO agenda VALUES(?,?,?,?);", arraydatos);
            });
            print("Guardado con éxito.");
            mensaje.text = "Guardado con éxito.";
            timer.start();
        }
        function buscarDatos(nombreContacto){
            print("Buscando contacto ...");
            if(!db){
                print("DB inexistente.");
                return;
            }
            db.transaction(function (transaction){
                print("Leyendo DB...");
                var resultado = transaction.executeSql("SELECT * FROM agenda WHERE nombre='"+ nombreContacto +"';");
                if(resultado.rows.length >= 1){
                    var contacto = resultado.rows[0];
                    nombre.input = contacto.nombre;
                    tlf.input    = contacto.telefono;
                    fechaSeleccionable.input = contacto.birthday;
                    archivoFoto.input = contacto.foto;

                    mensaje.text="Datos cargados";
                    timer.start();
                }else{
                    print("No he encontrado nada.");
                    mensaje.text="No he encontrado nada";
                    timer.start();
                }
            });
        }
        function guardarPosiciones(){
            console.log("Guardando posiciones de campos");
            if(!db){
                return;
            }else{
                db.transaction(function(tranc){
                    var resultado1 = tranc.executeSql("select * from posiciones where nombre = 'posCampo1'");
                    var resultado2 = tranc.executeSql("select * from posiciones where nombre = 'posCampo2'");
                    var resultado3 = tranc.executeSql("select * from posiciones where nombre = 'posCampo2'");
                    var resultado4 = tranc.executeSql("select * from posiciones where nombre = 'posCampo2'");
                    var obj1 = {
                        x : nombre.x,
                        y : nombre.y
                    };
                    var obj2 = {
                        x : tlf.x,
                        y : tlf.y
                    }
                    var obj3 = {
                        x : fechaSeleccionable.x,
                        y : fechaSeleccionable.y
                    }
                    var obj4 = {
                        x : archivoFoto.x,
                        y : archivoFoto.y
                    }
                    if(resultado1.rows.length === 1){
                        console.log("Ya existen los datos. Se actualizan los datos de la tabla");
                        resultado1 = tranc.executeSql("update posiciones set coordenadas = ? where nombre = 'posCampo1'", [JSON.stringify(obj1)]);
                    }else{
                        console.log("Los datos todavia no existen. Se crea valor en la tabla");
                        resultado1 = tranc.executeSql("insert into posiciones values (?,?)", [ 'posCampo1' , [JSON.stringify(obj1)] ] );
                    }

                    if(resultado2.rows.length === 1){
                        console.log("Ya existen los datos. Se actualizan los datos de la tabla");
                        resultado2 = tranc.executeSql("update posiciones set coordenadas = ? where nombre = 'posCampo2'", [JSON.stringify(obj2)]);
                    }else{
                        console.log("Los datos todavia no existen. Se crea valor en la tabla");
                        resultado2 = tranc.executeSql("insert into posiciones values (?,?)", [ 'posCampo2' , [JSON.stringify(obj2)] ] );
                    }

                    if(resultado3.rows.length === 1){
                        console.log("Ya existen los datos. Se actualizan los datos de la tabla");
                        resultado3 = tranc.executeSql("update posiciones set coordenadas = ? where nombre = 'posCampo3'", [JSON.stringify(obj3)]);
                    }else{
                        console.log("Los datos todavia no existen. Se crea valor en la tabla");
                        resultado3 = tranc.executeSql("insert into posiciones values (?,?)", [ 'posCampo3' , [JSON.stringify(obj3)] ] );
                    }

                    if(resultado4.rows.length === 1){
                        console.log("Ya existen los datos. Se actualizan los datos de la tabla");
                        resultado4 = tranc.executeSql("update posiciones set coordenadas = ? where nombre = 'posCampo4'", [JSON.stringify(obj4)]);
                    }else{
                        console.log("Los datos todavia no existen. Se crea valor en la tabla");
                        resultado4 = tranc.executeSql("insert into posiciones values (?,?)", [ 'posCampo4' , [JSON.stringify(obj4)] ] );
                    }


                });
            }
        }
        function leerPosiciones(){
            console.log("Leyendo las posiciones guardada");
            if(!db){
                return;
            }else{
                db.transaction(function (transac){
                    console.log("Leyendo de la base de datos");
                    var result1 = transac.executeSql("select * from posiciones where nombre = 'posCampo1'");
                    var result2 = transac.executeSql("select * from posiciones where nombre = 'posCampo2'");
                    var result3 = transac.executeSql("select * from posiciones where nombre = 'posCampo3'");
                    var result4 = transac.executeSql("select * from posiciones where nombre = 'posCampo4'");
                    console.log("Length: "+result1.rows.length )
                    if (result1.rows.length === 1){
                        var valor1 = result1.rows[0].coordenadas;
                        var objJS1 = JSON.parse(valor1);
                        nombre.x = objJS1.x;
                        nombre.y = objJS1.y;
                    }
                    if (result2.rows.length === 1){
                        var valor2 = result2.rows[0].coordenadas;
                        var objJS2 = JSON.parse(valor2);
                        tlf.x = objJS2.x;
                        tlf.y = objJS2.y;
                    }
                    if (result3.rows.length === 1){
                        var valor3 = result3.rows[0].coordenadas;
                        var objJS3 = JSON.parse(valor3);
                        fechaSeleccionable.x = objJS3.x;
                        fechaSeleccionable.y = objJS3.y;
                    }
                    if (result4.rows.length === 1){
                        var valor4 = result4.rows[0].coordenadas;
                        var objJS4 = JSON.parse(valor4);
                        archivoFoto.x = objJS4.x;
                        archivoFoto.y = objJS4.y;
                    }

                });
            }
        }
    }
    Timer{
        id: timer
        interval: 1000
        running: false
        repeat: false
        onTriggered: {
            mensaje.text ="";
        }
    }
}

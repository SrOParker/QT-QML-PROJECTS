import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.LocalStorage
import QtQuick.Shapes

Window {
    id:application
    maximumHeight: 720
    minimumHeight: 720
    maximumWidth: 640
    minimumWidth: 640
    color: "#A9A9b2"
    visible: true
    title: "Ventas"
    property var dB
    property string nameUserLoged  : "USER"
    property string passUserLoged  : ""
    property string photoUserLoged : "https://cdn.pixabay.com/photo/2015/10/05/22/37/blank-profile-picture-973460_1280.png"
    Rectangle{
        id:rect_first
        anchors.fill: parent
        anchors.margins: 20
        color:"#A9a9b9"
        Rectangle{
            anchors.fill: parent
            anchors.margins: 20
            color:"#A9a9b9"
            StackView{
                id: stack

                initialItem: page_Principal

                anchors.fill: parent
            }

            Component{
                id: page_Principal

                Rectangle{
                    id:container1
                    color: rect_first.color
                    anchors.fill:page_Principal.parent
                    anchors.margins: 10

                    Campo{
                        id:login_nombre
                        label: "User"
                        width: parent.width
                        nextTab: login_pass.inputItem
                        prevTab: this
                        color: Qt.darker(rect_first.color, 1.2)

                        y: (application.height/2) - height*10
                    }
                    Campo{
                        id:login_pass
                        label: "Password"
                        width: parent.width
                        echoMode: TextInput.Password
                        color: Qt.darker(rect_first.color, 1.2)
                        nextTab: this
                        prevTab: login_nombre.inputItem
                        y: (application.height/2)-height*5
                    }

                    Button{
                        id: butt_new
                        anchors.top: login_pass.bottom
                        anchors.topMargin: 60
                        x: 145
                        text: "New User"
                        width: 100
                        height: 50
                        onClicked: {
                            stack.push(page_newuser);
                        }

                    }
                    Button {
                        anchors.top: login_pass.bottom
                        anchors.left: butt_new.right
                        anchors.topMargin: 60
                        anchors.leftMargin: 60
                        text: "LogIn"
                        width: 100
                        height: 50
                        onClicked: {
                            checkIfExistsToLogIn(login_nombre.input, login_pass.input);
                        }
                    }
                }


            }

            Component{
                id: page_newuser
                Rectangle{
                    id:container2
                    color: rect_first.color
                    anchors.fill:page_newuser.parent
                    anchors.margins: 10
                    Campo{
                        id: newname
                        label: "New User *"
                        width: parent.width

                        color: Qt.darker(rect_first.color, 1.2)
                        nextTab: newpass.inputItem
                        prevTab: this
                        y: (application.height/2) - height*15
                    }
                    Campo{
                        id: newpass
                        label: "New Password *"
                        width: parent.width
                        echoMode: TextInput.Password
                        color: Qt.darker(rect_first.color, 1.2)
                        nextTab: repass.inputItem
                        prevTab: newname.inputItem
                        y: (application.height/2) - height*10
                    }
                    Campo{
                        id: repass
                        label: "Repeat Password *"
                        width: parent.width
                        echoMode: TextInput.Password
                        color: Qt.darker(rect_first.color, 1.2)
                        nextTab: fotoinp.inputItem
                        prevTab: newpass.inputItem
                        y: (application.height/2) - height*5
                    }
                    Campo{
                        id: fotoinp
                        label: "Photo"
                        width: parent.width

                        color: Qt.darker(rect_first.color, 1.2)
                        nextTab: fotoinp.inputItem
                        prevTab: repass.inputItem
                        y: (application.height/2) - height
                        onInputChanged: {
                            fotoSeleccionada.source = fotoinp.input;
                        }
                    }
                    Rectangle{
                        id:container_photo
                        height: 130
                        anchors.left: container2.left
                        anchors.top: fotoinp.bottom
                        anchors.right: container2.right
                        anchors.margins: 75

                        border.color: Qt.darker(application.color)
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
                            //source: archivoFoto.input
                            fillMode: Image.PreserveAspectCrop
                        }

                    }
                    Button{
                        id: butt_cancel
                        anchors.top: container_photo.bottom
                        anchors.topMargin: 30
                        x: 170
                        text: "Cancel"
                        width: 100
                        height: 50
                        onClicked: {
                            stack.pop();
                        }

                    }
                    Button {
                        anchors.top: container_photo.bottom
                        anchors.left: butt_cancel.right
                        anchors.topMargin: 30
                        anchors.leftMargin: 60
                        text: "Create User"
                        width: 100
                        height: 50

                        onClicked: {
                            addToDB(newname.input, newpass.input, repass.input, fotoinp.input);

                        }
                    }
                }
            }

            Component{
                id: principal_page_loged
                Rectangle{
                    id:drawpage
                    color: rect_first.color
                    anchors.fill:principal_page_loged.parent
                    anchors.margins: 10
                    Drawer{
                        id:drawer
                        width: 0.66 * parent.width
                        height: parent.height

                        Rectangle{
                            color: "#DDDDDD"
                            anchors.fill: parent

                            Image{
                                height: parent.height/4
                                width: height
                                anchors.top: parent.top
                                anchors.topMargin: 50
                                anchors.horizontalCenter: parent.horizontalCenter
                                id:image_user_loged
                                //anchors.fill: parent
                                fillMode: Image.PreserveAspectCrop
                                source: application.photoUserLoged

                            }




                            Rectangle{
                                id:textuser
                                width: parent.width
                                height: 40
                                color: parent.color
                                anchors.top: image_user_loged.bottom
                                Text{
                                    id:textuserlabel
                                    anchors.centerIn: parent
                                    text:application.nameUserLoged
                                    font.pixelSize: 20

                                }
                            }

                            Button{
                                id:changepass
                                text: "Change Password"
                                width: 100
                                height: 50
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.top: textuser.bottom
                                anchors.margins: 10
                            }
                            Button{
                                id:changephoto
                                text: "Change Photo"
                                width: 100
                                height: 50
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.top: changepass.bottom
                                anchors.margins: 10
                            }
                            Button{
                                id:logoutbutton
                                text: "LogOut"
                                width: 100
                                height: 50
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.bottom: parent.bottom
                                anchors.margins: 10

                                onClicked: {
                                    stack.pop();
                                    application.passUserLoged ="";
                                    application.nameUserLoged="";
                                    application.photoUserLoged="";
                                }
                            }
                        }
                        onOpened: {
                            //RECARGA
                            //image_user_loged.source = application.photoUserLoged;
                            //textuserlabel.text = application.nameUserLoged;
                        }
                    }
                    Rectangle{
                        id:pageVentasContainer
                        width: parent.width
                        height: 100
                        anchors.horizontalCenter: parent.horizontalCenter
                        Rectangle{
                            anchors.centerIn: parent
                            width: parent.width
                            height: parent.height/3
                            ComboBox {
                                id:dropdownProductos
                                textRole: "producto"

                                //model
                                model:ListModel{
                                        id:lmod
                                        ListElement{producto:"Seleccione item"; value:0}
                                        //ListElement{producto:"EE"; value:0}
                                    }

                                width: parent.width / 1.5
                                height: parent.width / 20
                                font.pixelSize: 14
                                anchors.left: parent.left
                                anchors.leftMargin: 50
                                Component.onCompleted:{
                                    loadDropDownProducts();
                                }
                            }

                            SpinBox{
                                id: spinCount
                                height: dropdownProductos.height
                                width: parent.width/10
                                anchors.left: dropdownProductos.right
                                anchors.leftMargin: 20
                            }

                        }


                    }
                    Button{
                        width: 100
                        height: 50
                        text: "COMPRAR"
                        anchors.top: pageVentasContainer.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: 20
                        onClicked: {
                            sellProductsToUser();
                            viewSales();
                        }
                    }
                    function loadDropDownProducts(){
                        if(!dB){
                            return;
                        }else{
                            dB.transaction(function(tranc){
                                var resultado = tranc.executeSql("select * from products");

                                for(var i=0; i<resultado.rows.length;i++){
                                    lmod.append({"producto": resultado.rows[i].product, "value":resultado.rows[i].price});
                                    //console.log(resultado.rows[i].price);
                                }

                            });
                        }

                    }
                    function sellProductsToUser(){
                        console.log("Guardando pedido y venta");
                        if(!dB){
                            return;
                        }else{
                            dB.transaction(function(tranc){
                                var resultado = tranc.executeSql("select * from products where product='"+ dropdownProductos.currentText +"'");
                                var price = spinCount.value * resultado.rows[0].price;
                                tranc.executeSql("insert into sales values (?,?,?,?)", [ application.nameUserLoged ,
                                                                                        dropdownProductos.currentText ,
                                                                                        spinCount.value,
                                                                                        price] );
                                console.log("Venta guardada");
                                //sales(user Text, product Text, amount Int, totalPrice Int)


                            });
                        }
                    }
                    function viewSales(){
                        console.log("VENTAS");
                        if(!dB){
                            return;
                        }else{
                            dB.transaction(function(tranc){
                                var resultado = tranc.executeSql("select * from sales");

                                for(var i=0; i < resultado.rows.length;i++){
                                    console.log("-> USER: "+resultado.rows[i].user+ " PRODUCT: "+
                                                resultado.rows[i].product+ " AMOUNT: "+
                                                resultado.rows[i].amount+ " TOTAL PRICE: "+
                                                resultado.rows[i].totalPrice);
                                }
                            });
                        }
                    }
                }

            }
        }
    }


    MessageDialog{
        id:dialogo1
        //anchors.centerIn: parent
        title: "ERROR"

        text: "No se puede iniciar sesión"
        detailedText: "Prueba a reescribir la contraseña"
        informativeText: "La contraseña o el usuario es incorrecto"

    }
    MessageDialog{
        id:dialogo2
        //anchors.centerIn: parent
        title: "ERROR"

        text: "No se puede crear"
        detailedText: "Crea un nuevo usuario o retrocede y accede con uno existente"
        informativeText: "El usuario que intentas crear ya existe"

    }
    MessageDialog{
        id:dialogo3
        //anchors.centerIn: parent
        title: "CREADO CORRECTAMENTE"

        text: "Disfrute de la aplicación"

    }
    MessageDialog{
        id:dialogo4
        //anchors.centerIn: parent
        title: "ERROR"

        text: "No coinciden las contraseñas"

    }
    //DATABASE
    function inicializarDB(){
        dB = LocalStorage.openDatabaseSync("C:\\Users\\aurec\\Documents\\Laure\\QT GIT\\QT-QML-PROJECTS\\SQL\\VentasDB", "1.0", "base de datos para guardar usuarios de la aplicacion",20);
        dB.transaction(function(transac){
            console.log("Comprobando tabla");
            transac.executeSql("CREATE TABLE IF NOT EXISTS users(user Text, password Text, photo Text)");
            transac.executeSql("CREATE TABLE IF NOT EXISTS products(product Text, price Int)");
            transac.executeSql("CREATE TABLE IF NOT EXISTS sales(user Text, product Text, amount Int, totalPrice Int)");
        });
    }
    function addToDBInitialProducts(){
        console.log("Creando productos");
        if(!dB){
            return;
        }else{
            dB.transaction(function(tranc){
                var resultado = tranc.executeSql("select * from products");

                if (resultado.rows.length===0){
                    tranc.executeSql("insert into products values (?,?)", [ "Naranja" , "1"] );
                    tranc.executeSql("insert into products values (?,?)", [ "Melón" , "2"] );
                    tranc.executeSql("insert into products values (?,?)", [ "Melocotón" , "1"] );
                    tranc.executeSql("insert into products values (?,?)", [ "Piña" , "3"] );
                    tranc.executeSql("insert into products values (?,?)", [ "Mango" , "1"] );
                    tranc.executeSql("insert into products values (?,?)", [ "Sandía" , "4"] );
                 }

            });
        }
    }

    function addToDB(userInput, pass1, pass2, photo){
        console.log("Intentando crear user");
        if(!dB){
            return;
        }else{
            dB.transaction(function(tranc){
                var resultado = tranc.executeSql("select * from users where user = '"+userInput+"'");

                if(resultado.rows.length === 1){
                    console.log("El usuario existe");
                    //dialogo con boton de aceptar
                    dialogo2.open();
                }else{
                    if(pass1 === pass2){
                        console.log("Los datos todavia no existen. Se crea usuario en la tabla");
                        resultado = tranc.executeSql("insert into users values (?,?,?)", [ userInput , pass1, photo ] );
                        //dialogo creado correctamente
                        dialogo3.open();
                        stack.pop();

                    }else{
                        dialogo4.open();
                        //dialogo las contraseñas no coinciden
                    }

                }
            });
        }
    }
    function checkIfExistsToLogIn(name, pass){
        console.log("Intentando acceder");
        if(!dB){
            return;
        }else{
            dB.transaction(function(tranc){
                var resultado = tranc.executeSql("select * from users where user = '"+name+"' and password = '"+pass+"'");

                if(resultado.rows.length === 1){
                    console.log("El usuario existe y es correcto");
                    stack.push(principal_page_loged);
                    application.nameUserLoged = name;
                    application.passUserLoged = pass;
                    var h = resultado.rows[0].photo;
                    //application.photoUserLoged = resultadoPhoto.rows[0].photo;
                    if(h!=""){
                        var path =h.toString();
                                // remove prefixed "file:///"
                                path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
                                // unescape html codes like '%23' for '#'
                                application.photoUserLoged = decodeURIComponent(path);
                                //console.log(application.photoUserLoged);
                        //console.log(application.photoUserLoged);
                    }else{
                        application.photoUserLoged = "https://cdn.pixabay.com/photo/2015/10/05/22/37/blank-profile-picture-973460_1280.png"
                    }

                    addToDBInitialProducts();

                }else{
                    console.log("El usuario no existe o es incorrecto");

                    //dialogo que lo muestre
                    dialogo1.open();
                }
            });
        }
    }


    Component.onCompleted:{
        inicializarDB();
    }
}

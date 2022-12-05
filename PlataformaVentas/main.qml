import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Dialogs
import QtQuick.Controls
import QtQuick.LocalStorage

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

                        color: Qt.darker(rect_first.color, 1.2)

                        y: (application.height/2) - height*10
                    }
                    Campo{
                        id:login_pass
                        label: "Password"
                        width: parent.width
                        echoMode: TextInput.Password
                        color: Qt.darker(rect_first.color, 1.2)

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

                        y: (application.height/2) - height*15
                    }
                    Campo{
                        id: newpass
                        label: "New Password *"
                        width: parent.width
                        echoMode: TextInput.Password
                        color: Qt.darker(rect_first.color, 1.2)

                        y: (application.height/2) - height*10
                    }
                    Campo{
                        id: repass
                        label: "Repeat Password *"
                        width: parent.width
                        echoMode: TextInput.Password
                        color: Qt.darker(rect_first.color, 1.2)

                        y: (application.height/2) - height*5
                    }
                    Campo{
                        id: fotoinp
                        label: "Photo"
                        width: parent.width

                        color: Qt.darker(rect_first.color, 1.2)

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
                            anchors.fill: parent
                            Image{
                                id:image_user_loged
                                height: parent.height/4
                                width: height
                                anchors.top: parent.top
                                anchors.topMargin: 50
                                anchors.horizontalCenter: parent.horizontalCenter
                                fillMode: Image.PreserveAspectFit
                                source: application.photoUserLoged

                            }
                            Rectangle{
                                id:textuser
                                width: parent.width
                                height: 40
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
        });
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

                    var path =h.toString();
                            // remove prefixed "file:///"
                            path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
                            // unescape html codes like '%23' for '#'
                            application.photoUserLoged = decodeURIComponent(path);
                            console.log(application.photoUserLoged);
                    //console.log(application.photoUserLoged);
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

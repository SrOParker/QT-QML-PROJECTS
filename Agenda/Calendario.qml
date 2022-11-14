import QtQuick

Item {
    id: contenedorCalendario
    property alias color: rectanguloSeleccionador.color
    property var months: ["Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"]
    property int currentMonth
    property int year
    property bool monthShown: true
    signal fechaseleccionada(int dia, int mes, int anyo)
    Component.onCompleted: {
        var fecha = new Date();
        contenedorCalendario.year = fecha.getFullYear();
        contenedorCalendario.currentMonth = fecha.getMonth();

        populateModel();
    }
    Rectangle{
        id: rectanguloSeleccionador
        width: parent.width
        height: parent.height / 7
        radius: 5
        color: "white"

        Rectangle{
            id: rectangleMonthYear
            height: parent.height
            anchors.left: decrementarMes.right
            anchors.right: incrementarMes.left
            color: parent.color
            Text{
                id: textMonthYear
                text: monthShown ? contenedorCalendario.months[currentMonth] : contenedorCalendario.year.toString()
                anchors.centerIn: parent
                color: Qt.darker(parent.color, 4)
                font.pixelSize: parent.height/3
            }
            Text{
                id:textYearMonth
                text: monthShown ? contenedorCalendario.year.toString() : contenedorCalendario.months[currentMonth]
                color: Qt.darker(parent.color, 4)
                anchors.left: textMonthYear.right
                anchors.bottom: parent.bottom
                font.pixelSize: parent.height/5
            }
            MouseArea{
                id:mouseAreaTextMonthYear
                property string tex:""
                onClicked: {
                    monthShown = !monthShown;
                }
            }
        }
        BotonClass{
            id:incrementarMes
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 10
            texto:">"
            height:( parent.height / 7 ) * 5
            width: (parent.width / 5)
            color:  Qt.darker(rectanguloSeleccionador.color, 1.2)
            radius: height/2
            onClicked: {
                if(monthShown){
                    contenedorCalendario.currentMonth += 1;
                    if(contenedorCalendario.currentMonth>11){
                        contenedorCalendario.currentMonth = 0;
                        contenedorCalendario.year = contenedorCalendario.year + 1;
                    }
                }else{
                    contenedorCalendario.year++;
                }
                populateModel();
            }
        }
        BotonClass{
            id:decrementarMes
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 10
            height:( parent.height / 7 ) * 5
            width: (parent.width / 5)
            texto:"<"
            color:  Qt.darker(rectanguloSeleccionador.color, 1.2)
            radius: height/2
            onClicked: {
                if(monthShown){
                    contenedorCalendario.currentMonth -= 1;
                    if(contenedorCalendario.currentMonth < 0){
                        contenedorCalendario.currentMonth = 11;
                        contenedorCalendario.year = contenedorCalendario.year - 1;
                    }
                }else{
                    contenedorCalendario.year--;
                }
                populateModel();
            }
        }


    }
    Rectangle{
        id:rectanguloCalendario
        color: Qt.darker(rectanguloSeleccionador.color, 4)
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: rectanguloSeleccionador.bottom
        anchors.bottom: parent.bottom

        GridView{
            id: vistaCalendario

            anchors.fill: parent
            //model :42
            cellWidth: Math.round(rectanguloCalendario.width   / 7)
            cellHeight: Math.round(rectanguloCalendario.height / 6)
            delegate: Rectangle{
                id:rectanguloDelegado
                color: rectanguloSeleccionador.color
                width: vistaCalendario.cellWidth
                height: vistaCalendario.cellHeight
                required property int modelData
                required property int index
                Rectangle{
                    id: rectanguloInternoDelegado
                    anchors.fill: parent
                    anchors.margins: calendario.width/200
                    radius: calendario.width/100
                    color: Qt.darker(parent.color,1.1)

                    Text{
                        id:fechadelegado
                        text: rectanguloDelegado.modelData
                        anchors.centerIn: parent
                        font.pixelSize: rectanguloInternoDelegado.height / 5
                    }
                    MouseArea{
                        id:mouseAreaRecInternoDelegado
                        anchors.fill: parent
                        onClicked: {
                            //print(modelData + "/" + (currentMonth+1)+ "/" + year);
                            if( modelData > 15 && index < 6){
                                calendario.fechaseleccionada(modelData, currentMonth, year);
                            }else if(modelData < 15 && index > 27){
                                calendario.fechaseleccionada(modelData, currentMonth+2, year);
                            }else{
                                calendario.fechaseleccionada(modelData, currentMonth+1, year);
                            }

                        }
                    }
                }

            }
        }
    }


    //FUNCTIONS JS
    function populateModel(){
        var modeloLocal = [];
        var fechalocal = new Date(year, currentMonth, 1);
        fechalocal.setDate(1);
        if(fechalocal.getDay() > 1){
            fechalocal.setTime(fechalocal.getTime() - 24*3600*1000*(fechalocal.getDay() - 1 ));
        }else if (fechalocal.getDay() < 1){
            fechalocal.setTime(fechalocal.getTime() - 24*3600*1000*6);
        }
        for (var i=0;i<42;i++){
            modeloLocal.push(fechalocal.getDate(i));
            fechalocal.setTime(fechalocal.getTime() +24*3600000);
        }
        vistaCalendario.model = modeloLocal;
        //print(fechalocal);

    }
}

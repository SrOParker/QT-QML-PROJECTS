import QtQuick
import QtQuick.Window
import QtQuick.Controls //dialogos
Window {
    id: view
    width: 640
    height: 480
    visible: true
    title: "Agenda SQL"
    property alias colorAg: agenda.color
    Rectangle{
        id: agenda
        anchors.fill: parent
        anchors.margins: 5
        color:"#AAddAA"
        CampoInput{
            id:nombre
            label: "Nombre"
            width: parent.width
            color: Qt.darker(view.colorAg, 1.2)
            visibleButton: false
        }
        CampoInput{
            id:fechaSeleccionable
            label:"Fecha"
            width: parent.width
            color: Qt.darker(view.colorAg, 1.2)
            y: 65
            nameButton: "SELECCIONAR"
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
                fechaSeleccionable.input = dia + "/" + mes + "/" + anyo;
                calendario_dialogo.close();
            }

        }
    }
    }
}

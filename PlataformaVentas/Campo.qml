import QtQuick

Item {
    id: item_campo
    property alias color: rectInput.color
    property alias label: nombreLabel.text
    property alias input: inputTe.text
    property bool  clickeable: true
    property alias echoMode : inputTe.echoMode


    property alias inputItem: inputTe
    property var nextTab: inputTe
    property var prevTab: inputTe

    height: campo1.height
    Rectangle{
        id:campo1
        width: application.width
        height: 20
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#00000000"
        Text{
            id: nombreLabel
            height: 20
            width: parent.width
            anchors.top: parent.top
            anchors.left: parent.left
            text: ""
            verticalAlignment: TextInput.AlignVCenter
            anchors.leftMargin: 5
        }


        Rectangle{
            id: rectInput
            width: application.width
            height: 45
            anchors.top: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            radius: 5
            TextInput{
                id: inputTe
                anchors.fill: parent
                verticalAlignment: TextInput.AlignVCenter
                anchors.leftMargin: 5
                font.pixelSize: 20
                clip: true
                KeyNavigation.tab: nextTab
                KeyNavigation.backtab: prevTab
                //passwordCharacter: "·"
                //anchors.top: nombreLabel.bottom
                MouseArea{
                    id:mouseAreaInput
                    anchors.fill: parent

                    hoverEnabled: true
                    cursorShape: Qt.IBeamCursor

                    onClicked: {
                        inputTe.focus = true;

                    }
                }
            }
        }



    }

}

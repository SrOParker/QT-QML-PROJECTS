import QtQuick

Item {
    id : campo
    width: parent.width
    height:60
    anchors.topMargin: 5
    anchors.bottomMargin: 5
    property alias color: campoBackground.color
    property alias label: label.text
    Rectangle{
        id: campoBackground
        width: parent.width / 1.1
        height: parent.height
        anchors.centerIn: parent
        radius: 20
        Text{
            id:label
            text: "Placeholder"
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 5
            font.pixelSize: 12
            font.bold: true
        }
        Rectangle{
            anchors.fill: parent
            anchors.topMargin: 22
            anchors.leftMargin:20
            anchors.rightMargin:20
            anchors.bottomMargin: 15
            radius: 10
            color: Qt.lighter(campoBackground.color)
            TextInput{
                anchors.fill: parent
                anchors.topMargin: 5
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                clip: true

            }
        }

    }
}

import QtQuick 2.4

Item {
    width: 400
    height: 400

    Grid {
        id: grid
        anchors.fill: parent
        rows: 2
        columns: 2

        Rectangle {
            id: rectangle
            width: 200
            height: 200
            color: "#e46868"
            visible: true
        }

        Rectangle {
            id: rectangle1
            width: 200
            height: 200
            color: "#4d4a83"
        }

        Rectangle {
            id: rectangle2
            width: 200
            height: 200
            color: "#acdcc4"
        }

        MouseArea {
            id: mouseArea
            width: 100
            height: 100
        }
    }

    Text {
        id: element
        x: 235
        y: 346
        width: 165
        height: 54
        color: "#478f39"
        text: qsTr("TEST TEXT")
        font.bold: true
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 27
    }
}

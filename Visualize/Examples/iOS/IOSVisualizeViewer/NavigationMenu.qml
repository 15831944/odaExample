import QtQuick 2.6
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle{
    id: navMenu
    color: "#ccf9f8f8"
    border.color: "transparent"
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.rightMargin: 20
    height: 55
    width: parent.width
    visible: false

    function setStartButtonBorder(){
        panBtn.background.visible = true;
    }

    function resetBorderForButtons(){
        panBtn.background.visible = false;
        orbitBtn.background.visible = false;
        zoomWindowBtn.background.visible = false;
        zoomExtentsBtn.background.visible = false;
    }

    property variant renderPage

    property int iconSize: 40
    property int rightMarginProp: width * 0.07

    ColumnLayout {
        anchors.fill: parent

    RowLayout{
        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

        Button{
            id: panBtn
            icon.source: "qrc:/icons/pan.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            Layout.rightMargin: navMenu.rightMarginProp
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: true
            }

            onClicked: {
                navMenu.resetBorderForButtons();
                background.visible = true;
                renderPage.panelButtonPressed("pan");
            }
        }

        Button{
            id: orbitBtn
            icon.source: "qrc:/icons/orbit.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            Layout.rightMargin: navMenu.rightMarginProp
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: false
            }

            onClicked: {
                navMenu.resetBorderForButtons();
                background.visible = true;
                renderPage.panelButtonPressed("orbit");
            }
        }

        Button{
            id: zoomWindowBtn
            icon.source: "qrc:/icons/zoomWindow.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            Layout.rightMargin: navMenu.rightMarginProp
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: false
            }

            onClicked: {
                navMenu.resetBorderForButtons();
                background.visible = true;
                renderPage.panelButtonPressed("zoomWindow");
            }
        }

        Button{
            id: zoomExtentsBtn
            icon.source: "qrc:/icons/zoomExtents.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                anchors.fill: parent
                color: "transparent"
            }

            onClicked: {
                renderPage.panelButtonPressed("zoomExtents");
            }
        }

    }
    }
}

import QtQuick 2.6
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle{
    id: styleMenu
    color: "#ccf9f8f8"
    border.color: "transparent"
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.rightMargin: 20
    height: 60
    width: parent.width
    visible: false

    property variant renderPage

    property int iconSize: 35

    function resetButtonsBorders() {
        optimized2d.background.visible = false;
        wireframe3d.background.visible = false;
        hiddenLine.background.visible = false;
        shaded.background.visible = false;
        gouraudShaded.background.visible = false;
        shadedWithEdges.background.visible = false;
        gouraudShadedWithEdges.background.visible = false;
    }

    function setRenderModeType(renderMode) {
        resetButtonsBorders();
        if(renderMode == "2DOptimized")
            optimized2d.background.visible = true;
        else if(renderMode == "Wireframe")
            wireframe3d.background.visible = true;
        else if(renderMode == "HiddenLine")
            hiddenLine.background.visible = true;
        else if(renderMode == "FlatShaded")
            shaded.background.visible = true;
        else if(renderMode == "GouraudShaded")
            gouraudShaded.background.visible = true;
        else if(renderMode == "FlatShadedWithWireframe")
            shadedWithEdges.background.visible = true;
        else if(renderMode == "GouraudShadedWithWireframe")
            gouraudShadedWithEdges.background.visible = true;
    }

    RowLayout{
        anchors.fill: parent

        Rectangle {
            color:"transparent"
            Layout.fillWidth: true
        }

        Button{
            id: optimized2d
            icon.source: "qrc:/icons/2dwireframe.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: false
            }

            onClicked: {
                resetButtonsBorders();
                background.visible = true;
                renderPage.panelButtonPressed("2dwireframe");
            }
        }

        Button{
            id: wireframe3d
            icon.source: "qrc:/icons/3dwireframe.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: false
            }

            onClicked: {
                resetButtonsBorders();
                background.visible = true;
                renderPage.panelButtonPressed("3dwireframe");
            }
        }

        Button{
            id: hiddenLine
            icon.source: "qrc:/icons/hiddenline.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: false
            }

            onClicked: {
                resetButtonsBorders();
                background.visible = true;
                renderPage.panelButtonPressed("hiddenline");
            }
        }

        Button{
            id: shaded
            icon.source: "qrc:/icons/shaded.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: false
            }

            onClicked: {
                resetButtonsBorders();
                background.visible = true;
                renderPage.panelButtonPressed("shaded");
            }
        }

        Button{
            id: gouraudShaded
            icon.source: "qrc:/icons/gouraudShaded.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: false
            }

            onClicked: {
                resetButtonsBorders();
                background.visible = true;
                renderPage.panelButtonPressed("gouraudShaded");
            }
        }

        Button{
            id: shadedWithEdges
            icon.source: "qrc:/icons/shadedWithEdges.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: false
            }

            onClicked: {
                resetButtonsBorders();
                background.visible = true;
                renderPage.panelButtonPressed("shadedWithEdges");
            }
        }

        Button{
            id: gouraudShadedWithEdges
            icon.source: "qrc:/icons/gouraudShadedWithEdges.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                height: 2
                color: "gray"
                visible: false
            }

            onClicked: {
                resetButtonsBorders();
                background.visible = true;
                renderPage.panelButtonPressed("gouraudShadedWithEdges");
            }
        }

        Rectangle {
            color:"transparent"
            Layout.fillWidth: true
        }

    }
}

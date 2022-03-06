import QtQuick 2.6
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle{
    id: markupMenu
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
    property variant headerToolBarMenu

    property int iconSize: 35

    function resetButtonsBorders() {
        rectId.background.visible = false;
        circId.background.visible = false;
        handleId.background.visible = false;
        cloudId.background.visible = false;
        txtId.background.visible = false;
    }

    RowLayout{
        anchors.fill: parent
        spacing: 0

        Rectangle {
            color:"transparent"
            Layout.fillWidth: true
        }

        Button{
            id: rectId
            icon.source: "qrc:/icons/markupRect.png"
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

                headerToolBarMenu.checkButtonBar();
                renderPage.panelButtonPressed("markupRect");
            }
        }

        Button{
            id: circId
            icon.source: "qrc:/icons/markupCirc.png"
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

                headerToolBarMenu.checkButtonBar();
                renderPage.panelButtonPressed("markupCirc");
            }
        }

        Button{
            id: handleId
            icon.source: "qrc:/icons/markupHandle.png"
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

                headerToolBarMenu.checkButtonBar();
                renderPage.panelButtonPressed("markupHandle");
            }
        }

        Button{
            id: cloudId
            icon.source: "qrc:/icons/markupCloud.png"
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

                renderPage.panelButtonPressed("markupCloud");
                headerToolBarMenu.activateDraggerDoneButton("Done");
            }
        }

        Button{
            id: txtId
            icon.source: "qrc:/icons/markupText.png"
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

                headerToolBarMenu.checkButtonBar();
                renderPage.panelButtonPressed("markupText");
            }
        }

        Button{
            icon.source: "qrc:/icons/markupSave.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                color: "transparent"
            }

            onClicked: {
                headerToolBarMenu.checkButtonBar();
                renderPage.panelButtonPressed("markupSave");
            }
        }

        Button{
            icon.source: "qrc:/icons/markupLoad.png"
            icon.width: iconSize
            icon.height: iconSize
            icon.color: "transparent"
            background: Rectangle{
                color: "transparent"
            }

            onClicked: {
                headerToolBarMenu.checkButtonBar();
                renderPage.panelButtonPressed("markupLoad");
            }
        }

        Rectangle {
            color:"transparent"
            Layout.fillWidth: true
        }

    }
}

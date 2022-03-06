import QtQuick 2.6
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

ToolBar {
    id: footerToolbar
    background: Rectangle {
        anchors.fill: parent
        color : "#C8546299"
    }

    objectName: "footerToolBar"

    property variant explorerBtn
    property variant projectionBtn
    property variant topToolLabel
    property variant tviController
    property variant pageStack
    property variant headerToolBarMenu

    property variant viewMenu
    property variant navMenu
    property variant regenMenu
    property variant styleMenu
    property variant markupMenu

    property ToolButton naviBtn: naviBtn

    function disableFileBar(bDisable){
        // on/off header toolbar buttons
        projectionBtn.visible = bDisable;

        // on/off footer tool bar buttons
        viewBtn.enabled = bDisable;
        naviBtn.enabled = bDisable;
        regenBtn.enabled = bDisable;
        styleBtn.enabled = bDisable;
        markupBtn.enabled = bDisable;
    }

    function setButtonActive(btnName){
        fileBtn.icon.color = "white";
        viewBtn.icon.color = "white";
        naviBtn.icon.color = "white";
        regenBtn.icon.color = "white";
        styleBtn.icon.color = "white";
        markupBtn.icon.color = "white";

        btnName.icon.color = "#d1933c";
    }

    function resetMenus( menuType ){
        if(menuType !== viewMenu)
            viewMenu.visible = false;
        if(menuType !== navMenu)
            navMenu.visible = false;
        if(menuType !== regenMenu)
            regenMenu.visible = false;
        if(menuType !== styleMenu)
            styleMenu.visible = false;
        if(menuType !== markupMenu)
            markupMenu.visible = false;
    }

    RowLayout {
        anchors.fill: parent

        ToolButton{
            id: fileBtn
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter
            icon.source: "qrc:/icons/fileMenu.png"
            icon.width: 40
            icon.height: 40
            icon.color: "#d1933c"

            background: Rectangle{
                color: "transparent"
            }

            onClicked: {
                topToolLabel.text = "Files";
                footerToolbar.setButtonActive(fileBtn);
                if(tviController.closeFileEvent()){
                    headerToolBarMenu.hideHeaderFileInfoPanel();
                    pageStack.pop();
                    footerToolbar.disableFileBar( false );
                    footerToolbar.resetMenus(null);
                    navMenu.resetBorderForButtons();
                    navMenu.setStartButtonBorder();
                }
            }
        }

        ToolButton{
            id: viewBtn
            Layout.fillWidth: true
            enabled: false
            icon.source: "qrc:/icons/viewMenu.png"
            icon.width: 40
            icon.height: 40
            icon.color: "white"

            background: Rectangle{
                color: "transparent"
            }

            onClicked: {
                topToolLabel.text = "View";
                footerToolbar.setButtonActive(viewBtn);
                footerToolbar.resetMenus(viewMenu);
                viewMenu.visible = !viewMenu.visible;
            }
        }

        ToolButton{
            id: naviBtn
            Layout.fillWidth: true
            enabled: false
            icon.source: "qrc:/icons/naviMenu.png"
            icon.width: 40
            icon.height: 40
            icon.color: "white"

            background: Rectangle{
                color: "transparent"
            }

            onClicked: {
                topToolLabel.text = "Navigation";
                footerToolbar.setButtonActive(naviBtn);
                footerToolbar.resetMenus(navMenu);
                navMenu.visible = !navMenu.visible;
            }
        }

        ToolButton{
            id: markupBtn
            Layout.fillWidth: true
            enabled: false
            icon.source: "qrc:/icons/markupMenu.png"
            icon.width: 40
            icon.height: 40
            icon.color: "white"

            background: Rectangle{
                color: "transparent"
            }

            onClicked: {
                topToolLabel.text = "Markup";
                footerToolbar.setButtonActive(markupBtn);
                footerToolbar.resetMenus(markupMenu);
                markupMenu.visible = !markupMenu.visible;
            }
        }

        ToolButton{
            id: regenBtn
            Layout.fillWidth: true
            enabled: false
            icon.source: "qrc:/icons/regenMenu.png"
            icon.width: 40
            icon.height: 40
            icon.color: "white"

            background: Rectangle{
                color: "transparent"
            }

            onClicked: {
                topToolLabel.text = "Regen";
                footerToolbar.setButtonActive(regenBtn);
                footerToolbar.resetMenus(regenMenu);
                regenMenu.visible = !regenMenu.visible;
            }
        }

        ToolButton{
            id: styleBtn
            Layout.fillWidth: true
            enabled: false
            icon.source: "qrc:/icons/styleMenu.png"
            icon.width: 40
            icon.height: 40
            icon.color: "white"

            background: Rectangle{
                color: "transparent"
            }

            onClicked: {
                topToolLabel.text = "Style";
                footerToolbar.setButtonActive(styleBtn);
                footerToolbar.resetMenus(styleMenu);
                styleMenu.visible = !styleMenu.visible;
            }
        }

    }

}


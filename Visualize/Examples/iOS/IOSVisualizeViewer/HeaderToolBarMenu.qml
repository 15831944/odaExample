import QtQuick 2.6
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

ToolBar {
    id: headerToolbar
    background: Rectangle {
        anchors.fill: parent
        color : "#94b9c2e2"
    }
    objectName: "headerToolBar"
    height: 73

    property variant renderPage
    property variant filePage
    property variant pageStack

    property Label topToolLabel: topToolLabel
    property ToolButton projectionBtn: projectionBtn

    function setHeaderFileInfoPanel(fileNameStr) {
        fileInfoLayout.visible = true;
        fileNameLbl.text = fileNameStr;
    }

    function setTotalTime(totalTimeStr) {
        totalTimeLbl.text = totalTimeStr;
    }

    function hideHeaderFileInfoPanel() {
        fileInfoLayout.visible = false;
    }

    function activateDraggerDoneButton(buttonText) {
        projectionBtn.visible = false;
        findBtn.visible = false;
        draggerDoneBtn.text = buttonText;
        draggerDoneBtn.visible = true;
    }

    function checkButtonBar() {
        if(draggerDoneBtn.visible) {
            draggerDoneBtn.visible = false;
            projectionBtn.visible = true;
        }
    }

    function setProjectionButton(isPerspective) {
        projectionBtn.isPerspective = isPerspective;
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        RowLayout {
            Layout.alignment: Qt.AlignVCenter

            ToolButton {
                id: settingsBtn
                icon.source: "qrc:/icons/settings.png"
                icon.width: 35
                icon.height: 35
                icon.color: "transparent"
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    if(pageStack.currentItem === filePage)
                        filePage.appearanceSettingsVisible = true;
                    else if(pageStack.currentItem === renderPage)
                        renderPage.appearanceSettingsVisible = true;
                }
            }

            ToolButton {
                id: saveBtn
                icon.source: "qrc:/icons/save.png"
                icon.width: 35
                icon.height: 35
                icon.color: "transparent"
                visible: !findBtn.visible
                background: Rectangle {
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.showSaveDlg();
                }

            }

            Label{
                id: topToolLabel
                text: "Files"
                font.pixelSize: 18
                horizontalAlignment: "AlignHCenter";
                Layout.fillWidth: true
            }

            ToolButton{
                id: findBtn
                icon.source: "qrc:/icons/find.png"
                icon.width: 35
                icon.height: 35
                icon.color: "transparent"
                Layout.rightMargin: 10
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    filePage.searchFieldVisible = !filePage.searchFieldVisible;
                }
            }

            ToolButton {
                id: draggerDoneBtn
                text: "Done"
                font.pixelSize: 18
                visible: false
                background: Rectangle {
                    anchors.fill: parent
                    color: "#e1a4aed7"
                }
                Layout.rightMargin: 5

                onClicked: {
                    tviController.onDraggerDonePressed();
                    tviController.draggerFinished();
                    visible = false;
                    projectionBtn.visible = true;
                }
            }

            ToolButton{
                id: projectionBtn
                icon.source: "qrc:/icons/isometric.png"
                icon.width: 40
                icon.height: 40
                icon.color: "transparent"
                visible: false
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                property bool isPerspective: false

                onVisibleChanged: {
                    findBtn.visible = !visible;
                }

                onIsPerspectiveChanged: {
                    if(isPerspective) {
                        icon.source = "qrc:/icons/perspective.png"
                        isPerspective = true;
                        renderPage.panelButtonPressed("perspective");
                    }
                    else{
                        icon.source = "qrc:/icons/isometric.png"
                        isPerspective = false;
                        renderPage.panelButtonPressed("isometric");
                    }
                }

                onClicked: {
                    isPerspective = !isPerspective;
                }
            }

        }

        RowLayout {
            id: fileInfoLayout
            Layout.alignment: Qt.AlignBottom
            spacing: 0
            visible: false
            Label {
                id: fileNameLbl
                text: "No file"
                font.pixelSize: 18
                Layout.fillWidth: true
                background: Rectangle{
                    anchors.fill: parent
                    color: "#bfc0c3d1"
                }
            }
            Label {
                text: "Total time:"
                font.pixelSize: 18
                background: Rectangle{
                    anchors.fill: parent
                    color: "#bfc0c3d1"
                }
            }
            Label {
                id: totalTimeLbl
                text: "20.0s"
                font.pixelSize: 18
                background: Rectangle{
                    anchors.fill: parent
                    color: "#bfc0c3d1"
                }
            }
        }

    }
}

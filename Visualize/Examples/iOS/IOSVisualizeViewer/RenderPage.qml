import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import TvDeviceUnderQML 1.0

Page{
    id: renderPage
    objectName: "renderPage"
    background: Rectangle{
        anchors.fill: parent
        color: "transparent"
    }

    property variant headerToolBarMenu
    property variant footerToolBarMenu
    property variant pageStack
    property variant filePage

    property TviController tviController: tviController
    property Rectangle navMenu: navMenu
    property Rectangle viewMenu: viewMenu
    property Rectangle regenMenu: regenMenu
    property Rectangle styleMenu: styleMenu
    property Rectangle markupMenu: markupMenu

    property alias appearanceSettingsVisible: appearanceSettings.visible

    MessageDialog {
        id: messageDialogId
    }

    signal panelButtonPressed(string buttonName);
    signal unblockRenderSg();

    function showSaveDlg() {
        saveDialog.setSaveFilename(filePage.displayFileName);
        saveDialog.visible = true;
    }

    TextEdit {
        id: txtInput
        visible: false
        wrapMode: TextInput.WrapAnywhere

        onTextChanged: {
            tviController.onTextChanged(text);
            text = "";
        }

        Keys.onReturnPressed: {
            tviController.onReturnPressed();
        }

        Keys.onPressed: {
            if(event.key === Qt.Key_Backspace) {
               tviController.onBackspacePressed();
            }
        }
    }

    TviController{
        id: tviController
        anchors.fill: parent
        objectName: "tviController"

        onFileLoadDoneSg: {
            headerToolBarMenu.setHeaderFileInfoPanel("  " + filePage.displayFileName);
            pageStack.push(renderPage);
            filePage.loading = false;
            headerToolBarMenu.topToolLabel.text = "Navigation";
            headerToolBarMenu.setProjectionButton(isPerspective);
            footerToolBarMenu.disableFileBar( true );
            footerToolBarMenu.setButtonActive( footerToolBarMenu.naviBtn );
            styleMenu.setRenderModeType(renderMode);
            navMenu.visible = true;
            unblockRenderSg();
            appearanceSettings.enableStatistic();
        }

        onShowMessage: {
            messageDialogId.title = titleStr;
            messageDialogId.text = msgStr;
            messageDialogId.open();
        }

        onResetSg: {
            filePage.loading = false;
        }

        onShowImportParamsDialog: {
            filePage.showImportParamsDlg(ext);
        }

        onShowTotalTime: {
            headerToolBarMenu.setTotalTime( " " + totalTime / 1000 + " s  " );
        }

        onShowSaveMarkupDlg: {
            markupSaveDlg.visible = true;
        }

        onShowLoadMarkupDlg: {
            markupLoadDlg.setModel(list);
            markupLoadDlg.visible = true;
        }

        onDisplayVirtualKeyboard: {
            txtInput.forceActiveFocus();
        }

        onHideVirtualKeyboard: {
            txtInput.focus = false;
        }

        onDraggerFinished: {
            if(markupMenu.visible)
                markupMenu.resetButtonsBorders();
        }
    }

    PinchArea {
        id: pinchAreaId
        anchors.fill: parent
        objectName: "pinchArea"
        pinch.minimumRotation: 0
        pinch.maximumRotation: 360

        signal onZoomSg(double delta, int x, int y);
        signal onTouchStartSg(int x, int y);
        signal onTouchUpdatedSg(int x, int y);
        signal onTouchReleasedSg(int x, int y);

        onPinchUpdated: {
            if(pinch.pointCount == 2){
                onZoomSg(pinch.scale - pinch.previousScale, pinch.center.x, pinch.center.y);
            }
        }

        MultiPointTouchArea {
            anchors.fill: parent
            touchPoints: [ TouchPoint { id: touchPt } ]

            onPressed: {
                pinchAreaId.onTouchStartSg( touchPt.x, touchPt.y );
            }

            onUpdated: {
                pinchAreaId.onTouchUpdatedSg( touchPt.x, touchPt.y );
            }

            onReleased: {
                pinchAreaId.onTouchReleasedSg( touchPt.x, touchPt.y );
            }

        }

    }

    NavigationMenu {
        id: navMenu
        renderPage: renderPage
    }

    ViewMenu{
        id: viewMenu
        renderPage: renderPage
    }

    RegenMenu {
        id: regenMenu
        renderPage: renderPage
    }

    StyleMenu {
        id: styleMenu
        renderPage: renderPage
    }

    MarkupMenu {
        id: markupMenu
        renderPage: renderPage
        headerToolBarMenu: headerMenu
    }

    AppearanceSettingsDialog {
        id: appearanceSettings
        anchors.centerIn: parent
        visible: false

        onShowStatBtnPressed: {
            modelStatisticDlg.visible = true;
        }
    }

    ModelStatisticDialog {
        id: modelStatisticDlg
        anchors.centerIn: parent
        visible: false
    }

    MarkupSaveDialog {
        id: markupSaveDlg
        visible: false
    }

    MarkupLoadDialog {
        id: markupLoadDlg
        visible: false
    }

    SaveDialog {
        id: saveDialog
    }
}


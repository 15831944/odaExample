import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    id: appearanceDlg
    title: "General settings"
    standardButtons: Dialog.Ok | Dialog.Cancel
    anchors.centerIn: parent
    modal: true

    signal showStatBtnPressed();

    onAccepted: {
        tviController.applyAppearanceParams();
    }

    function enableStatistic() {
        showStatBtnId.visible = true;
    }

    ColumnLayout{
        anchors.fill: parent

        CheckBox{
            id: wcsId
            text: "Enable WCS"
            checked: tviController.getAppearanceParams().wcsEnabled

            onCheckedChanged: {
                tviController.getAppearanceParams().wcsEnabled = checked;
            }
        }

        CheckBox{
            id: fpsId
            text: "Enable FPS"
            checked: tviController.getAppearanceParams().fpsEnabled

            onCheckedChanged: {
                tviController.getAppearanceParams().fpsEnabled = checked;
            }
        }

        CheckBox{
            id: animationId
            text: "Enable animation"
            checked: tviController.getAppearanceParams().animationEnabled

            onCheckedChanged: {
                tviController.getAppearanceParams().animationEnabled = checked;
            }
        }

        CheckBox{
            id: partialOpen
            text: "Partial open"
            visible: !showStatBtnId.visible
            checked: tviController.getAppearanceParams().partialOpen

            onCheckedChanged: {
                tviController.getAppearanceParams().partialOpen = checked;
            }
        }

        CheckBox{
            id: useLimitManager
            text: "Use limit manager"
            enabled: partialOpen.checked
            visible: !showStatBtnId.visible
            checked: tviController.getAppearanceParams().useLimitManager

            onCheckedChanged: {
                tviController.getAppearanceParams().useLimitManager = checked;
            }
        }

        CheckBox {
            font.bold: false
            id: useSceneGraphId
            text: "Use scene graph"
            checked: tviController.getAppearanceParams().useSceneGraph
            visible: !showStatBtnId.visible

            onCheckedChanged:  {
                tviController.getAppearanceParams().useSceneGraph = checked;
            }
        }

        Button {
            id: showStatBtnId
            visible: false
            Layout.alignment: Qt.AlignHCenter
            text: "Show statistic"

            onClicked: {
                appearanceDlg.showStatBtnPressed();
            }
        }

        Rectangle{
            Layout.fillWidth: true
            height: 1
            color: "gray"
        }

    }

}


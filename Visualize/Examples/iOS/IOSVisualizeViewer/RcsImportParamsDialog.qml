import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    title: "Rcs import parameters"
    standardButtons: Dialog.Reset | Dialog.Ok
    anchors.centerIn: parent
    modal: true

    onReset: {
        importController.getRcsImportParams().resetParams();
        ignorePointSizeId.checked = importController.getRcsImportParams().ignorePointSize
        colorBtnBackground.color = importController.getRcsImportParams().baseColor;
    }

    onVisibleChanged: {
        if(visible){
            ignorePointSizeId.checked = importController.getRcsImportParams().ignorePointSize
            colorBtnBackground.color = importController.getRcsImportParams().baseColor;
        }
    }

    ColumnLayout{
        anchors.fill: parent

        CheckBox{
            id: ignorePointSizeId
            text: "Ignore point size"
            checked: importController.getRcsImportParams().ignorePointSize

            onCheckedChanged: {
                importController.getRcsImportParams().ignorePointSize = checked;
            }
        }

        RowLayout{

            Label{
                text: "Default color:"
            }

            Button{
                Layout.fillWidth: true
                Layout.fillHeight: true
                background: Rectangle{
                    id: colorBtnBackground
                    anchors.fill: parent
                    color: importController.getRcsImportParams().baseColor
                }

                onClicked: {
                    colorDlg.open();
                }
            }
        }

        Rectangle{
            Layout.fillWidth: true
            height: 1
            color: "gray"
        }

    }

    ColorChooseDialog{
        id: colorDlg
        onAccepted: {
            colorBtnBackground.color = colorDlg.color;
            importController.getRcsImportParams().baseColor = colorDlg.color;
        }
    }

}

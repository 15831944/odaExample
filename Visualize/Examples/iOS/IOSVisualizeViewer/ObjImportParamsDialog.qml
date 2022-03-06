import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    title: "Obj import parameters"
    standardButtons: Dialog.Reset | Dialog.Ok
    anchors.centerIn: parent
    modal: true

    onReset: {
        importController.getObjImportParams().resetParams();
        calcNormalsId.checked = importController.getObjImportParams().calculateNormals;
        flipUVid.checked = importController.getObjImportParams().flipUVCoordSystem;
        colorBtnBackground.color = importController.getObjImportParams().baseColor;
    }

    onVisibleChanged: {
        calcNormalsId.checked = importController.getObjImportParams().calculateNormals;
        flipUVid.checked = importController.getObjImportParams().flipUVCoordSystem;
        colorBtnBackground.color = importController.getObjImportParams().baseColor;
    }

    ColumnLayout{
        anchors.fill: parent

        Label{
            text: "Normals:"
            font.bold: true
        }

        CheckBox{
            id: calcNormalsId
            text: "Calculate normals"
            checked: importController.getObjImportParams().calculateNormals

            onCheckedChanged: {
                importController.getObjImportParams().calculateNormals = checked;
            }
        }

        Rectangle{
            Layout.fillWidth: true
            height: 1
            color: "gray"
        }

        Label{
            text: "BRep:"
            font.bold: true
        }

        CheckBox{
            id: flipUVid
            text: "Flip UV coordinate system"
            checked: importController.getObjImportParams().flipUVCoordSystem

            onCheckedChanged: {
                importController.getObjImportParams().flipUVCoordSystem = checked;
            }
        }

        Rectangle{
            Layout.fillWidth: true
            height: 1
            color: "gray"
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
                    color: importController.getObjImportParams().baseColor
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
            importController.getObjImportParams().baseColor = colorDlg.color;
        }
    }

}

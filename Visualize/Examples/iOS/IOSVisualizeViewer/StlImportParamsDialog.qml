import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    title: "Stl import parameters"
    standardButtons: Dialog.Reset | Dialog.Ok
    anchors.centerIn: parent
    modal: true

    function setStlParams() {
        fixNormalsId.checked = importController.getStlImportParams().fixNormals;
        unifyDuplVerticesId.checked = importController.getStlImportParams().unifyDuplicatedVertices;
        calcNormalArVerticesId.checked = importController.getStlImportParams().calcNormalsAtVertices
        colorBtnBackground.color = importController.getStlImportParams().baseColor;
    }

    onReset: {
        importController.getStlImportParams().resetParams();
        setStlParams();
    }

    onVisibleChanged: {
        setStlParams();
    }

    ColumnLayout{
        anchors.fill: parent

        CheckBox{
            id: fixNormalsId
            text: "Fix normals"
            checked: importController.getStlImportParams().fixNormals

            onCheckedChanged: {
                importController.getStlImportParams().fixNormals = checked;
            }
        }

        CheckBox{
            id: unifyDuplVerticesId
            text: "Unify duplicated vertices"
            checked: importController.getStlImportParams().unifyDuplicatedVertices

            onCheckedChanged: {
                importController.getStlImportParams().unifyDuplicatedVertices = checked;
            }
        }

        CheckBox{
            id: calcNormalArVerticesId
            text: "Calc normals at vertices"
            checked: importController.getStlImportParams().calcNormalsAtVertices

            onCheckedChanged: {
                importController.getStlImportParams().calcNormalsAtVertices = checked;
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
                    color: importController.getStlImportParams().baseColor
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
            importController.getStlImportParams().baseColor = colorDlg.color;
        }
    }

}

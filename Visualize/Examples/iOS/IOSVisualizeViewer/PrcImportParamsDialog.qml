import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    title: "Prc import parameters"
    standardButtons: Dialog.Reset | Dialog.Ok
    anchors.centerIn: parent
    modal: true
    visible: true

    function setPrcParameters(){
        objectNamingId.checked = importController.getPrcImportParams().objectNaming;
        storeSourceId.checked = importController.getPrcImportParams().storeSource;
        clearEmptyObjectsId.checked = importController.getPrcImportParams().clearEmptyObjects;
        xMinId.text = "" + importController.getPrcImportParams().xMin;
        xMaxId.text = "" + importController.getPrcImportParams().xMax;
        yMinId.text = "" + importController.getPrcImportParams().yMin;
        yMaxId.text = "" + importController.getPrcImportParams().yMax;
    }

    onReset: {
        importController.getPrcImportParams().resetParams();
        setPrcParameters();
    }

    onVisibleChanged: {
        if(visible){
            setPrcParameters();
        }
    }

    ColumnLayout{
        anchors.fill: parent

        CheckBox{
            id: objectNamingId
            text: "Object naming"
            checked: importController.getPrcImportParams().objectNaming

            onCheckedChanged: {
                importController.getPrcImportParams().objectNaming = checked;
            }
        }

        CheckBox{
            id: storeSourceId
            text: "Store source"
            checked: importController.getPrcImportParams().storeSource

            onCheckedChanged: {
                importController.getPrcImportParams().storeSource = checked;
            }
        }

        CheckBox{
            id: clearEmptyObjectsId
            text: "Clear empty objects"
            checked: importController.getPrcImportParams().clearEmptyObjects

            onCheckedChanged: {
                importController.getPrcImportParams().clearEmptyObjects = checked;
            }
        }

        GroupBox {
            title: "DCRect"
            font.bold: true

            RowLayout {
                anchors.fill: parent

                ColumnLayout {

                    RowLayout{
                        Label {
                            text: "X min:"
                        }
                        TextInput {
                            id: xMinId
                            maximumLength: 4
                            smooth: true
                            validator : IntValidator { bottom: 0; top: 9999; }
                            text: "" + importController.getPrcImportParams().xMin
                            Layout.fillWidth: true
                        }
                    }

                    RowLayout{
                        Label {
                            text: "Y min:"
                        }
                        TextInput {
                            id: yMinId
                            maximumLength: 4
                            smooth: true
                            validator : IntValidator { bottom: 0; top: 9999; }
                            text: "" + importController.getPrcImportParams().yMin
                            Layout.fillWidth: true
                        }
                    }
                }

                ColumnLayout {
                    RowLayout{
                        Label {
                            text: "X max:"
                        }
                        TextInput {
                            id: xMaxId
                            maximumLength: 4
                            smooth: true
                            validator : IntValidator { bottom: 0; top: 9999; }
                            text: "" + importController.getPrcImportParams().xMax
                        }
                    }

                    RowLayout{
                        Label {
                            text: "Y max:"
                        }
                        TextInput {
                            id: yMaxId
                            maximumLength: 4
                            smooth: true
                            validator : IntValidator { bottom: 0; top: 9999; }
                            text: "" + importController.getPrcImportParams().yMax
                        }
                    }
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
            importController.getPrcImportParams().baseColor = colorDlg.color;
        }
    }

}

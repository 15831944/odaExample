import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    title: "Dgn import parameters"
    standardButtons: Dialog.Reset | Dialog.Ok
    anchors.centerIn: parent
    modal: true
    visible: true

    function setDgnParameters(){
        objectNamingId.checked = importController.getDgnImportParams().objectNaming;
        storeSourceId.checked = importController.getDgnImportParams().storeSource;
        clearEmptyObjectsId.checked = importController.getDgnImportParams().clearEmptyObjects;
        xMinId.text = "" + importController.getDgnImportParams().xMin;
        xMaxId.text = "" + importController.getDgnImportParams().xMax;
        yMinId.text = "" + importController.getDgnImportParams().yMin;
        yMaxId.text = "" + importController.getDgnImportParams().yMax;
    }

    onReset: {
        importController.getDgnImportParams().resetParams();
        setDgnParameters();
    }

    onVisibleChanged: {
        if(visible){
            setDgnParameters();
        }
    }

    ColumnLayout{
        anchors.fill: parent

        CheckBox{
            id: objectNamingId
            text: "Object naming"
            checked: importController.getDgnImportParams().objectNaming

            onCheckedChanged: {
                importController.getDgnImportParams().objectNaming = checked;
            }
        }

        CheckBox{
            id: storeSourceId
            text: "Store source"
            checked: importController.getDgnImportParams().storeSource

            onCheckedChanged: {
                importController.getDgnImportParams().storeSource = checked;
            }
        }

        CheckBox{
            id: clearEmptyObjectsId
            text: "Clear empty objects"
            checked: importController.getDgnImportParams().clearEmptyObjects

            onCheckedChanged: {
                importController.getDgnImportParams().clearEmptyObjects = checked;
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
                            text: "" + importController.getDgnImportParams().xMin
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
                            text: "" + importController.getDgnImportParams().yMin
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
                            text: "" + importController.getDgnImportParams().xMax
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
                            text: "" + importController.getDgnImportParams().yMax
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
            importController.getDgnImportParams().baseColor = colorDlg.color;
        }
    }

}

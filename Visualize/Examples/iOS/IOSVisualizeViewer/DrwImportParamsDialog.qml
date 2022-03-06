import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    title: "Dwg import parameters"
    standardButtons: Dialog.Reset | Dialog.Ok
    anchors.centerIn: parent
    modal: true
    visible: true
    height: parent.height * 0.7

    function setDrwParameters(){
        objectNamingId.checked = importController.getDrwImportParams().objectNaming;
        storeSourceId.checked = importController.getDrwImportParams().storeSource;
        clearEmptyObjectsId.checked = importController.getDrwImportParams().clearEmptyObjects;
        mtCheckBoxId.checked = importController.getDrwImportParams().enableMultithreading;
        maxThreadsId.value = importController.getDrwImportParams().maxThreads;
        useAdvTessId.checked = importController.getDrwImportParams().useAdvancedTess;
        facetResId.value = importController.getDrwImportParams().facetRes * 100;
        xMinId.text = "" + importController.getDrwImportParams().xMin;
        xMaxId.text = "" + importController.getDrwImportParams().xMax;
        yMinId.text = "" + importController.getDrwImportParams().yMin;
        yMaxId.text = "" + importController.getDrwImportParams().yMax;
        colorBtnBackground.color = importController.getDrwImportParams().baseColor;
        useLowMemoryId.checked = importController.getDrwImportParams().lowMemoryImport;
    }

    onReset: {
        importController.getDrwImportParams().resetParams();
        setDrwParameters();
    }

    onVisibleChanged: {
        if(visible){
            setDrwParameters();
        }
    }

    ScrollView {
        clip: true
        anchors.fill: parent
        ScrollBar.vertical.interactive: contentHeight > height
        ScrollBar.horizontal.interactive: false

        ColumnLayout{
            anchors.fill: parent

            CheckBox{
                id: objectNamingId
                text: "Object naming"
                checked: importController.getDrwImportParams().objectNaming

                onCheckedChanged: {
                    importController.getDrwImportParams().objectNaming = checked;
                }
            }

            CheckBox{
                id: storeSourceId
                text: "Store source"
                checked: importController.getDrwImportParams().storeSource

                onCheckedChanged: {
                    importController.getDrwImportParams().storeSource = checked;
                }
            }

            CheckBox{
                id: clearEmptyObjectsId
                text: "Clear empty objects"
                checked: importController.getDrwImportParams().clearEmptyObjects

                onCheckedChanged: {
                    importController.getDrwImportParams().clearEmptyObjects = checked;
                }
            }

            CheckBox {
                id: mtCheckBoxId
                text: "Enable multithreading"
                checked: importController.getDrwImportParams().enableMultithreading

                onCheckedChanged: {
                    importController.getDrwImportParams().enableMultithreading = checked;
                }
            }

            RowLayout {
                Label {
                    text: "Max. Threads:"
                    enabled: mtCheckBoxId.checked
                }

                SpinBox {
                    id: maxThreadsId
                    enabled: mtCheckBoxId.checked
                    from: 0
                    to: 99
                    stepSize: 1
                    value: importController.getDrwImportParams().maxThreads

                    onValueChanged: {
                        importController.getDrwImportParams().maxThreads = value;
                    }
                }
            }

            CheckBox {
                id: useAdvTessId
                text: "Use advanced tess"
                checked: importController.getDrwImportParams().useAdvancedTess

                onCheckedChanged: {
                    importController.getDrwImportParams().useAdvancedTess = checked;
                }
            }

            RowLayout {

                Label {
                    text: "Facet res:"
                    enabled: useAdvTessId.checked
                    Layout.fillWidth: true
                }

                SpinBox {
                    id: facetResId
                    enabled: useAdvTessId.checked
                    from: 0
                    value: importController.getDrwImportParams().facetRes * 100
                    to: 100 * 100
                    stepSize: 10

                    property int decimals: 2
                    property real realValue: value / 100

                    validator: DoubleValidator {
                        bottom: Math.min(facetResId.from, facetResId.to)
                        top:  Math.max(facetResId.from, facetResId.to)
                    }

                    textFromValue: function(value, locale) {
                        return Number(value / 100).toLocaleString(locale, 'f', facetResId.decimals)
                    }

                    valueFromText: function(text, locale) {
                        return Number.fromLocaleString(locale, text) * 100
                    }

                    onValueChanged: {
                        importController.getDrwImportParams().maxThreds = realValue;
                    }
                }
            }

            GroupBox {
                title: "DCRect"
                font.bold: true
                Layout.fillWidth: true

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
                                text: "" + importController.getDrwImportParams().xMin
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
                                text: "" + importController.getDrwImportParams().yMin
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
                                text: "" + importController.getDrwImportParams().xMax
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
                                text: "" + importController.getDrwImportParams().yMax
                            }
                        }
                    }

                }
            }

            GroupBox {
                title: "Partial import"
                font.bold: true
                Layout.fillWidth: true

                CheckBox {
                    font.bold: false
                    id: useLowMemoryId
                    text: "Low memory import"
                    checked: importController.getDrwImportParams().lowMemoryImport

                    onCheckedChanged:  {
                        importController.getDrwImportParams().lowMemoryImport = checked;
                    }
                }
            }

            RowLayout{

                Label{
                    text: "Background color:"
                }

                Button{
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    background: Rectangle{
                        id: colorBtnBackground
                        anchors.fill: parent
                        color: importController.getDrwImportParams().baseColor
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
    }


    ColorChooseDialog{
        id: colorDlg
        onAccepted: {
            colorBtnBackground.color = colorDlg.color;
            importController.getDrwImportParams().baseColor = colorDlg.color;
        }
    }

}

import QtQuick 2.6
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import Qt.labs.folderlistmodel 2.2

Page{
    property variant tviController
    property variant renderPage
    property variant headerToolBarMenu

    property alias searchFieldVisible: searchField.visible

    property alias appearanceSettingsVisible: appearanceSettings.visible

    property alias loading: busyInd.running

    property string displayFileName: "nofile"

    function showImportParamsDlg(extStr){
        if(extStr === "OBJ")
            objImportDialog.visible = true;
        else if(extStr === "DRW")
            drwImportDialog.visible = true;
        else if(extStr === "RCS")
            rcsImportDialog.visible = true;
        else if(extStr === "DGN")
            dgnImportDialog.visible = true;
        else if(extStr === "STL")
            stlImportDialog.visible = true;
        else if(extStr === "PRC")
            prcImportDialog.visible = true;
        else if(extStr === "VSF") {
            loading = true;
            // any parameters for vsf, in the method will be used base parameters
            tviController.onAcceptImportDlg(importController.getObjImportParams());
        }
    }

    TextField{
        id: searchField
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        placeholderText: "Search"
        visible: false

        onTextChanged: {
            folderModel.updateFilter();
        }

        onVisibleChanged: {
            if( visible) {
                fileList.anchors.top = searchField.bottom;
                forceActiveFocus();
            }
            else {
                fileList.anchors.top = parent.top;
                text = "";
            }
        }
    }


    ListView {
        id: fileList
        anchors.top:  parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        function getStrSize(bytes) {
            var sizes = ['Bytes', 'KB', 'MB', 'GB', 'TB'];
            if (bytes == 0)
                return '0 Byte';
            var i = parseInt(Math.floor(Math.log(bytes) / Math.log(1024)));
            return Math.round(bytes / Math.pow(1024, i), 2) + ' ' + sizes[i];
        }

        FolderListModel {
            id: folderModel
            showDirs: false
            folder: appDataPath

            property variant extFilters: ["*.obj", "*.stl", "*.vsf", "*.dwg", "*.dgn", "*.rcs", "*.prc"]
            property string extStr: ".obj.stl.vsf.dwg.dgn.rcs.prc"

            nameFilters: extFilters

            function updateFilter()
            {
                var text = searchField.text
                var filter = ""

                if( text.indexOf(".") !== -1 ){
                    if(text.length > 1 && extStr.indexOf(text) !== -1) {
                        filter += "*";
                        filter += text;
                        filter += "*";
                        nameFilters = [ filter ];
                    }
                    else {
                        nameFilters = extFilters;
                    }
                }
                else {
                    for(var i = 0; i<text.length; i++)
                        filter+= text[i];

                    var newFilters = nameFilters;
                    for(var i = 0; i < extFilters.length; i++){
                        newFilters[i] = filter + extFilters[i];

                        nameFilters = newFilters;
                    }
                }
            }
        }

        Component {
            id: fileDelegate

            Item {
                id: itemId
                width: fileList.width
                height: 50

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 5
                    anchors.rightMargin: 5

                    Text { id: fileNameTxtId; text: fileName; Layout.alignment: Qt.AlignLeft }
                    Text {
                        text: fileList.getStrSize( fileSize )
                        Layout.alignment: Qt.AlignRight
                    }
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        displayFileName = fileNameTxtId.text;
                        searchField.visible = false;
                        folderModel.nameFilters = folderModel.extFilters;
                        fileList.currentIndex = index;
                        tviController.filePath = dirDataPath + "/" + fileNameTxtId.text;
                    }
                }
            }
        }


        highlight: Rectangle {
            color: "#c2cddd"
            radius: 3
        }

        model: folderModel
        delegate: fileDelegate
    }

    ObjImportParamsDialog{
        id: objImportDialog
        visible: false

        onAccepted:{
            loading = true;
            importController.getObjImportParams().applyParams();
            tviController.onAcceptImportDlg(importController.getObjImportParams());
        }

        onRejected: tviController.onRejectImportDlg();
    }

    DrwImportParamsDialog {
        id: drwImportDialog
        visible: false

        onAccepted: {
            loading = true;
            importController.getDrwImportParams().applyParams();
            tviController.onAcceptImportDlg(importController.getDrwImportParams());
        }

        onRejected: tviController.onRejectImportDlg();
    }

    RcsImportParamsDialog{
        id: rcsImportDialog
        visible: false

        onAccepted: {
            loading = true;
            importController.getRcsImportParams().applyParams();
            tviController.onAcceptImportDlg(importController.getRcsImportParams());
        }

        onRejected: tviController.onRejectImportDlg();
    }

    DgnImportParamsDialog{
        id: dgnImportDialog
        visible: false

        onAccepted: {
            loading = true;
            importController.getDgnImportParams().applyParams();
            tviController.onAcceptImportDlg(importController.getDgnImportParams());
        }

        onRejected: tviController.onRejectImportDlg();
    }

    StlImportParamsDialog{
        id: stlImportDialog
        visible: false

        onAccepted: {
            loading = true;
            importController.getStlImportParams().applyParams();
            tviController.onAcceptImportDlg(importController.getStlImportParams());
        }

        onRejected: tviController.onRejectImportDlg();
    }

    PrcImportParamsDialog{
        id: prcImportDialog
        visible: false

        onAccepted: {
            loading = true;
            importController.getPrcImportParams().applyParams();
            tviController.onAcceptImportDlg(importController.getPrcImportParams());
        }

        onRejected: tviController.onRejectImportDlg();
    }

    AppearanceSettingsDialog {
        id: appearanceSettings
        anchors.centerIn: parent
        visible: false
    }

    BusyIndicator {
        id: busyInd
        anchors.centerIn: parent
        running: false

        onRunningChanged: {
            fileList.enabled = !running;
            headerToolBarMenu.enabled = !running;
        }
    }

}

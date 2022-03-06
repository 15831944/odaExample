import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    id: saveDlg
    title: "Save parameters"
    standardButtons: Dialog.Ok | Dialog.Cancel
    anchors.centerIn: parent
    modal: true

    function setSaveFilename(originalFilename) {
        filenameID.text = originalFilename.substring(0, originalFilename.lastIndexOf(".")) + ".vsf";
    }

    ColumnLayout {

        CheckBox {
            id: partialIndexingId
            text: "Partial indexing"
        }

        RowLayout {

            Label {
                text: "Filename:"
            }

            TextField {
                id: filenameID
                text: ""
                Layout.fillWidth: true
            }

        }

    }

    onAccepted: {
        if(filenameID.text.split('.').pop() !== "vsf")
            filenameID.text = filenameID.text + ".vsf";
        tviController.saveFile(partialIndexingId.checked, filenameID.text);
    }
}

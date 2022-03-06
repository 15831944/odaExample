import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    id: markupSaveDialog
    title: "Save markup"
    anchors.centerIn: parent
    modal: true
    width: parent.width * 0.7

    onAccepted: {
        tviController.saveMarkup(txtInput.text);
        txtInput.text = "";
    }

    onVisibleChanged: {
        txtInput.forceActiveFocus();
    }

    ColumnLayout {
        anchors.fill: parent
        RowLayout {

            Label {
                text: "Enter name:"
            }

            TextField {
                id: txtInput
                Layout.fillWidth: true
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignRight

            Button {
                text: "Ok"
                onClicked: markupSaveDialog.accept();
            }
            Button {
                text: "Cancel"
                onClicked: markupSaveDialog.reject();
            }
        }

    }

}


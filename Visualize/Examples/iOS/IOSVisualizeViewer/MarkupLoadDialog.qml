import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Dialog {
    id: markupLoadDialog
    title: "Load markup"
    anchors.centerIn: parent
    modal: true
    width: parent.width * 0.7
    height: parent.height * 0.5

    function setModel(listModel) {
        listView.model = listModel;
        listView.delegate = markupDelegate;
        if(listView.currentIndex < 0)
            listView.currentIndex = 0;
    }

    RowLayout {
        anchors.fill: parent

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            border.width: 1
            border.color: "#e6c5cfe3"
            radius: 5
            color: "#fafafb"

            ListView {
                id: listView
                anchors.fill: parent
                spacing: 1
                highlight: Rectangle {
                    color: "#c9d2e2"
                    radius: 5
                }
                interactive: contentHeight > listView.height ? true : false
                anchors.margins: 2
                currentIndex: -1

                Component {
                    id: markupDelegate

                    Item {
                        id: itemId
                        width: listView.width
                        height: 45

                        property string itemText: txtId.text

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 5
                            anchors.rightMargin: 5

                            Text {
                                id: txtId
                                text: modelData
                                Layout.alignment: Qt.AlignLeft
                            }
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked:{
                                listView.currentIndex = index;
                            }
                        }
                    }
                }
            }

        }

        ColumnLayout {
            Button {
                text: "Load"
                onClicked:  {
                    tviController.loadMarkup( listView.currentItem.itemText );
                    markupLoadDlg.accept();
                }
            }
            Button {
                text: "Delete"

                onClicked:  {
                    tviController.deleteMarkup( listView.currentItem.itemText );
                }
            }

            Item {
                Layout.fillHeight: true
            }

            Button {
                text: "Close"
                onClicked: markupLoadDialog.reject();
            }
        }

    }

}


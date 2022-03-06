import QtQuick 2.6
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle{
    id: regenMenu
    color: "#ccf9f8f8"
    border.color: "transparent"
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.rightMargin: 20
    height: 55
    width: parent.width
    visible: false

    property variant renderPage

    property int iconSize: 45
    property int rightMarginProp: width * 0.07

    ColumnLayout{
        anchors.fill: parent

        RowLayout{
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            Button{
                icon.source: "qrc:/icons/regenAll.png"
                icon.width: iconSize
                icon.height: iconSize
                icon.color: "transparent"
                Layout.rightMargin: regenMenu.rightMarginProp
                background: Rectangle{
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("regenAll");
                }
            }

            Button{
                icon.source: "qrc:/icons/regenVisible.png"
                icon.width: iconSize
                icon.height: iconSize
                icon.color: "transparent"
                Layout.rightMargin: regenMenu.rightMarginProp
                background: Rectangle{
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("regenVisible");
                }
            }

            Button{
                icon.source: "qrc:/icons/regenVp.png"
                icon.width: iconSize
                icon.height: iconSize
                icon.color: "transparent"
                background: Rectangle{
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("regenVp");
                }
            }

        }
    }
}

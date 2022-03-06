import QtQuick 2.6
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Rectangle{
    id: viewMenu
    color: "#ccf9f8f8"
    border.color: "transparent"
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.rightMargin: 20
    height: 100
    width: parent.width
    visible: false

    property variant renderPage

    property int iconSize: 35
    property int isoIconSize: 40
    property int rightMarginProp: width * 0.02

    ColumnLayout {
        anchors.fill: parent
        RowLayout{
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            Button{
                icon.source: "qrc:/icons/top_view.png"
                icon.width: iconSize
                icon.height: iconSize
                icon.color: "transparent"
                Layout.rightMargin: viewMenu.rightMarginProp
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewTop");
                }
            }


            Button{
                icon.source: "qrc:/icons/bottom_view.png"
                icon.width: iconSize
                icon.height: iconSize
                icon.color: "transparent"
                Layout.rightMargin: viewMenu.rightMarginProp
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewBottom");
                }
            }


            Button{
                icon.source: "qrc:/icons/left_view.png"
                icon.width: iconSize
                icon.height: iconSize
                icon.color: "transparent"
                Layout.rightMargin: viewMenu.rightMarginProp
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewLeft");
                }
            }


            Button{
                icon.source: "qrc:/icons/right_view.png"
                icon.width: iconSize
                icon.height: iconSize
                icon.color: "transparent"
                Layout.rightMargin: viewMenu.rightMarginProp
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewRight");
                }
            }


            Button{
                icon.source: "qrc:/icons/front_view.png"
                icon.width: iconSize
                icon.height: iconSize
                icon.color: "transparent"
                Layout.rightMargin: viewMenu.rightMarginProp
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewFront");
                }
            }


            Button{
                icon.source: "qrc:/icons/back_view.png"
                icon.width: iconSize
                icon.height: iconSize
                icon.color: "transparent"
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewBack");
                }
            }
        }

        RowLayout{
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            Button{
                icon.source: "qrc:/icons/SW_view.png"
                icon.width: isoIconSize
                icon.height: isoIconSize
                icon.color: "transparent"
                Layout.rightMargin: viewMenu.rightMarginProp
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewSW");
                }
            }

            Button{
                icon.source: "qrc:/icons/SE_view.png"
                icon.width: isoIconSize
                icon.height: isoIconSize
                icon.color: "transparent"
                Layout.rightMargin: viewMenu.rightMarginProp
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewSE");
                }
            }

            Button{
                icon.source: "qrc:/icons/NW_view.png"
                icon.width: isoIconSize
                icon.height: isoIconSize
                icon.color: "transparent"
                Layout.rightMargin: viewMenu.rightMarginProp
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewNW");
                }
            }

            Button{
                icon.source: "qrc:/icons/NE_view.png"
                icon.width: isoIconSize
                icon.height: isoIconSize
                icon.color: "transparent"
                background: Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                }

                onClicked: {
                    renderPage.panelButtonPressed("viewNE");
                }
            }
        }

    }

}


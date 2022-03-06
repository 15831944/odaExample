import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.2

ApplicationWindow {
    id: mainWindowId
    width: 320
    height: 480
    color: "black"
    visible: false

    header: HeaderToolBarMenu{
        id: headerMenu
        renderPage: renderPage
        filePage: filePage
        pageStack: pageStack
    }

    footer: FooterToolBarMenu{
        id: footerMenu
        navMenu: renderPage.navMenu
        viewMenu: renderPage.viewMenu
        regenMenu: renderPage.regenMenu
        styleMenu: renderPage.styleMenu
        markupMenu: renderPage.markupMenu
        explorerBtn: headerMenu.explorerBtn
        projectionBtn: headerMenu.projectionBtn
        topToolLabel: headerMenu.topToolLabel
        tviController: renderPage.tviController
        pageStack: pageStack
        headerToolBarMenu: headerMenu
    }

    StackView {
        id: pageStack
        anchors.fill: parent
        objectName: "pageStack"

        initialItem:  FilePage {
            id: filePage
            tviController: renderPage.tviController
            renderPage: renderPage
            headerToolBarMenu: headerMenu
        }

        RenderPage {
            id: renderPage
            headerToolBarMenu: headerMenu
            footerToolBarMenu: footerMenu
            pageStack: pageStack
            filePage: filePage
        }

    }

}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtMultimedia 5.0
import "mainmenu" as Mainmenu

Item
{
    signal clickedNewGame
    signal clickedChangeVisibility
    signal clickedExit

    id: root

    Mainmenu.MenuBackground { id: bgTexture; anchors.fill: parent }

    Rectangle
    {
        id: bgItem
        anchors.fill: parent
        color: "transparent"

        GridLayout
        {
            id: layout
            anchors.fill: parent
            anchors.leftMargin: 40
            anchors.bottomMargin: 40
            rowSpacing: 10
            rows: 4
            columns: 1

            Item
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 0
                Layout.row: 0
                Rectangle { anchors.fill: parent; color: "transparent" }
            }

            Mainmenu.MenuButton
            {
                id: bnNewGame
                text: "New game"
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                Layout.column: 0
                Layout.row: 1
                onClicked: clickedNewGame()
            }
            Mainmenu.MenuButton
            {
                id: bnVisibility
                text: appVisibility == Window.FullScreen ? "Windowed" : "FullScreen"
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                Layout.column: 0
                Layout.row: 2
                onClicked: clickedChangeVisibility()
            }
            Mainmenu.MenuButton
            {
                id: bnExit
                text: "Exit"
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                Layout.column: 0
                Layout.row: 3
                onClicked: clickedExit()
            }
        }
    }

    onClickedNewGame: bgTexture.reload()
    onClickedChangeVisibility: bgTexture.reload()
    onClickedExit: bgTexture.reload()
}

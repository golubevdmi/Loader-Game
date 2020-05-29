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
        property int margin: 40
        property int size: (Math.min(root.width, root.height) - margin * 4) / 2

        id: bgItem
        width: 300 + margin * 2
        height: 40 * 3 + margin * 2 + layout.rowSpacing * 2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        color: "transparent"

        GridLayout
        {
            id: layout
            anchors.centerIn: parent
            anchors.margins: bgItem.margin
            rowSpacing: 10
            rows: 4
            columns: 1

            Mainmenu.MenuButton
            {
                id: bnNewGame
                text: "New game"
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                Layout.column: 0
                Layout.row: 0
                onClicked: clickedNewGame()
            }
            Mainmenu.MenuButton
            {
                id: bnVisibility
                text:
                {
                    if (appVisibility === Window.FullScreen || appVisibility === Window.Maximized)
                        return "Windowed";
                    else
                        return "FullScreen";
                }
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                Layout.column: 0
                Layout.row: 1
                onClicked: clickedChangeVisibility()
            }
            Mainmenu.MenuButton
            {
                id: bnExit
                text: "Exit"
                Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                Layout.column: 0
                Layout.row: 2
                onClicked: clickedExit()
            }
            Item
            {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 0
                Layout.row: 3
                Rectangle { anchors.fill: parent; color: "transparent" }
            }
        }
    }

    onClickedNewGame: bgTexture.reload()
    onClickedChangeVisibility: bgTexture.reload()
    onClickedExit: bgTexture.reload()
}

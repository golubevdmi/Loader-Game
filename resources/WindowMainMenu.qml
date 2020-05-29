import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import "mainmenu" as Mainmenu
import "items" as SokobanItems

Item
{
    signal clickedNewGame
    signal clickedChangeVisibility
    signal clickedExit

    id: root

    Mainmenu.MenuBackground { id: bgTexture; anchors.fill: parent }

    Rectangle
    {
        id: menuNavigation
        width: 300 + 100
        height: 40 * 7
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        color: "transparent"

        ColumnLayout
        {
            id: layout
            anchors.centerIn: parent

            Mainmenu.MenuButton
            {
                text: "New game"
                onClicked: clickedNewGame()
            }
            Mainmenu.MenuButton
            {
                text:
                {
                    switch(appVisibility)
                    {
                    case Window.Maximized:
                    case Window.FullScreen:
                        return "Windowed";
                    case Window.Windowed:
                        return "FullScreen";
                    default:
                        return "undefined";
                    }
                }
                onClicked: clickedChangeVisibility()
            }
            Mainmenu.MenuButton
            {
                text: "Exit"
                onClicked: clickedExit()
            }
            SokobanItems.Spacer { Layout.fillHeight: true }
        }
    }
}

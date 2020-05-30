import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import "mainmenu" as Mainmenu
import "items" as SokobanItems

Item
{
    signal clickedContinue
    signal clickedNewGame
    signal clickedLevels
    signal clickedStatistics
    signal clickedChangeVisibility
    signal clickedExit
    signal clickedListItem(int index)

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

        ListView
        {
            id: view

            anchors.margins: 10
            anchors.fill: parent
            spacing: 10
            model: ListModel
            {
                id: dataModel
                ListElement { text: "Continue"; }
                ListElement { text: "New game"; }
                ListElement { text: "Levels"; }
                ListElement { text: "Statistics"; }
                ListElement { text: "Visibility"; }
                ListElement { text: "Exit"; }
            }
            clip: true

            highlight: Rectangle { color: "darkgrey" }
            highlightFollowsCurrentItem: true

            delegate: Item {
                id: listDelegate

                property var view: ListView.view
                property var isCurrent: ListView.isCurrentItem

                width: bn.implicitWidth
                height: bn.implicitHeight

                Mainmenu.MenuButton
                {
                    id: bn
                    animationActive: isCurrent
                    text:
                    {
                        if (model.index === 4)
                            model.text = getBnVisibilityName(appVisibility);
                        return "%1".arg(model.text);
                    }
                    onClicked:
                    {
                        view.currentIndex = model.index;
                        clickedListItem(model.index);
                    }
                }
            }
            Shortcut
            {
                sequence: "Up"
                onActivated: view.currentIndex ? view.currentIndex-- : print("main menu: index invalid");
            }
            Shortcut
            {
                sequence: "Down"
                onActivated: view.currentIndex < view.count - 1 ? view.currentIndex++ : print("main menu: index invalid");
            }
            Shortcut
            {
                sequence: "Enter"
                onActivated: { clickedListItem(view.currentIndex);  }
            }
        }
    }

    onClickedListItem:
    {
        switch (index)
        {
        case 0:
            clickedContinue();
            break;
        case 1:
            clickedNewGame();
            break;
        case 2:
            clickedLevels();
            break;
        case 3:
            clickedStatistics();
            break;
        case 4:
            clickedChangeVisibility();
            break;
        case 5:
            clickedExit();
            break;
        }
    }

    function getBnVisibilityName(appVisibility)
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
}

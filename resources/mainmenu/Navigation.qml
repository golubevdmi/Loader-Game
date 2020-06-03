import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.12
import "./" as Mainmenu

Item
{
    signal clickedListItem(int index)
    signal clickedContinue
    signal clickedNewGame
    signal clickedLevels
    signal clickedStatistics
    signal clickedChangeVisibility
    signal clickedExit

    id: root
    implicitWidth: 300
    implicitHeight: 250

    ListView
    {
        id: view
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

        delegate: Mainmenu.MenuButton
        {
            property var view: ListView.view
            property var isCurrent: ListView.isCurrentItem

            id: bn
            implicitWidth: root.implicitWidth
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
            Connections
            {
                target: view
                onCurrentIndexChanged: { if (index === view.currentIndex) bn.playSound(); }
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
            onActivated: view.currentItem.clicked()
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

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
    signal clickedLevel(int index)
    signal clickedChangeVisibility
    signal clickedExit

    id: root
    Mainmenu.MenuBackground { id: bgTexture; anchors.fill: parent }

    Item
    {
        id: menuStates
        states: [
            State { name: "navigation";
                PropertyChanges { target: loaderNavigation; active: true; }
                PropertyChanges { target: loaderLvls;       active: false; }
                PropertyChanges { target: loaderStat;       active: false; }
            },
            State { name: "levels";
                PropertyChanges { target: loaderNavigation; active: false; }
                PropertyChanges { target: loaderLvls;       active: true; }
            },
            State { name: "statistics";
                PropertyChanges { target: loaderNavigation; active: false; }
                PropertyChanges { target: loaderStat;       active: true; }
            }
        ]
    }

    Rectangle
    {
        id: menuRect
        anchors.fill: parent
        anchors.margins: 50
        color: "transparent"

        Connections
        {
            target: loaderNavigation.item
            onClickedNewGame: clickedNewGame()
            onClickedLevels:
            {
                print("Main menu -> Levels");
                menuStates.state = "levels";
            }
            onClickedStatistics:
            {
                print("Main menu -> Statistics");
                menuStates.state = "statistics";
            }

            onClickedChangeVisibility: clickedChangeVisibility()
            onClickedExit: clickedExit()
        }

        Connections
        {
            target: loaderLvls.item
            onClickedListItem:
            {
                print("Levels -> select level " + index);
                clickedLevel(index);
                menuStates.state = "navigation";
            }
        }

        Loader
        {
            id: loaderNavigation
            active: false
            sourceComponent: Component { Mainmenu.Navigation {} }
            anchors.horizontalCenter: menuRect.horizontalCenter
            anchors.bottom: menuRect.bottom
        }
        Loader
        {
            id: loaderLvls
            active: false
            sourceComponent: Component { Mainmenu.MenuLvlsList {} }
            anchors.horizontalCenter: menuRect.horizontalCenter
            anchors.bottom: menuRect.bottom
        }
        Loader
        {
            id: loaderStat
            active: false
            sourceComponent: Component { Mainmenu.MenuStats {} }
            anchors.fill: menuRect
        }
    }

    Shortcut { sequence: "Escape"; onActivated: updateState(menuStates) }
    Shortcut { sequence: "Backspace"; onActivated: updateState(menuStates) }

    function updateState(menuStates)
    {
        switch (menuStates.state)
        {
        case "navigation":
            clickedExit();
            break;
        default:
            menuStates.state = "navigation";
        }
    }

    Component.onCompleted: menuStates.state = "navigation"
}

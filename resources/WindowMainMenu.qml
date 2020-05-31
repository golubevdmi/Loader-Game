import QtQuick 2.12
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
                PropertyChanges { target: loaderBackBn;     active: false; }
            },
            State { name: "levels";
                PropertyChanges { target: loaderNavigation; active: false; }
                PropertyChanges { target: loaderLvls;       active: true; }
                PropertyChanges { target: loaderBackBn;     active: true; }
            },
            State { name: "statistics";
                PropertyChanges { target: loaderNavigation; active: false; }
                PropertyChanges { target: loaderStat;       active: true; }
                PropertyChanges { target: loaderBackBn;     active: true; }
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
            onClickedContinue: clickedContinue()
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

    Loader
    {
        id: loaderBackBn
        active: false
        sourceComponent: Component {
            Mainmenu.MenuButton { text: "back"; bgColor: "black"; onClicked: menuStates.state = "navigation" }
        }
        anchors.leftMargin: 50
        anchors.bottomMargin: 15
        anchors.left: root.left
        anchors.bottom: root.bottom
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

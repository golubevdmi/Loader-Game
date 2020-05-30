import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

ApplicationWindow
{
    id: root
    visible: true
    width: 1280
    //height: 960
    height: 600
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Sakoban")

    Item
    {
        id: gameStates
        states: [
            State { name: "mainMenu";
                PropertyChanges { target: loaderGameplay; active: false; }
                PropertyChanges { target: loaderMainMenu; active: true; }
            },
            State { name: "gameplay";
                PropertyChanges { target: loaderGameplay; active: true; }
                PropertyChanges { target: loaderMainMenu; active: false; }
            },
            State { name: "levels";
                PropertyChanges { target: loaderLvls;     active: true; }
                PropertyChanges { target: loaderMainMenu; active: false; }
            },
            State { name: "stat";
                PropertyChanges { target: loaderStat;     active: true; }
                PropertyChanges { target: loaderMainMenu; active: false; }
            },
            State { name: "undefined";
                PropertyChanges { target: loaderGameplay; active: false; }
                PropertyChanges { target: loaderMainMenu; active: false; }
            }
        ]
    }

    Component
    {
        id: gameplay
        WindowGameplay
        {
            Connections
            {
                target: root
                onVisibilityChanged: loaderGameplay.item.updateState();
                onWidthChanged:      loaderGameplay.item.updateState();
                onHeightChanged:     loaderGameplay.item.updateState();
            }
            Component.onCompleted: newGame();
        }
    }

    Connections
    {
        target: loaderMainMenu.item
        onClickedNewGame:
        {
            print("Main menu -> New game");
            loaderGameplay.startLvl = 0;
            gameStates.state = "gameplay";
        }
        onClickedLevels:
        {
            print("Main menu -> Levels");
            gameStates.state = "levels";
        }
        onClickedStatistics:
        {
            print("Main menu -> Statistics");
            gameStates.state = "stat";
        }

        onClickedChangeVisibility:
        {
            if (root.visibility === Window.Windowed)
                root.visibility = Window.FullScreen
            else if (root.visibility === Window.FullScreen || root.visibility === Window.Maximized)
                root.visibility = Window.Windowed
        }
        onClickedExit:
        {
            print("Main menu -> Exit");
            gameStates.state = "undefined";
            Qt.quit();
        }
    }

    Connections
    {
        target: loaderLvls.item
        onClickedListItem:
        {
            print("Levels -> select level " + index);
            gameStates.state = "mainMenu";
            loaderGameplay.startLvl = index;
            gameStates.state = "gameplay";
        }
    }

    Connections
    {
        target: loaderStat.item
        onClickedBack:
        {
            print("Statistics -> back ");
            gameStates.state = "mainMenu";
        }
    }

    Loader
    {
        property var appVisibility: root.visibility

        id: loaderMainMenu
        active: false
        sourceComponent: Component { WindowMainMenu { } }
        focus: true
        anchors.fill: parent
    }
    Loader
    {
        property int startLvl: 0

        id: loaderGameplay
        active: false
        sourceComponent: gameplay
        anchors.fill: parent
    }
    Loader
    {
        id: loaderLvls
        active: false
        sourceComponent: Component { WindowLvlsList {} }
        anchors.fill: parent
    }
    Loader
    {
        id: loaderStat
        active: false
        sourceComponent: Component { WindowStats {} }
        anchors.fill: parent
    }

    Shortcut { sequence: "Escape"; onActivated: updateState(gameStates) }
    Shortcut { sequence: "Backspace"; onActivated: updateState(gameStates) }

    function updateState(gameStates)
    {
        switch (gameStates.state)
        {
        case "mainMenu":
            gameStates.state = "undefined";
            Qt.quit();
            break;
        default:
            gameStates.state = "mainMenu";
        }
    }

    Component.onCompleted: { gameStates.state = "mainMenu"; }
}

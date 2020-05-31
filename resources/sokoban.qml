import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

ApplicationWindow
{
    id: root
    visible: true
    width: 1280
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
        onClickedContinue:
        {
            print("Main menu -> Continue");
            gameStates.state = "gameplay";
            loaderGameplay.item.continueGame();
        }
        onClickedNewGame:
        {
            print("Main menu -> New game");
            loaderGameplay.startLvl = 0;
            gameStates.state = "gameplay";
        }
        onClickedLevel:
        {
            print("Main menu -> Levels");
            loaderGameplay.startLvl = index;
            gameStates.state = "gameplay";
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
            Qt.quit();
        }
    }

    Connections
    {
        target: loaderGameplay.item
        onExit: gameStates.state = "mainMenu"
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

    Component.onCompleted: { gameStates.state = "mainMenu"; }
}

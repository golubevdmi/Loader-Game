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
        }
    }

    Connections
    {
        target: loaderMainMenu.item
        onClickedNewGame:
        {
            print("Main menu -> New game");
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
            gameStates.state = "undefined";
            Qt.quit();
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
        id: loaderGameplay
        active: false
        sourceComponent: gameplay
        anchors.fill: parent
    }

    Shortcut
    {
        sequence: "Escape"
        onActivated:
        {
            switch (gameStates.state)
            {
            case "mainMenu":
                gameStates.state = "undefined";
                Qt.quit();
                break;
            case "gameplay":
                gameStates.state = "mainMenu";
                break;
            }
        }
    }

    Component.onCompleted: { gameStates.state = "mainMenu"; }
}

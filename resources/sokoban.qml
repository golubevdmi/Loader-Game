import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow
{
    id: root
    visible: true
    //visibility: "FullScreen"
    width: 1280
    //height: 960
    height: 600
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Sakoban")

    Component { id: mainMenu; WindowMainMenu { } }
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
        id: conncectMainMenu
        target: loaderMainMenu.item
        onClickedNewGame:
        {
            print("Main menu -> New game");
            loaderMainMenu.active = false;
            loaderGameplay.active = true;
        }
        onClickedExit:
        {
            print("Main menu -> Exit");
            Qt.quit();
        }
    }

    Loader
    {
        id: loaderMainMenu
        active: false
        sourceComponent: mainMenu
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
            if (loaderGameplay.active)
            {
                loaderGameplay.active = false;
                loaderMainMenu.active = true;
            }
            else
            {
                Qt.quit();
            }
        }
    }

    Component.onCompleted: { loaderGameplay.active = true; }
}

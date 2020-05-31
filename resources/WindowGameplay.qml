import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtMultimedia 5.0
import SokobanModel 1.0
import "gameplay" as Gameplay
import "items" as SokobanItem

Item
{
    signal continueGame
    signal newGame
    signal updateState
    signal exit

    id: root

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 0

        Gameplay.ToolBar
        {
            Layout.fillWidth: true
            modelObj: sokobanModel
        }

        TableView
        {
            id: view
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: SokobanModel { id: sokobanModel }
            delegate: Gameplay.ModelDelegate
            {
                id: modelDelegate
                implicitWidth: view.width / view.columns
                implicitHeight: view.height / view.rows

                Connections
                {
                    target: root
                    onUpdateState: modelDelegate.reload()
                }

                Connections
                {
                    target: sokobanModel
                    onDataChanged: modelDelegate.reload()

                    onMoved_up:    playerState = "up"
                    onMoved_down:  playerState = "down"
                    onMoved_left:  playerState = "left"
                    onMoved_right: playerState = "right"
                }
            }
        }
    }

    onContinueGame: sokobanModel.continue_game();
    onNewGame: sokobanModel.loadLevel(startLvl);
    onUpdateState: view.forceLayout();
    onExit: sokobanModel.quit_game();

    Connections
    {
        target: sokobanModel
        onGame_win: loaderLvlComplete.active = true
        onDataChanged: loaderLvlComplete.active = false
        onGrid_changed: loaderLvlComplete.active = false
    }

    Shortcut
    {
        sequence: "Up"
        onActivated: sokobanModel.moveUp();
    }
    Shortcut
    {
        sequence: "Down"
        onActivated: sokobanModel.moveDown();
    }
    Shortcut
    {
        sequence: "Left"
        onActivated: sokobanModel.moveLeft();
    }
    Shortcut
    {
        sequence: "Right"
        onActivated: sokobanModel.moveRight();
    }
    Shortcut
    {
        sequence: StandardKey.Undo
        onActivated: sokobanModel.undo();
    }
    Shortcut
    {
        sequence: StandardKey.Redo
        onActivated: sokobanModel.redo();
    }

    Loader
    {
        id: loaderLvlComplete
        active: false
        sourceComponent: Gameplay.LvlComplete { }
        anchors.centerIn: root
    }


    Shortcut { sequence: "Escape"; onActivated: exit() }
    Shortcut { sequence: "Backspace"; onActivated: exit() }
}

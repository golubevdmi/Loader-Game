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
    signal updateState

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
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: SokobanModel { id: sokobanModel }
            delegate: Gameplay.ModelDelegate
            {
                id: loaderGrid
                implicitWidth: tableView.width / sokobanModel.columnCount()
                implicitHeight: tableView.height / sokobanModel.rowCount()

                Connections
                {
                    target: root
                    onUpdateState: loaderGrid.reload()
                }

                Connections
                {
                    target: sokobanModel
                    onData_changed_custom:
                    {
                        if (row === model.row && col === model.column)
                            loaderGrid.reload();
                    }

                    onMoved_up:    playerState = "up"
                    onMoved_down:  playerState = "down"
                    onMoved_left:  playerState = "left"
                    onMoved_right: playerState = "right"
                }
            }
        }
    }

    onUpdateState: tableView.forceLayout();

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
}

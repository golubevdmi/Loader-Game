import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtMultimedia 5.0
import SokobanModel 1.0

ApplicationWindow
{
    id: root
    visible: true
    width: 1280
    //height: 960
    height: 600
    minimumWidth: 640
    minimumHeight: 480
    color: "#09102B"
    title: qsTr("Sakoban")

    menuBar: WindowMenu {}
    header: WindowHeader { colorLvl: "#48d1cc"; colorLabel: root.color; colorButton: root.color; }

    TableView
    {
        id: tableView
        anchors.fill: parent
        clip: true
        model: SokobanModel { id: sokobanModel }
        delegate: ModelDelegate
        {
            id: loaderGrid
            implicitWidth: root.contentItem.width / sokobanModel.columnCount()
            implicitHeight: root.contentItem.height / sokobanModel.rowCount()
            playerState: "down"

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
        onWidthChanged:  tableView.forceLayout();
        onHeightChanged: tableView.forceLayout();
    }

    Item
    {
        id: keysNavigation
        anchors.fill: parent
        focus: true
        Keys.onUpPressed:    sokobanModel.moveUp();
        Keys.onDownPressed:  sokobanModel.moveDown();
        Keys.onRightPressed: sokobanModel.moveRight();
        Keys.onLeftPressed:  sokobanModel.moveLeft();

        onFocusChanged: keysNavigation.focus = true
    }
}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtMultimedia 5.0
import GridModel 1.0


ApplicationWindow
{
    property color labelColor: "#483d8b"
    property color bnColor: root.color

    id: root
    visible: true
    width: 1280
    //height: 960
    height: 600
    minimumWidth: 640
    minimumHeight: 480
    color: "#09102B"
    title: qsTr("Loader Game")



    menuBar: MenuBar
    {
        Menu
        {
            title: qsTr("&File")
            MenuSeparator { }
            Action
            {
                text: qsTr("&Quit")
                icon.source: "qrc:/icons/icons/exit.png"
                shortcut: StandardKey.Quit
                onTriggered: Qt.quit()
            }
        }
        Menu
        {
            title: qsTr("&Edit")
            Action
            {
                text: qsTr("&Undo")
                icon.source: "qrc:/icons/icons/undo.png"
                shortcut: StandardKey.Undo
                onTriggered: gridModel.undo()
            }
            Action
            {
                text: qsTr("&Redo")
                icon.source: "qrc:/icons/icons/redo.png"
                shortcut: StandardKey.Redo
                onTriggered: gridModel.redo()
            }
        }
        Menu
        {
            title: qsTr("&Help")
            Action
            {
                text: qsTr("&About")
                icon.source: "qrc:/icons/icons/about.png"
            }
        }
    }
    header: WindowHeader {}

    TableView
    {
        id: tableView
        anchors.fill: parent
        clip: true
        model: gridModel
        GridModel
        {
            id: gridModel
        }
        delegate: ModelDelegate
        {
            id: loaderGrid
            implicitWidth: root.contentItem.width / gridModel.columnCount()
            implicitHeight: root.contentItem.height / gridModel.rowCount()
            playerState: "down"

            Connections
            {
                target: gridModel
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
        Keys.onUpPressed:    gridModel.moveUp();
        Keys.onDownPressed:  gridModel.moveDown();
        Keys.onRightPressed: gridModel.moveRight();
        Keys.onLeftPressed:  gridModel.moveLeft();

        onFocusChanged: keysNavigation.focus = true
    }
}

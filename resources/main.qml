import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import GridModel 1.0


ApplicationWindow
{
    property color labelColor: "#483d8b"
    property color bnColor: root.color

    id: root
    visible: true
    width: 1280
    height: 960
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
                icon.source: "qrc:/images/resources/exit.png"
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
                icon.source: "qrc:/images/resources/undo.png"
                shortcut: StandardKey.Undo
                onTriggered: gridModel.undo()
            }
            Action
            {
                text: qsTr("&Redo")
                icon.source: "qrc:/images/resources/redo.png"
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
                icon.source: "qrc:/images/resources/about.png"
            }
        }
    }
    header: RowLayout
    {

        LoaderGirdButton
        {
            Layout.alignment: Qt.AlignLeft
            backgroundColor: bnColor
            text: qsTr("Previous")
            onClicked: gridModel.previous()
        }
        LoaderGirdButton
        {
            Layout.alignment: Qt.AlignLeft
            backgroundColor: bnColor
            text: qsTr("Next")
            onClicked: gridModel.next()
        }
        LabelInformation
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Level:"
            text2: gridModel.level
            color: labelColor
        }

        Item
        {
            id: spacerHeaderItem
            Layout.fillWidth: true
            Layout.fillHeight: true
            Rectangle { anchors.fill: parent; color: root.color } // to visualize the spacer
        }

        LoaderGirdButton
        {
            Layout.alignment: Qt.AlignLeft
            backgroundColor: root.color
            text: qsTr("Reset")
            onClicked: gridModel.reset()
        }
        LabelInformation
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Cargos:"
            text2: gridModel.cargos
            color: labelColor
        }
        LabelInformation
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Moves:"
            text2: gridModel.nMoves
            color: labelColor
        }
        LabelInformation
        {
            Layout.alignment: Qt.AlignRight
            text1: "Cargos Left:"
            text2: gridModel.cargosLeft
            color: labelColor
        }
    }

    TableView
    {
        id: tableView
        anchors.fill: parent
        clip: true
        model: GridModel
        {
            id: gridModel
        }
        delegate: LoaderGridDelegate
        {
            id: loaderGrid
            implicitWidth: root.contentItem.width / gridModel.columnCount()
            implicitHeight: root.contentItem.height / gridModel.rowCount()
        }
        onWidthChanged: tableView.forceLayout();
        onHeightChanged: tableView.forceLayout();
    }

    Item
    {
        id: keysNavigation
        anchors.fill: parent
        focus: true
        Keys.onUpPressed: gridModel.moveUp();
        Keys.onDownPressed: gridModel.moveDown();
        Keys.onRightPressed: gridModel.moveRight();
        Keys.onLeftPressed: gridModel.moveLeft();

        onFocusChanged: keysNavigation.focus = true
    }
}

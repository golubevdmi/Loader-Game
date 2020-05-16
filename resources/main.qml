import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import GridModel 1.0


ApplicationWindow
{
    id: root
    visible: true
    width: 640
    height: 400
    minimumWidth: 400
    minimumHeight: 220
    color: "#09102B"
    title: qsTr("Loader Game")

    GridModel
    {
        id: gridModel
    }
    Component
    {
        id: gridDelegate
        Rectangle
        {
            implicitWidth: 40
            implicitHeight: implicitWidth
            color:
            {
                if (LoaderPlayer == true)
                    "green";
                else if (Cargo == true)
                    "blue";
                else if (CargoDestination == true)
                    "purple";
                else if (Barrier == true)
                    "black";
                else
                    "white";
            }
            Text
            {
                text: display
                font.pointSize: 12
                anchors.centerIn: parent
            }
        }
    }

    TableView
    {
        id: gridView
        anchors.fill: parent
        clip: true
        model: gridModel
        delegate: gridDelegate
        contentX: (contentWidth - parent.width) / 2;
        contentY: (contentHeight - parent.height) / 2;
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
    }

    header: toolBar
    ToolBar
    {
        id: toolBar
        RowLayout
        {
            LoaderGirdButton
            {
                text: qsTr("5x5")
                onClicked: gridModel.grid5x5()
            }
            LoaderGirdButton
            {
                text: qsTr("10x10")
                onClicked: gridModel.grid10x10()
            }
            LoaderGirdButton
            {
                text: qsTr("5x5")
                onClicked: gridModel.grid15x15()
            }
        }
    }
    Shortcut { sequence: StandardKey.Quit; onActivated: Qt.quit() }
}

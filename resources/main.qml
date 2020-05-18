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
    height: 480
    minimumWidth: 320
    minimumHeight: 240
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
            backgroundColor: root.color
            text: qsTr("5x5")
            onClicked: gridModel.grid5x5()
        }
        LoaderGirdButton
        {
            Layout.alignment: Qt.AlignLeft
            backgroundColor: root.color
            text: qsTr("10x10")
            onClicked: gridModel.grid10x10()
        }
        LoaderGirdButton
        {
            Layout.alignment: Qt.AlignLeft
            backgroundColor: root.color
            text: qsTr("15x15")
            onClicked: gridModel.grid15x15()
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
    }
    footer: ToolBar
    {
        RowLayout
        {
            anchors.fill: parent
            LabelInformation
            {
                id: labelCargos
                Layout.alignment: Qt.AlignLeft
                text1: "Cargos:"
                color: root.color
            }
            LabelInformation
            {
                id: labelCargosDst
                Layout.alignment: Qt.AlignLeft
                text1: "Cargos Dst:"
                color: root.color
            }
            LabelInformation
            {
                id: labelBarriers
                Layout.alignment: Qt.AlignLeft
                text1: "Barriers:"
                color: root.color
            }

            Item
            {
                id: spacerFooterItem
                Layout.fillWidth: true
                Layout.fillHeight: true
                Rectangle { anchors.fill: parent; color: root.color } // to visualize the spacer
            }

            LabelInformation
            {
                id: labelCargosLeft
                Layout.alignment: Qt.AlignRight
                text1: "Cargos Left:"
                color: root.color
            }
        }
    }

    TableView
    {
        id: tableView
        anchors.fill: parent
        clip: true
        rowSpacing: 1
        columnSpacing: 1
        model: gridModel
        GridModel
        {
            id: gridModel
            onGrid_changed:
            {
                labelCargos.text2 = gridModel.getFieldsCargos();
                labelCargosDst.text2 = gridModel.getFieldsCargosDestination();
                labelBarriers.text2 = gridModel.getFieldsBarriers();
                labelCargosLeft.text2 = gridModel.getFieldsCargosDestination();
            }
            onCargos_left: labelCargosLeft.text2 = nCargos
            Component.onCompleted: grid5x5()
        }
        delegate: LoaderGridDelegate
        {
            id: loaderGrid
            implicitWidth: root.contentItem.width / gridModel.columnCount()
            implicitHeight: root.contentItem.height / gridModel.rowCount()
            colorCell:
            {
                if (Cargo == true)
                    "blue";
                else if (CargoDestination == true)
                    "purple";
                else if (Barrier == true)
                    "black";
                else
                    "white";
            }
            colorCircle:
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

import QtQuick 2.12
import QtQuick.Controls 2.12

MenuBar
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

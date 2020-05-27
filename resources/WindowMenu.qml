import QtQuick 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12

MenuBar
{
    Menu
    {
        title: qsTr("&File")
        MenuSeparator { }
        Action
        {
            text: qsTr("&Exit")
            icon.source: "qrc:/icons/icons/exit.png"
            shortcut: StandardKey.Quit
            onTriggered: msgQuit.setVisible(true)
        }

        MessageDialog
        {
            id: msgQuit
            title: "Exit?"
            text: "Do you want exit?"
            icon: StandardIcon.Question
            modality: Qt.ApplicationModal
            standardButtons: StandardButton.Yes | StandardButton.No
            onYes: Qt.quit()
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
            shortcut: StandardKey.HelpContents
            onTriggered: msgAbout.setVisible(true)

        }
        MessageDialog
        {
            id: msgAbout
            title: "About"
            text: "Free demo version of Sokoban game"
            modality: Qt.ApplicationModal
        }
    }
}

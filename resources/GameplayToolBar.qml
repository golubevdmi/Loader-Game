import QtQuick 2.12
import QtQuick.Layouts 1.3

RowLayout
{
    property color colorArea: "white"
    property color colorLvl: "white"
    property color colorLabel: "white"
    property color colorButton: "white"

    height: 40

    ManageButton
    {
        audioFile: "qrc:/sounds/sounds/sound_bn1.wav"
        Layout.alignment: Qt.AlignLeft
        backgroundColor: colorButton
        text: qsTr("Previous")
        onClicked: sokobanModel.previous()
    }
    ManageButton
    {
        audioFile: "qrc:/sounds/sounds/sound_bn2.wav"
        Layout.alignment: Qt.AlignLeft
        backgroundColor: colorButton
        text: qsTr("Next")
        onClicked: sokobanModel.next()
    }
    ManageButton
    {
        audioFile: "qrc:/sounds/sounds/sound_bn3.wav"
        Layout.alignment: Qt.AlignLeft
        backgroundColor: colorButton
        text: qsTr("Reset")
        onClicked: sokobanModel.reset()
    }

    Item
    {
        Layout.fillWidth: true
    }

    InfoLabel
    {
        Layout.alignment: Qt.AlignLeft
        text1: "Level:"
        text2: sokobanModel.level
        color: colorLvl
    }
    InfoLabel
    {
        Layout.alignment: Qt.AlignLeft
        text1: "Step:"
        text2: sokobanModel.step
        color: colorLabel
    }
    InfoLabel
    {
        Layout.alignment: Qt.AlignLeft
        text1: "Moves:"
        text2: sokobanModel.nMoves
        color: colorLabel
    }
    InfoLabel
    {
        Layout.alignment: Qt.AlignLeft
        text1: "Cargos:"
        text2: sokobanModel.cargos
        color: colorLabel
    }
    InfoLabel
    {
        Layout.alignment: Qt.AlignRight
        text1: "Cargos Left:"
        text2: sokobanModel.cargosLeft
        color: colorLabel
    }
}

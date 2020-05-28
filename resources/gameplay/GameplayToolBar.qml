import QtQuick 2.12
import QtQuick.Layouts 1.3

Rectangle
{
    property var modelObj
    property color colorArea: "white"
    property color colorLvl: "white"
    property color colorLabel: "white"
    property color colorButton: "white"

    id: root
    color: colorArea
    height: 50

    RowLayout
    {
        id: layout
        anchors.fill: parent
        ManageButton
        {
            audioFile: "qrc:/sounds/sounds/sound_bn1.wav"
            Layout.alignment: Qt.AlignLeft
            backgroundColor: colorButton
            text: qsTr("Previous")
            onClicked: modelObj.previous()
        }
        ManageButton
        {
            audioFile: "qrc:/sounds/sounds/sound_bn2.wav"
            Layout.alignment: Qt.AlignLeft
            backgroundColor: colorButton
            text: qsTr("Next")
            onClicked: modelObj.next()
        }
        ManageButton
        {
            audioFile: "qrc:/sounds/sounds/sound_bn3.wav"
            Layout.alignment: Qt.AlignLeft
            backgroundColor: colorButton
            text: qsTr("Reset")
            onClicked: modelObj.reset()
        }

        Item
        {
            Layout.fillWidth: true
        }

        InfoLabel
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Level:"
            text2: modelObj.level
            color: colorLvl
        }
        InfoLabel
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Step:"
            text2: modelObj.step
            color: colorLabel
        }
        InfoLabel
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Moves:"
            text2: modelObj.nMoves
            color: colorLabel
        }
        InfoLabel
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Cargos:"
            text2: modelObj.cargos
            color: colorLabel
        }
        InfoLabel
        {
            Layout.alignment: Qt.AlignRight
            text1: "Cargos Left:"
            text2: modelObj.cargosLeft
            color: colorLabel
        }
    }
}

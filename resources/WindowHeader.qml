import QtQuick 2.12
import QtQuick.Layouts 1.3

RowLayout
    {
        ManageButton
        {
            Layout.alignment: Qt.AlignLeft
            backgroundColor: bnColor
            text: qsTr("Previous")
            onClicked: gridModel.previous()
            audioFile: "qrc:/sounds/sounds/sound_bn1.wav"
        }
        ManageButton
        {
            audioFile: "qrc:/sounds/sounds/sound_bn2.wav"
            Layout.alignment: Qt.AlignLeft
            backgroundColor: bnColor
            text: qsTr("Next")
            onClicked: gridModel.next()
        }
        ManageButton
        {
            audioFile: "qrc:/sounds/sounds/sound_bn3.wav"
            Layout.alignment: Qt.AlignLeft
            backgroundColor: root.color
            text: qsTr("Reset")
            onClicked: gridModel.reset()
        }

        Item
        {
            id: spacerHeaderItem
            Layout.fillWidth: true
            Layout.fillHeight: true
            Rectangle { anchors.fill: parent; color: root.color } // to visualize the spacer
        }

        InfoLabel
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Level:"
            text2: gridModel.level
            color: "#48d1cc"
        }
        InfoLabel
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Step:"
            text2: gridModel.step
            color: labelColor
        }
        InfoLabel
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Moves:"
            text2: gridModel.nMoves
            color: labelColor
        }
        InfoLabel
        {
            Layout.alignment: Qt.AlignLeft
            text1: "Cargos:"
            text2: gridModel.cargos
            color: labelColor
        }
        InfoLabel
        {
            Layout.alignment: Qt.AlignRight
            text1: "Cargos Left:"
            text2: gridModel.cargosLeft
            color: labelColor
        }
    }

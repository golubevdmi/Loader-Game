import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import "./" as Gameplay
import "../items" as SokobanItems

ToolBar
{
    property var modelObj

    id: root
    //position: ToolBar.Header
    implicitHeight: 70

    Rectangle
    {
        anchors.fill: parent
        color: "black"
        RowLayout
        {
            id: layout
            anchors.fill: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 20
            Gameplay.Button
            {
                audioFile: "qrc:/sounds/sounds/sound_bn1.wav"
                text: qsTr("Previous")
                onClicked: modelObj.previous()
            }
            Gameplay.Button
            {
                audioFile: "qrc:/sounds/sounds/sound_bn2.wav"
                text: qsTr("Next")
                onClicked: modelObj.next()
            }
            Gameplay.Button
            {
                audioFile: "qrc:/sounds/sounds/sound_bn3.wav"
                text: qsTr("Reset")
                onClicked: modelObj.reset()
            }

            SokobanItems.Spacer { Layout.fillWidth: true }

            Gameplay.Info
            {
                text1: "Level:"
                text2: modelObj.level
                color: "#1e90ff"
            }
            Gameplay.Info
            {
                text1: "Step:"
                text2: modelObj.step
            }
            Gameplay.Info
            {
                text1: "Moves:"
                text2: modelObj.nMoves
            }
            Gameplay.Info
            {
                text1: "Cargos:"
                text2: modelObj.cargos
            }
            Gameplay.Info
            {
                text1: "Cargos Left:"
                text2: modelObj.cargosLeft
            }
        }
    }
}

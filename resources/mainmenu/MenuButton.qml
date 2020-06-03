import QtQuick 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.12
import "../items" as SokobanItems


SokobanItems.Button
{
    property string audioFileOnSelected: "qrc:/sounds/sounds/sound_bn_menu.mp3"
    signal playSound

    id: root
    implicitWidth: 300
    implicitHeight: 30

    Audio { id: soundCurrent; source: audioFileOnSelected }
    onPlaySound: soundCurrent.play()
}

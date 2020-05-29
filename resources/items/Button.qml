import QtQuick 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.0
import "./" as SokobanItems

Button
{
    property color downColor: "gray"
    property alias bnColor: bnBackground.color
    property alias audioFile: sound.source
    property int fontSize: 10

    id: root
    implicitWidth: 30
    implicitHeight: 30

    contentItem: SokobanItems.Text
    {
        text: root.text
        font.pointSize: fontSize
        color: root.down ? downColor : sourceColor
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: SokobanItems.Rectangle { id: bnBackground }

    Audio { id: sound }

    onFocusChanged:
    {
        //sound.play();
    }
}

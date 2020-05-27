import QtQuick 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.0

Button
{
    property color backgroundColor
    property alias audioFile: sound.source

    id: root
    contentItem: Text
    {
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: root.down ? "gray" : "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle
    {
        id: backgroundRectangle
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        color: root.down ? "white" : backgroundColor
        border.color: "white"
        border.width: 2
        radius: 2
    }

    Audio
    {
        id: sound
    }

    onClicked:
    {
        //sound.play();
    }
}

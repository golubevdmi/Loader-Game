import QtQuick 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.0

Button
{
    property color bgColor: "#09102B"
    property color txtColor: "white"
    property int bnWidth: 200
    property int bnHeight: 40
    property alias audioFile: sound.source

    id: root
    contentItem: Text
    {
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: root.down ? "gray" : txtColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle
    {
        id: backgroundRectangle
        implicitWidth: bnWidth
        implicitHeight: bnHeight
        opacity: enabled ? 1 : 0.3
        color: bgColor
        border.color: "white"
        border.width: 2
        radius: 2
    }

    Audio
    {
        id: sound
    }

    onFocusChanged:
    {
        //sound.play();
    }
}

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtMultimedia 5.0

Button
{
    property color bgColor: "transparent"
    property color txtColor: "black"
    property int bnWidth: 300
    property int bnHeight: 40
    property alias audioFile: sound.source

    id: root

    contentItem: Text
    {
        id: text
        text: root.text
        font.family: "Helvetica"
        font.pixelSize: 25
        font.bold: true
        style: Text.Outline
        styleColor: "white"
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

import QtQuick 2.12
import QtQuick.Controls 2.12
import "../items" as SokobanItems

SokobanItems.Rectangle
{
    property alias text1: text1.text
    property alias text2: text2.text
    property int margin: 5
    property int fontSize: 15

    id: root
    implicitWidth: 130
    implicitHeight: 40
    color: "#5f9ea0"

    SokobanItems.Text
    {
        id: text1
        font.pixelSize: fontSize
        anchors.left: root.left
        anchors.leftMargin: root.margin
        anchors.verticalCenter: root.verticalCenter
    }
    SokobanItems.Text
    {
        id: text2
        font.pixelSize: fontSize
        anchors.right: root.right
        anchors.rightMargin: root.margin
        anchors.verticalCenter: root.verticalCenter
    }
}

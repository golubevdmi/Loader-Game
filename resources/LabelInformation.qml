import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    property alias text1: labelPre.text
    property alias text2: labelPost.text

    id: root
    implicitWidth: 100
    implicitHeight: 40
    opacity: enabled ? 1 : 0.3
    border.color: "white"
    border.width: 2
    radius: 2

    Label
    {
        id: labelPre
        anchors
        {
            left: parent.left
            leftMargin: 5
            verticalCenter: parent.verticalCenter
        }
        color: "white"
        font.pixelSize: 12
        font.italic: true
    }
    Label
    {
        id: labelPost
        anchors
        {
            right: parent.right
            rightMargin: 5
            verticalCenter: parent.verticalCenter
        }
        color: "white"
        font.pixelSize: 12
        font.italic: true
    }
}

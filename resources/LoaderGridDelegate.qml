import QtQuick 2.12
import QtQuick.Controls 2.12


Rectangle
{
    property alias colorCell: root.color
    property alias colorCircle: delegateRect.color
    property alias text: text.text

    id: root
    Text
    {
        id: text
        font.pointSize: 12
        anchors.centerIn: parent
    }

    Rectangle
    {
        id: delegateRect
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height) / 2
        height: width
        radius: width * 0.5
        border.color: "black"
        border.width: 2


        ColorAnimation
        {
            target: root
            from: "red"
            to: "purple"
            duration: 100
        }
    }
}


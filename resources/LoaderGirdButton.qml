import QtQuick 2.12
import QtQuick.Controls 2.12

Button
{
    id: root
    contentItem: Text
    {
        text: root.text
        font: root.font
        opacity: enabled ? 1.0 : 0.3
        color: root.down ? "black" : "#09102B"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle
    {
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.3
        border.color: root.down ? "#black" : "#09102B"
        border.width: 5
        radius: 5
    }
}

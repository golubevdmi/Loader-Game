import QtQuick 2.12
import QtQuick.Controls 2.12

Component
{
    Image
    {
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectCrop
        scale: 0.8
        width: Math.min(parent.implicitWidth, parent.implicitHeight)
        height: width
        source: sourceImage
    }
}

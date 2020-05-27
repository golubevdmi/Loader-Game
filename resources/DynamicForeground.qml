import QtQuick 2.12
import QtQuick.Controls 2.12

Component
{
    AnimatedImage
    {
        fillMode: Image.PreserveAspectCrop
        scale: 0.8
        width: Math.min(parent.implicitWidth, parent.implicitHeight)
        height: width
        speed: 0.5
        source: sourceImage
    }
}

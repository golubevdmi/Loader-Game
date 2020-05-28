import QtQuick 2.12
import QtQuick.Controls 2.12

Component
{
    AnimatedImage
    {
        fillMode: Image.PreserveAspectFit
        scale: 0.8
        height: width
        speed: 0.5
        source: sourceImage
    }
}

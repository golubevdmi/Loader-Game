import QtQuick 2.12
import QtQuick.Controls 2.12

Component
{
    Image
    {
        fillMode: Image.PreserveAspectFit
        scale: 0.8
        height: width
        source: sourceImage
    }
}

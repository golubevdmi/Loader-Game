import QtQuick 2.12
import QtQuick.Controls 2.12

AnimatedSprite
{
    property bool role: false

    id: sprite
    anchors.centerIn: parent
    scale: 0.8
    width: Math.min(parent.implicitWidth, parent.implicitHeight)
    height: width

    running: role
    interpolate: true
    frameDuration: 100

    Component.onCompleted: { if (!role) source = ""; }
}

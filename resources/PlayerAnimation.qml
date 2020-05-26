import QtQuick 2.12
import QtQuick.Controls 2.12

AnimatedSprite
{
    property bool role: false

    id: sprite
    anchors.centerIn: parent
    scale: 0.8
    frameWidth: 50
    frameHeight: 50
    width: Math.min(parent.implicitWidth, parent.implicitHeight)
    height: width

    running: role
    frameCount: 4
    interpolate: true
    frameDuration: 100

    states: [
        State {
            name: "up"
            PropertyChanges { target: playerSprite; frameY: frameHeight * 1; }
        },
        State {
            name: "down"
            PropertyChanges { target: playerSprite; frameY: frameHeight * 0; }
        },
        State {
            name: "left"
            PropertyChanges { target: playerSprite; frameY: frameHeight * 2; }
        },
        State {
            name: "right"
            PropertyChanges { target: playerSprite; frameY: frameHeight * 3; }
        }
    ]

    Component.onCompleted: { if (!role) source = ""; }
}

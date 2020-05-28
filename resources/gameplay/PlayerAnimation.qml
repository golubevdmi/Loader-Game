import QtQuick 2.12
import QtQuick.Controls 2.12

Component
{
    AnimatedSprite
    {
        id: sprite
        scale: 0.8
        frameWidth: 50
        frameHeight: 50
        height: width
        running: true
        frameCount: 4
        interpolate: true
        frameDuration: 100

        source: sourceImage
        state: currentPlayerState

        states: [
            State {
                name: "up"
                PropertyChanges { target: sprite; frameY: frameHeight * 1; }
            },
            State {
                name: "down"
                PropertyChanges { target: sprite; frameY: frameHeight * 0; }
            },
            State {
                name: "left"
                PropertyChanges { target: sprite; frameY: frameHeight * 2; }
            },
            State {
                name: "right"
                PropertyChanges { target: sprite; frameY: frameHeight * 3; }
            }
        ]
    }
}

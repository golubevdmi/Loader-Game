import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    id: root

    //
    // Static sprites

    Image
    {
        id: bgSprite
        anchors.fill: parent
        source:
        {
            if (Barrier == true)
                return "qrc:/sprites/resources/field_wall.png";
            else
                return "qrc:/sprites/resources/field_floor.png";
        }
        sourceSize: Qt.size(width, height)
    }

    Image
    {
        id: fgSprite
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectCrop
        scale: 0.8
        width: Math.min(parent.implicitWidth, parent.implicitHeight)
        height: width

        source:
        {
            if (Cargo == true && CargoDestination == true)
                return "qrc:/sprites/resources/field_delivered.png";
            else if (Cargo == true)
                return "qrc:/sprites/resources/field_cargo.png";
            else
                return "";
        }
    }

    SokobanAnimatedSprite
    {
        id: playerSprite
        role: LoaderPlayer
        frameWidth: 227
        frameHeight: 294
        frameCount: 4
        source: "qrc:/sprites/resources/field_player_poses.png"
    }
    SokobanAnimatedSprite
    {
        id: cargodstSprite
        role: { CargoDestination && !Cargo && !LoaderPlayer }
        frameWidth: 50
        frameCount: 4
        frameDuration: 3000
        source: "qrc:/sprites/resources/field_cargodst.png"

        RotationAnimator
        {
            target: cargodstSprite;
            loops: Animation.Infinite
            from: 0;
            to: 360;
            duration: 3000
            running: true
        }
    }
}


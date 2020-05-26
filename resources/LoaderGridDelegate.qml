import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    property string playerState: "left"

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

    PlayerAnimation
    {
        id: playerSprite
        role: LoaderPlayer
        state: playerState
        source: "qrc:/sprites/resources/field_player_poses.png"
    }
    AnimatedImage
    {
        id: cargodstSprite
        width: Math.min(parent.implicitWidth, parent.implicitHeight)
        height: width
        speed: 0.5
        source:
        {
            if (CargoDestination && !Cargo && !LoaderPlayer)
                return "qrc:/sprites/resources/field_cargodst2.gif";
            else
                return "";
        }
    }
}


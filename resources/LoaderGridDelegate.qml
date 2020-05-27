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
            if (model.Barrier)
                return "qrc:/sprites/sprites/field_wall.png";
            else
                return "qrc:/sprites/sprites/field_floor.png";
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
            if (model.Cargo && model.CargoDestination)
                return "qrc:/sprites/sprites/field_delivered.png";
            else if (model.Cargo)
                return "qrc:/sprites/sprites/field_cargo.png";
            else
                return "";
        }
    }

    PlayerAnimation
    {
        id: playerSprite
        role: model.LoaderPlayer
        state: playerState
        source: "qrc:/sprites/sprites/field_player_poses.png"
    }
    AnimatedImage
    {
        id: cargodstSprite
        width: Math.min(parent.implicitWidth, parent.implicitHeight)
        height: width
        speed: 0.5
        source:
        {
            if (model.CargoDestination && !model.Cargo && !model.LoaderPlayer)
                return "qrc:/sprites/sprites/field_cargodst2.gif";
            else
                return "";
        }
    }
}


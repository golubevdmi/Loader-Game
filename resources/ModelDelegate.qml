import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    property string playerState: "down"
    signal reload

    id: root

    SpriteBackground  { id: spriteFloor }
    SpriteBackground  { id: spriteBarrier }
    SpriteForeground  { id: spriteCargo }
    SpriteForeground  { id: spriteDelivered }
    DynamicForeground { id: spriteCargoDst }
    PlayerAnimation   { id: spritePlayer }

    Loader
    {
        property string sourceImage: "qrc:/sprites/sprites/field_floor.png"

        id: loaderFloor
        active: true
        sourceComponent: spriteFloor
        anchors.fill: root
    }
    Loader
    {
        property string sourceImage: "qrc:/sprites/sprites/field_wall.png"

        id: loaderBarrier
        active: false
        sourceComponent: spriteBarrier
        anchors.fill: root
    }
    Loader
    {
        property string sourceImage: "qrc:/sprites/sprites/field_cargo.png"

        id: loaderCargo
        active: false
        sourceComponent: spriteCargo
        anchors.fill: root
        width: Math.min(root.implicitWidth, root.implicitHeight)
    }
    Loader
    {
        property string sourceImage: "qrc:/sprites/sprites/field_cargodst2.gif"

        id: loaderCargoDst
        active: false
        sourceComponent: spriteCargoDst
        anchors.fill: root
        width: Math.min(root.implicitWidth, root.implicitHeight)
    }
    Loader
    {
        property string sourceImage: "qrc:/sprites/sprites/field_delivered.png"

        id: loaderDelivered
        active: false
        sourceComponent: spriteDelivered
        anchors.fill: root
        width: Math.min(root.implicitWidth, root.implicitHeight)
    }
    Loader
    {
        property string sourceImage: "qrc:/sprites/sprites/field_player_poses.png"
        property string currentPlayerState: playerState

        id: loaderPlayer
        active: false
        sourceComponent: spritePlayer
        anchors.fill: root
        width: Math.min(root.implicitWidth, root.implicitHeight)
    }

    onReload:
    {
        //loaderFloor.active = true;
        loaderBarrier.active = model.Barrier;
        loaderCargo.active = model.Cargo && !model.CargoDestination;
        loaderCargoDst.active = model.CargoDestination && !model.Cargo;
        loaderDelivered.active = model.Cargo && model.CargoDestination;
        loaderPlayer.active = model.LoaderPlayer;
    }

    Component.onCompleted: reload()
}


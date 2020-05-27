import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle
{
    property string playerState: "left"
    signal reload

    id: root

    SpriteBackground { id: spriteFloor }
    SpriteBackground { id: spriteBarrier }

    SpriteForeground { id: spriteCargo }
    SpriteForeground { id: spriteDelivered }

    DynamicForeground { id: spriteCargoDst }

    PlayerAnimation  { id: spritePlayer }


    onReload:
    {
        //reloadSprite(loaderFloor);
        //reloadSprite(loaderBarrier);
        reloadSprite(loaderCargo);
        //reloadSprite(loaderCargoDst);
        reloadSprite(loaderDelivered);
        reloadSprite(loaderPlayer);
    }
    function reloadSprite(loader)
    {
        if (loader)
        {
            loader.active = false;
            loader.active = true;
        }
    }

    Loader
    {
        id: loaderFloor
        property string sourceImage: "qrc:/sprites/sprites/field_floor.png"
        sourceComponent: spriteFloor
        anchors.fill: root
        onActiveChanged: sourceComponent = spriteFloor
    }
    Loader
    {
        id: loaderBarrier
        property string sourceImage: "qrc:/sprites/sprites/field_wall.png"
        sourceComponent: model.Barrier ? spriteBarrier : undefined
        anchors.fill: root
        onActiveChanged: sourceComponent = model.Barrier ? spriteBarrier : undefined
    }
    Loader
    {
        id: loaderCargo
        property string sourceImage: "qrc:/sprites/sprites/field_cargo.png"
        sourceComponent: model.Cargo && !model.CargoDestination ? spriteCargo : undefined
        anchors.fill: root
        onActiveChanged: sourceComponent = model.Cargo && !model.CargoDestination ? spriteCargo : undefined
    }
    Loader
    {
        id: loaderCargoDst
        property string sourceImage: "qrc:/sprites/sprites/field_cargodst2.gif"
        sourceComponent: model.CargoDestination && !model.Cargo ? spriteCargoDst : undefined
        anchors.fill: root
        onActiveChanged: sourceComponent = model.CargoDestination && !model.Cargo ? spriteCargoDst : undefined
    }
    Loader
    {
        id: loaderDelivered
        property string sourceImage: "qrc:/sprites/sprites/field_delivered.png"
        sourceComponent: model.Cargo && model.CargoDestination ? spriteDelivered : undefined
        anchors.fill: root
        onActiveChanged: sourceComponent = model.Cargo && model.CargoDestination ? spriteDelivered : undefined
    }
    Loader
    {
        id: loaderPlayer
        property string sourceImage: "qrc:/sprites/sprites/field_player_poses.png"
        property string currentPlayerState: playerState
        sourceComponent: model.LoaderPlayer ? spritePlayer : undefined
        anchors.fill: root
        onActiveChanged: sourceComponent = model.LoaderPlayer ? spritePlayer : undefined
    }
}


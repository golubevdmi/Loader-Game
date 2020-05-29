import QtQuick 2.12
import "../gameplay" as Gameplay

Grid
{
    property var sokobanSymbolsList:
        [ 99, 100, 101, 131,163,195,196,197,229,261,291,292,293,199,200,201,231,233,
        263,265,295,296,297,203,205,235,236,267,268,299,301,207,208, 209,239,241,271,
        273,303,304,305,179,211,212,213,243,245,275,277,307,308,309,215,216,217,247,249,
        279,280,281,311,313,219,222,251,252,254,283,285,286,315,318 ]

    id: root
    x: 0; y: 0
    rows: 32; columns: 32; spacing: 0

    Repeater
    {
        model: 1024
        Gameplay.SpriteBackground { id: spriteBg }

        Loader
        {
            property string sourceImage:
            {
                var isBox = false;
                for (var i = 0; i < sokobanSymbolsList.length; i = i + 1)
                {
                    if (index + 1 === sokobanSymbolsList[i])
                    {
                        isBox = true;
                        break;
                    }
                }

                if (isBox)
                {
                    return "qrc:/sprites/sprites/field_cargo.png";
                }
                else if (!(index % columns)
                        || index % columns === columns - 1
                        || index < columns
                        || index > columns * rows - columns)
                {
                    return "qrc:/sprites/sprites/field_wall.png";
                }
                else
                {
                    return "qrc:/sprites/sprites/field_floor.png";
                }
            }

            id: loaderFloor
            active: true
            sourceComponent: spriteBg
            width: root.width / root.rows
            height: root.height / root.columns
        }
    }
}

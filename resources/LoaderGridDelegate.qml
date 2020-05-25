import QtQuick 2.12
import QtQuick.Controls 2.12
import "canvas.js" as Figure


Rectangle
{
    id: root

    Image
    {
        id: bgSprite
        anchors.fill: parent
        source:
        {
            if (Barrier == true)
                "qrc:/sprites/resources/field_wall1.png";
            else
                "qrc:/sprites/resources/field_floor1.png";
        }
        sourceSize: Qt.size(width, height)
    }

    Canvas
    {
        property string fgImage

        id: fgSprite
        contextType: "2d"
        anchors.fill: parent
        onPaint:
        {
            if (Cargo == true && CargoDestination == true)
            {
                fgImage = qsTr("qrc:/sprites/resources/field_delivered1.png");
                Figure.drawSprite(context, fgImage, width, height);
            }
            else if (LoaderPlayer == true)
            {
                fgImage = qsTr("qrc:/sprites/resources/field_player1_pose1.png");
                Figure.drawSprite(context, fgImage, width, height);
            }
            else if (Cargo == true)
            {
                fgImage = qsTr("qrc:/sprites/resources/field_cargo1_s1.png");
                Figure.drawSprite(context, fgImage, width, height);
            }
            else if (CargoDestination == true)
            {
                fgImage = qsTr("qrc:/sprites/resources/field_cargodst1_s1.png");
                Figure.drawSprite(context, fgImage, width, height);
            }
        }
        onImageLoaded: { requestPaint(); }
        Component.onCompleted: { loadImage(fgImage); }
    }
}


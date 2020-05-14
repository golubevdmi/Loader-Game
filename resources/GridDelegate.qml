import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import LoaderModel 1.0
import "scripts.js" as Scripts


Component
{
    id: root

    Rectangle
    {
        id: rect
        width: 50
        height: width
        color: Scripts.changeColor(loader_model.role(model.row, model.column))
        TableView.onPooled: rotationAnimation.pause()
        TableView.onReused: rotationAnimation.resume()
        Text
        {
            anchors.centerIn: parent
            //text: model.row + ", " + model.column
            text: display
        }
    }
}

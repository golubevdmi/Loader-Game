import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import GridWindow 1.0
import "scripts.js" as Scripts


ApplicationWindow
{
    id: root
    visible: true
    width: 640
    height: width
    color: "#09102B"
    title: qsTr("Loader Game")

    GridWindow
    {
    }

    header: ToolBar
    {
        height: 50
        RowLayout
        {
            ToolButton
            {
                text: qsTr("5x5")
                //onClicked: gridModel.grid5x5()
            }

            ToolButton
            {
                text: qsTr("10x10")
                //onClicked: gridModel.grid10x10()
            }
            ToolButton
            {
                text: qsTr("15x15")
                //onClicked: gridModel.grid15x15()
            }
        }
    }
}

import QtQuick 2.12
import "../items" as SokobanItems

Component
{
    SokobanItems.Rectangle
    {
        id: rect
        x: 0
        y: 0
        implicitWidth: 400
        implicitHeight: 120
        color: "#800000FF"
        SokobanItems.Text
        {
            font.pointSize: 15
            text: "Level complete"
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        ParallelAnimation
        {
            running: true
            SequentialAnimation
            {
                loops: Animation.Infinite
                PropertyAnimation { target: rect; properties: "implicitWidth"; to: 380;  duration: 500 }
                PropertyAnimation { target: rect; properties: "implicitWidth"; to: 400;  duration: 500 }
            }
            SequentialAnimation
            {
                loops: Animation.Infinite
                PropertyAnimation { target: rect; properties: "implicitHeight"; to: 100;  duration: 500 }
                PropertyAnimation { target: rect; properties: "implicitHeight"; to: 120;  duration: 500 }
            }
        }
    }
}

import QtQuick 2.12
import QtQuick.Controls 2.12
import "../items" as SokobanItems


Button
{
    property bool animationActive: false
    property int fontSize: 17
    property color downColor: "gray"
    property color bgColor: "transparent"

    id: root
    implicitWidth: 300
    implicitHeight: 30

    contentItem: SokobanItems.Text
    {
        id: text
        text: root.text
        font.pointSize: fontSize
        color: root.down ? downColor : sourceColor
        anchors.centerIn: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        Component
        {
            id: textAnimation
            ParallelAnimation
            {
                property int duration: 300

                id: parallelAnimation
                running: true
                SequentialAnimation
                {
                    loops: Animation.Infinite
                    PropertyAnimation {
                        target: text; properties: "font.pointSize"; to: text.font.pointSize - 4; duration: parallelAnimation.duration
                    }
                    PropertyAnimation {
                        target: text; properties: "font.pointSize"; to: text.font.pointSize; duration: parallelAnimation.duration
                    }
                }
            }
        }
        Loader
        {
            id: loaderBnAnimation
            sourceComponent: textAnimation
            active: root.animationActive
            onActiveChanged: { text.font.pointSize = fontSize }
        }
    }

    background: SokobanItems.Rectangle { color: bgColor }
}

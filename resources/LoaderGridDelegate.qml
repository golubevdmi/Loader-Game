import QtQuick 2.12
import QtQuick.Controls 2.12


Rectangle
{
    id: root
    color:
    {
        if (Cargo == true)
            "blue";
        else if (CargoDestination == true)
            "purple";
        else if (Barrier == true)
            "black";
        else
            "white";
    }

    Text
    {
        //text: display
        font.pointSize: 12
        anchors.centerIn: parent
    }

    Rectangle
    {
        id: delegateRect
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height) / 2
        height: width
        radius: width * 0.5
        border.color: "black"
        border.width: 2

        color:
        {
            if (LoaderPlayer == true)
                "green";
            else if (Cargo == true)
                "blue";
            else if (CargoDestination == true)
                "purple";
            else if (Barrier == true)
                "black";
            else
                "white";
        }

        ColorAnimation
        {
            target: root
            from: "red"
            to: "purple"
            duration: 100
        }
    }
}


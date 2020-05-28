import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import QtMultimedia 5.0

Item
{
    signal clickedNewGame
    signal clickedExit

    id: root

    Rectangle
    {
        anchors.fill: parent
        color: "white"

        GridLayout
        {
            id: grid
            anchors.fill: parent
            rows: 2
            columns: 1

            Rectangle
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.column: 0
                Layout.row: 0

                Button
                {
                    text: qsTr("New game")
                    anchors.centerIn: parent
                    width: 300
                    height: 50
                    onClicked: clickedNewGame()
                }
            }

            Rectangle
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.column: 0
                Layout.row: 1

                Button
                {
                    text: qsTr("Exit")
                    anchors.centerIn: parent
                    width: 300
                    height: 50
                    onClicked: clickedExit()
                }
            }
        }
    }
}

import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import StatStorage 1.0
import "items" as SokobanItems
import "mainmenu" as Mainmenu

Item
{
    signal clickedBack

    id: root

    Mainmenu.MenuBackground { id: bgTexture; anchors.fill: parent }

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 50

        RowLayout
        {
            Repeater
            {
                model: 4
                SokobanItems.Rectangle
                {
                    implicitWidth: view.width / 4 - view.anchors.margins / 3
                    implicitHeight: 40
                    color: "darkgray"
                    SokobanItems.Text
                    {
                        text:
                        {
                            switch (index)
                            {
                            case 0:
                                return qsTr("Date");
                            case 1:
                                return qsTr("Level");
                            case 2:
                                return qsTr("Steps");
                            case 3:
                                return qsTr("Moves");
                            }
                        }

                        anchors.centerIn: parent
                        font.pointSize: 15
                    }
                }
            }
        }

        Rectangle
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
            TableView
            {
                id: view
                anchors.margins: 10
                anchors.fill: parent
                model: StatStorage {}

                ScrollBar {}

                delegate: SokobanItems.Rectangle
                {
                    implicitWidth: view.width / 4 - view.anchors.margins / 3
                    implicitHeight: 40
                    color: "black"
                    SokobanItems.Text { text: display; anchors.centerIn: parent; font.pointSize: 15; }
                }
            }
            onWidthChanged: view.forceLayout();
            onHeightChanged: view.forceLayout();
        }
        Mainmenu.MenuButton { text: qsTr("back"); onClicked: clickedBack() }
    }
}

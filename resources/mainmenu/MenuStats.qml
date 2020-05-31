import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import StatStorage 1.0
import "../items" as SokobanItems
import "./" as Mainmenu

Item
{
    id: root
    ColumnLayout
    {
        anchors.fill: parent

        // Table header
        RowLayout
        {
            Repeater
            {
                model: 4
                SokobanItems.Rectangle
                {
                    implicitWidth: view.width / 4
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

        // Table cells
        SokobanItems.Rectangle
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            ScrollView
            {
                anchors.fill: parent
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                TableView
                {
                    id: view
                    anchors.fill: parent
                    anchors.margins: 10
                    rowSpacing: 10
                    model: StatStorage {}

                    delegate: SokobanItems.Rectangle
                    {
                        implicitWidth: view.width / 4
                        implicitHeight: 40
                        color: "black"
                        SokobanItems.Text { text: display; anchors.centerIn: parent; font.pointSize: 15 }
                    }
                }
            }
            onWidthChanged: view.forceLayout();
            onHeightChanged: view.forceLayout();
        }
    }
}

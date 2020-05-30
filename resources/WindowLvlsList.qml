import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.12
import SokobanModel 1.0
import "mainmenu" as Mainmenu
import "items" as SokobanItems

Item
{
    signal clickedBack
    signal clickedListItem(int index)

    id: root

    Mainmenu.MenuBackground { id: bgTexture; anchors.fill: parent }
    SokobanModel { id: sokobanModel }

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 50

        Rectangle
        {
            id: menuNavigation
            width: 300 + 100
            height: root.height / 2
            Layout.alignment: Qt.AlignBottom | Qt.AlignHCenter
            color: "transparent"

            ListView
            {
                id: view

                anchors.margins: 40
                anchors.fill: parent
                spacing: 10
                clip: true
                model: sokobanModel.nLevels

                highlight: Rectangle { color: "darkgrey" }
                highlightFollowsCurrentItem: true

                delegate: Item {
                    id: listDelegate

                    property var view: ListView.view
                    property var isCurrent: ListView.isCurrentItem

                    width: bn.implicitWidth
                    height: bn.implicitHeight

                    Mainmenu.MenuButton
                    {
                        id: bn
                        animationActive: isCurrent
                        text: "Level %1".arg(model.index)
                        onClicked:
                        {
                            view.currentIndex = model.index;
                            clickedListItem(model.index);
                        }
                    }
                }
                Shortcut
                {
                    sequence: "Up"
                    onActivated: view.currentIndex ? view.currentIndex-- : print("main menu: index invalid");
                }
                Shortcut
                {
                    sequence: "Down"
                    onActivated: view.currentIndex < view.count - 1 ? view.currentIndex++ : print("main menu: index invalid");
                }
                Shortcut
                {
                    sequence: "Enter"
                    onActivated: { clickedListItem(view.currentIndex);  }
                }
            }
        }

        Mainmenu.MenuButton { text: qsTr("back"); onClicked: clickedBack() }
    }
}

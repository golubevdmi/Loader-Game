import QtQuick 2.12
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import LoaderModel 1.0

LoaderModel
{
    id: root
    onGrid_changed:
    {
        console.log("grid changed");
        width = maximumWidth = minimumWidth = 50 * root.getWidth();
        height = maximumHeight = minimumHeight = 50 * (root.getHeight() + 1);
    }
}

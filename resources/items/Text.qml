import QtQuick 2.12

Text
{
    property color sourceColor: "transparent"
    property color sourceStyleColor: "white"

    id: text

    font.family: "Helvetica"
    font.bold: true

    style: Text.Outline
    styleColor: sourceStyleColor

    opacity: enabled ? 1.0 : 0.3
    color: sourceColor
    elide: Text.ElideRight
}

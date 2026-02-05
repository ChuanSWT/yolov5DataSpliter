import QtQuick
import QtQuick.Controls
Rectangle{
    Row{
        anchors.fill:parent
        Button{
            height:parent.height
            width:parent.width*0.3
            text: "set"
        }
        Text{
            id:path
            text:"none"
        }
    }
}

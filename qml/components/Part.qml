import QtQuick
Item {

    property string type:"none"
    property string text:input.text
    Row{
        anchors.fill:parent
        Text{
            id:text
            height:parent.height
            text:type
        }
        TextInput{
            id:input
            height:parent.height
            width:parent.width-text.width
            color:"tomato"
        }
    }
}

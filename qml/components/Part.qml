    import QtQuick
    Item {

        property string p_type:"none"
        property alias p_text:input.text
        Row{
            anchors.fill:parent
            Text{
                id:left_text
                height:parent.height
                text:p_type
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            TextInput{
                id:input
                height:parent.height
                width:parent.width-left_text.width
                color:"tomato"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                onTextChanged: {
                    console.log("用户输入：", input.text)
                }
            }
        }
    }

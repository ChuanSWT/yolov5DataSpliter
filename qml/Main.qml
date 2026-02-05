import QtQuick
import DataSpliter
Window{
    width:720
    height:480
    visible:true
    title:"hi"
    Column{
        anchors.fill:parent
        Rectangle{
            width:parent.width
            height:parent.height*0.1
        }

        DicSelector{
            id:source_dic
            width:parent.width
            height:parent.height*0.15
        }
        DicSelector{
            id:target_dic
            width:parent.width
            height:parent.height*0.15
        }

        Row {
            width: parent.width
            height: parent.height*0.6

            Column{
                width: parent.width*0.4
                height: parent.height

                Text {
                    text: qsTr("划分设置")
                    font.pixelSize: 24
                }
                Part{
                    id:train_part
                    width: parent.width
                    height: parent.height*0.3
                    type:"训练集占比(%)"
                }
                Part{
                    id:verify_part
                    width: parent.width
                    height: parent.height*0.3
                    type:"验证集占比(%)"
                }
                Part{
                    id:test_part
                    width: parent.width
                    height: parent.height*0.3
                    type:"测试集占比(%)"
                }
            }

            TextEdit {
                id: textEdit
                width: parent.width*0.3
                height: parent.height
                text: qsTr("Text Edit")
                font.pixelSize: 12
            }

            Column {
                width: parent.width*0.3
                height: parent.height

            }
        }
    }


}

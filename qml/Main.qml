import QtQuick
import QtQuick.Controls
import DataSpliter
Window{
    width:720
    height:480
    visible:true
    title:"hi"
    Column{
        //====上半部分-------------------------------------
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
        //====下半部分-------------------------------------
        Row {
            width: parent.width
            height: parent.height*0.6

            Column{
                width: parent.width*0.4
                height: parent.height

                Text {
                    text: qsTr("划分设置")
                    height: parent.height*0.1
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

            Column {
                width: parent.width*0.3
                height: parent.height
                Text {
                    height: parent.height*0.1
                    text: qsTr("信息")
                    font.pixelSize: 24
                }
                TextEdit {
                    id: textEdit
                    width: parent.width
                    height: parent.height
                    text: qsTr("Text Edit")
                    font.pixelSize: 12
                }
            }

            Column {
                width: parent.width*0.3
                height: parent.height
                Text {
                    height: parent.height*0.1
                    text: qsTr("控制")
                    font.pixelSize: 24
                }
                ProgressBar {
                    from: 0
                    to: 100
                    value: 50
                }
                Button{
                    text:"开始划分"
                }
            }

        }
    }


}

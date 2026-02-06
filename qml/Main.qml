import QtQuick
import QtQuick.Controls
import DataSpliter

Window{
    width:720
    height:480
    visible:true
    title:"hi"
    Backend{
        id:backend
    }

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
            path:backend.source_path
        }
        DicSelector{
            id:target_dic
            width:parent.width
            height:parent.height*0.15
            path:backend.target_path
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

                    p_type:"训练集占比(%)"
                    p_text:backend.train_part
                }
                Part{
                    id:verify_part
                    width: parent.width
                    height: parent.height*0.3

                    p_type:"验证集占比(%)"
                    p_text:backend.verify_part
                }
                Part{
                    id:test_part
                    width: parent.width
                    height: parent.height*0.3
                    p_type:"测试集占比(%)"
                    p_text:backend.test_part
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
                    text: backend.info
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
                    value: backend.progress
                }
                Button{
                    text:"开始划分"
                    onClicked: {
                        backend.UpdateSourcePath(source_dic.path)
                        backend.UpdateTargetPath(target_dic.path)
                        backend.UpdatePart("train",train_part.p_text)
                        backend.UpdatePart("verify",verify_part.p_text)
                        backend.UpdatePart("test",test_part.p_text)
                        backend.START();
                    }
                }
            }

        }
    }


}

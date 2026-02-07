import QtQuick
import QtQuick.Controls
import DataSpliter

Window{
    width:720
    height:480
    visible:true
    title:"yolov5DataSpliter"
    Rectangle{
        anchors.fill:parent
        color:"#F2D79D"
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
                button_name:"源路径"
                button_color:"#F7C75E"
                path_color:"#F5D287"
            }
            DicSelector{
                id:target_dic
                width:parent.width
                height:parent.height*0.15
                path:backend.target_path
                button_name:"目标路径"
                button_color:"#F7C75E"
                path_color:"#F5D287"
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
                        height: parent.height*0.1

                        p_type:"训练集占比(%)"
                        p_text:backend.train_part
                    }
                    Part{
                        id:verify_part
                        width: parent.width
                        height: parent.height*0.1

                        p_type:"验证集占比(%)"
                        p_text:backend.verify_part
                    }
                    Part{
                        id:test_part
                        width: parent.width
                        height: parent.height*0.1
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
                    Item {
                        id:progress_circle
                        width: parent.width
                        height: parent.width

                        property real progress: backend.progress/100.0 //0~100

                        Canvas {
                            id:canvas
                            anchors.fill: parent

                            onPaint: {
                                var ctx = getContext("2d")
                                ctx.clearRect(0, 0, width, height)

                                var centerX = width / 2
                                var centerY = height / 2
                                var radius = width / 2 - 6

                                // 背景圆
                                ctx.beginPath()
                                ctx.arc(centerX, centerY, radius, 0, Math.PI * 2)
                                ctx.strokeStyle = "#dddddd"
                                ctx.lineWidth = 8
                                ctx.stroke()

                                // 进度圆
                                ctx.beginPath()
                                ctx.arc(
                                    centerX,
                                    centerY,
                                    radius,
                                    -Math.PI / 2,
                                    -Math.PI / 2 + Math.PI * 2 * progress_circle.progress
                                )
                                ctx.strokeStyle = "#3b82f6"
                                ctx.lineWidth = 8
                                ctx.stroke()
                            }

                        }
                        onProgressChanged: canvas.requestPaint()
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




}

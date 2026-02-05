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
            id:source
            width:parent.width
            height:parent.height*0.15
        }
        DicSelector{
            id:target
            width:parent.width
            height:parent.height*0.15
        }
    }


}

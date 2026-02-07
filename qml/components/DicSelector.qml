import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import Qt.labs.platform


Item {
    //width: 400
    //height: 100

    property string button_name: "选择目录"
    property string path: ""
    property string button_color
    property string path_color
    FolderDialog {
        id: folderDialog
        title: "选择一个目录"
        currentFolder: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
        onAccepted: {
            console.log("选择的目录:", folderDialog.currentFolder)
            path = folderDialog.currentFolder
        }
    }
    Rectangle{
        anchors.fill:parent
        color:path_color
    Row {
        anchors.fill: parent
        anchors.margins: parent.height * 0.2
        Button {
            height: parent.height
            width: parent.width * 0.3
            background: Rectangle {
                color: button_color
            }
            contentItem: Text {
                text: button_name
                color: "black"          // 👈 文本颜色
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            onClicked: {
                folderDialog.open()
            }
        }

        Text {
            text: path
            height: parent.height
            width: parent.width * 0.7
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter



        }

    }
    }
}

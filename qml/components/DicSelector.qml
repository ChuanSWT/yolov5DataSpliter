import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import Qt.labs.platform
Rectangle{
    FolderDialog {
        id: folderDialog
        title: "选择一个目录"
        currentFolder: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
        onAccepted: {
            console.log("选择的目录:", folderDialog.currentFolder)
            path.text=folderDialog.currentFolder
        }
    }
    Row{
        anchors.fill:parent
        Button{
            height:parent.height
            width:parent.width*0.3
            text: "set"
            onClicked: {
                folderDialog.open()
            }
        }
        Text{
            id:path
            text:"none"
        }
    }
}

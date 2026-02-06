import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import Qt.labs.platform


Item {
    width: 400
    height: 100

    property string button_name: "选择目录"
    property string path: ""

    FolderDialog {
        id: folderDialog
        title: "选择一个目录"
        currentFolder: StandardPaths.standardLocations(StandardPaths.HomeLocation)[0]
        onAccepted: {
            console.log("选择的目录:", folderDialog.currentFolder)
            path = folderDialog.currentFolder
        }
    }

    Row {
        anchors.fill: parent
        anchors.margins: parent.height * 0.2
        Button {
            height: parent.height
            width: parent.width * 0.3
            text: button_name
            onClicked: {
                folderDialog.open()
            }
        }

        Text {
            height: parent.height
            width: parent.width * 0.7
            text: path
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}

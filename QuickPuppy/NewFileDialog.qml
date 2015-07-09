import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Dialog {

    id: root;

    Column {
        anchors.fill: parent
        TreeView {
            // There surely must be an easier way of doing this though.
            height: newFileDialog.height - 90;
            width: newFileDialog.width - 60;
            id: trumpet;
            TableViewColumn {
                title: "File:"
                role: "fileName"
            }
            model: FileSystemModel
        }
        Text {
            text: "File Name:"
        }

        Rectangle {
            color: "white"
            border.color: "black"
            border.width: 1
            height: 20; width: root.width - 60
            radius: 2
            TextInput {
                anchors.fill: parent
                id: input;
                width: root.width -60
                clip: true
            }
        }

    }
    standardButtons: StandardButton.Ok | StandardButton.Cancel
}


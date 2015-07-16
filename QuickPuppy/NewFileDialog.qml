import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Dialog {
    id: root;

    property var _callback: 0

    property var selModInd: treeView.currentIndex
    property string currentDirectory: ""
    property bool ready: false
    onSelModIndChanged: {
        if (selModInd && ready) {
            var basicDirectory = FileSystemModel.getFilePath(selModInd);
            currentDirectory = PuppyCore.directorizeFile(basicDirectory);
        }
        else currentDirectory = "";
    }

    Component.onCompleted: ready = true;

    function openDialog(callback) {
        _callback = callback;
        root.open();
    }

    onCurrentDirectoryChanged: {
        displayProposedFileName();
    }

    function displayProposedFileName() {
        var dir = ( currentDirectory == "" ? FileSystemModel.rootPath() : currentDirectory );
        var filenm = input.text
        dir += "/";
        proposedFileNameText.text = "(" + dir + filenm + ")";
    }

    onAccepted: {
        if (_callback) {
            var dir = ( currentDirectory == "" ? FileSystemModel.rootPath() : currentDirectory );
            var filenm = input.text
            _callback(dir, filenm);
            _callback = 0;
        }
    }

    Column {
        anchors.fill: parent
        TreeView {
            id: treeView;
            // There surely must be an easier way of doing this though.
            height: newFileDialog.height - 90;
            width: newFileDialog.width - 60;
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
            TextField {
                anchors.fill: parent
                id: input;
                width: root.width -60
                clip: true
                onTextChanged: {
                    displayProposedFileName();
                }
            }
        }

        Text {
            id: proposedFileNameText;
            height: 20; width: root.width - 60;

        }

    }
    standardButtons: StandardButton.Ok | StandardButton.Cancel
}


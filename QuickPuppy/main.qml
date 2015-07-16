import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("NotePuppy")
    width: 800
    height: 480
    visible: true
    id: root
    property var editors: 0

    Component.onCompleted: {
        editors = new Object;
    }

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Menu")
            MenuItem {
                text: qsTr("&New")
                shortcut: "Ctrl+N"
                onTriggered: makeNewFile();
            }
            MenuItem {
                text: qsTr("New &Quick File")
                shortcut: "Ctrl+Shift+Q"
                onTriggered: makeNewQuickFile();
            }
            MenuItem {
                text: qsTr("&Import")
                shortcut: "Ctrl+I"
                onTriggered: importFile();
            }
            MenuItem {
                text: qsTr("&Export")
                shortcut: "Ctrl+E"
                onTriggered: exportFile();
            }
            MenuItem {
                text: qsTr("&Rename")
                shortcut: "Ctrl+R"
                onTriggered: renameFile();
            }
            MenuItem {
                text: qsTr("&Delete")
                shortcut: "Ctrl+D"
                onTriggered: deleteFile();
            }
            MenuSeparator {}
            MenuItem {
                text: qsTr("&Translucent")
                shortcut: "Ctrl+T"
                onTriggered: {
                    if (root.opacity === 1)
                        root.opacity = 0.65;
                    else if (root.opacity === 0.65)
                        root.opacity = 0.3;
                    else
                        root.opacity = 1;
                }
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }




    TreeView {
        anchors.fill: parent;
        model: FileSystemModel;
        alternatingRowColors: false; // because they are complex for a minimalist text editor.

        TableViewColumn {
            title: "File:"
            role: "fileName"
            width: (5/8 * root.width)
        }
        TableViewColumn {
            title: "Size"
            role: "fileSize"
            width: (1/8 * root.width)
        }
        TableViewColumn {
            title: "Date Modified"
            role: "fileUpdateTime"
            width: (1/4 * root.width)
        }

        onDoubleClicked: {
            var theFileName = FileSystemModel.data(index, 262);
            openFile(theFileName)
        }

    }

    NewFileDialog {
        id: newFileDialog;
        title: "Plz enter a name for the file"
        width: 3/4*root.width; height: 3/4*root.height
    }


    // Editor handling shizzle
    function openFile(filename) {

        console.log("1")

        // 0. Check the file exists, if not then make it so.
        if (PuppyCore.checkFile(filename))  {
            console.log("2")
            // The file is good. Awesome.
            // 1. Check if the file is open already - it might be.
            if (editors.hasOwnProperty(filename)) {
                // 2. If it is, then focus it.
                  // How'm I gonna do that then????
            }
            // 3. If it ain't, then create an editor
            var editor = Qt.createComponent("EditorWindow.qml");
            console.log("3")

            if (editor.status === Component.Error) {
                console.log("ERROR CREATING EDITOR FOR " + filename)
            }
            else {
                if (editor.status === Component.Ready) {
                    console.log("4")
                    finishEditor(filename, editor);
                }
                else {
                    console.log("5")
                    editor.statusChanged.connect(function() {  console.log("yup"); finishEditor(filename, editor)  })
                }
            }


            // TODO Create edtors
            // 3b. Add the editor to the list of open editors
        }
    }

    function finishEditor(filename, editor) {
        console.log("6")
        var realEditor = editor.createObject(root);
        editors[filename] = realEditor;
        realEditor.setFile(filename);
        realEditor.visible = true;
    }


    // File handling shizzle
    function makeNewFile() {
        newFileDialog.openDialog(makeNewFileCallback);
    }

    function makeNewFileCallback(directory, file) {

        var fileName = PuppyCore.evaluateFile(directory, file)

        openFile(fileName);
    }

    function makeNewQuickFile() {

    }

    function importFile() {

    }

    function exportFile() {

    }

    function renameFile() {

    }

    function deleteFile() {

    }

    function doMakeNewFile() {

    }

}

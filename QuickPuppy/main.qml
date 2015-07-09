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

    }




    Dialog {
        id: newFileDialog;

        width: 3/4*root.width; height: 3/4*root.height

        Column {
            anchors.fill: parent
            TreeView {
                // There surely must be an easier way of doing this though.
                height: newFileDialog.height - 80;
                width: newFileDialog.width - 60;
                id: trumpet;
                TableViewColumn {
                    title: "File:"
                    role: "fileName"
                }
                model: FileSystemModel
            }
            Text {
                text: "dickbutt"
            }
        }
//        standardButtons: StandardButton.Save | StandardButton.Cancel
standardButtons: StandardButton.Ok | StandardButton.Cancel
    }


    function makeNewFile() {
        newFileDialog.open();
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

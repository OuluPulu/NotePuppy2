import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import NotePuppy2 2.0

ApplicationWindow {
    width: 800
    height: 480

    function setFile(filename) {
        console.log("File name is " + filename);
        pfile.setFile(filename);
    }

    function pushFileContents() {
        pfile.setContents(text.text);
    }

    PuppyFile {
        id: pfile

        onFileContentsChanged: {
            text.text = contents;
        }
        onFileError: {
            console.log(message);
        }
    }

    Timer {
        id: timer;
        interval: (1 * 1000);
        repeat: false;
        onTriggered: {
            pushFileContents();
        }
    }

    TextArea {
        id: text
        frameVisible: true;
        anchors.fill: parent
        textFormat: Qt.PlainText
        onTextChanged: {
            if (!timer.running) {
                timer.start();
            }
        }
    }

    Component.onDestruction: {
        pushFileContents();
    }
}


import QtQuick 2.4
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.3
import QtQuick.Window 2.1
import QtQuick.Layouts 1.15

import org.freedesktop.gstreamer.GLVideoItem 1.0

Rectangle {
    visible: true
    width: 640
    height: 480*2

    ColumnLayout {
        anchors.fill: parent

        GstGLVideoItem {
            id: videoItem1
            objectName: "videoItem1"
            Layout.fillHeight: true
            Layout.fillWidth: true

        }

        GstGLVideoItem {
            id: videoItem2
            objectName: "videoItem2"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}

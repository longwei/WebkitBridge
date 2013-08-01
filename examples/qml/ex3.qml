import QtQuick 2.0
import QtWebKit 3.0
import QtWebKit.experimental 1.0

// Example of using QtWebKit2 experimental APIs. Run using "qmlscene".
//
// Also see:
//   https://lists.webkit.org/pipermail/webkit-qt/2011-October/001953.html
//   https://lists.webkit.org/pipermail/webkit-qt/2012-January/002394.html

Item {
    width: 800
    height: 600
    WebView {
        id: webview
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: postButton.top

        experimental.preferences.navigatorQtObjectEnabled: true
        experimental.onMessageReceived: {
            lastReceivedText.text = "Received from web page: " + message.data
            console.log("WebView received Message: " + message.data)
        }

        // Load initial URL on startup
        Component.onCompleted: webview.url = Qt.resolvedUrl("./messagedemo.html")

        onLoadingChanged: webview.experimental.postMessage("Hello WebView")
    }

    Text {
        id: lastReceivedText
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: postButton.right
        height: 50
    }

    Rectangle {
        property int lastSent: 0
        id: postButton

        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 100
        height: 50
        border.width: 2
        border.color: "#aa0000"
        radius: 5
        color: "#cc4444"

        Text {
            anchors.centerIn: parent
            text: "Send!"
            color: "white"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                ++postButton.lastSent
                webview.experimental.postMessage("Received message #"+postButton.lastSent)
            }
        }
    }
}

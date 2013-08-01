import QtQuick 2.0
import QtWebKit 3.0
import QtWebKit.experimental 1.0

// Example of using QtWebKit2 experimental APIs. Run using "qmlscene".

Item {
    width: 800
    height: 600
    WebView {
        id: webview
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.top
        //experimental.flickableViewportEnabled: true
        url: "http://www.ics.com"

        // Load initial URL on startup
        Component.onCompleted: {
            experimental.evaluateJavaScript(console.log("Hello"));
            console.log("User agent: " + experimental.userAgent);
        }
    }
}

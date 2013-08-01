#!/usr/bin/env python
import sys
from PyQt4.QtCore import *
from PyQt4.QtGui import *
from PyQt4.QtWebKit import *


class Browser(QDialog):

    def __init__(self, parent=None):
        super(Browser, self).__init__(parent)

        url = "http://google.com" # the default url

        # widgets
        self.lineedit = QLineEdit(url)

        self.backButton = QPushButton("<")
        self.forwardButton = QPushButton(">")
        self.reloadButton = QPushButton("Reload")
        self.stopButton = QPushButton("Stop")
        self.goButton = QPushButton("Go!")

        self.webview = QWebView()
        self.webview.setUrl(QUrl(url))

        # layout
        hlayout = QHBoxLayout()
        hlayout.addWidget(self.backButton)
        hlayout.addWidget(self.forwardButton)
        hlayout.addWidget(self.reloadButton)
        hlayout.addWidget(self.stopButton)
        hlayout.addWidget(self.lineedit)
        hlayout.addWidget(self.goButton)

        vlayout = QVBoxLayout()
        vlayout.addLayout(hlayout)
        vlayout.addWidget(self.webview)
        self.setLayout(vlayout)
        self.lineedit.setFocus()

        # signals/slots
        self.connect(self.lineedit, SIGNAL("returnPressed()"),
                     self.loadUrl)
        self.connect(self.goButton, SIGNAL("clicked()"),
                     self.loadUrl)
        self.connect(self.backButton, SIGNAL("clicked()"),
                     self.webview.back)
        self.connect(self.forwardButton, SIGNAL("clicked()"),
                     self.webview.forward)
        self.connect(self.reloadButton, SIGNAL("clicked()"),
                     self.webview.reload)
        self.connect(self.stopButton, SIGNAL("clicked()"),
                     self.webview.stop)

        self.setWindowTitle("DanaFox") # heh


    def loadUrl(self):
        text = unicode(self.lineedit.text())
        url = QUrl(text)
        self.webview.setUrl(url)


app = QApplication(sys.argv)
web = Browser()
web.show()
app.exec_()


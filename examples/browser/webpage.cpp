#include <QUiLoader>

#include "browser.h"
#if QT_VERSION < 0x050000
#include "pluginfactory.h"
#endif
#include "webpage.h"

// constructor
WebPage::WebPage(QObject *parent)
    : QWebPage(parent)
{
#if QT_VERSION < 0x050000
    setPluginFactory(new PluginFactory(this));
#endif
}

// create a x-qt-plugin plugin
QObject *WebPage::createPlugin(const QString &classId,
                               const QUrl &/*url*/,
                               const QStringList &paramNames,
                               const QStringList &paramValues)
{
    // use QUiLoader as generic widget factory
    QUiLoader loader;
    QWidget *widget = loader.createWidget(classId, view());

    // set parameters
    if (widget) {
        int index = paramNames.indexOf("name");
        if (index && paramValues.size() > index) {
            widget->setObjectName(paramValues.at(index));
        }
    }

    return widget;
}

// create a new window
QWebPage *WebPage::createWindow(WebWindowType type)
{
    if (type == WebBrowserWindow) {
        Browser *browser = new Browser(0);
        return browser->view()->page();
    } else {
        return QWebPage::createWindow(type);
    }
}

#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QFileInfo>
#include <QLineEdit>
#include <QSettings>
#include <QToolBar>
#include <QWebHistoryItem>
#include <QWebSettings>
#include <QWebView>

#include "configure.h"
#include "spinner.h"
#include "webpage.h"
#include "browser.h"

// constructor
Browser::Browser(QWidget *parent)
    : QMainWindow(parent), urlEdit(new QLineEdit()), spinner(new Spinner()),
      historyMenu(new QMenu("&History"))
{
    setupUi(this);
    webView->setPage(new WebPage(webView));

    // finish go menu
    goMenu->addAction(webView->pageAction(QWebPage::Back));
    goMenu->addAction(webView->pageAction(QWebPage::Forward));
    goMenu->addAction(webView->pageAction(QWebPage::Reload));
    goMenu->addAction(webView->pageAction(QWebPage::Stop));
    goMenu->addSeparator();
    goMenu->addMenu(historyMenu);
    
    // create toolbar
    QToolBar *toolbar = addToolBar("Navigation");
    toolbar->addAction(webView->pageAction(QWebPage::Back));
    toolbar->addAction(webView->pageAction(QWebPage::Forward));
    toolbar->addAction(webView->pageAction(QWebPage::Reload));
    toolbar->addAction(webView->pageAction(QWebPage::Stop));
    toolbar->addWidget(urlEdit);
    toolbar->addWidget(spinner);

    // additional
    initialize();

    // connections
    connect(actionNewWindow, SIGNAL(triggered()),
            this, SLOT(onNewWindow()));
    connect(actionConfigure, SIGNAL(triggered()),
            this, SLOT(onConfigure()));
    connect(urlEdit, SIGNAL(returnPressed()),
            this, SLOT(onUrlEntered()));
    connect(webView, SIGNAL(iconChanged()),
            this, SLOT(onIconChanged()));
    connect(webView, SIGNAL(loadFinished(bool)),
            this, SLOT(onLoadFinished()));
    connect(webView, SIGNAL(loadStarted()),
            this, SLOT(onLoadStarted()));
    connect(webView, SIGNAL(titleChanged(const QString&)),
            this, SLOT(onTitleChanged(const QString&)));
    connect(webView, SIGNAL(urlChanged(const QUrl&)),
            this, SLOT(onUrlChanged(const QUrl&)));
    connect(historyMenu, SIGNAL(aboutToShow()),
            this, SLOT(onHistoryAboutToShow()));
}

// destructor
Browser::~Browser()
{
    // save web settings
    QSettings settings("ICS", "Browser Demo");
    settings.setValue("font/standard",
        webView->settings()->fontFamily(QWebSettings::StandardFont));
    settings.setValue("font/fixed",
        webView->settings()->fontFamily(QWebSettings::FixedFont));
    settings.setValue("font/sansserif",
        webView->settings()->fontFamily(QWebSettings::SansSerifFont));
    settings.setValue("font/serif",
        webView->settings()->fontFamily(QWebSettings::SerifFont));
    settings.setValue("misc/javascript",
        webView->settings()->testAttribute(QWebSettings::JavascriptEnabled));
    settings.setValue("misc/java",
        webView->settings()->testAttribute(QWebSettings::JavaEnabled));
    settings.setValue("misc/plugins",
        webView->settings()->testAttribute(QWebSettings::PluginsEnabled));
    settings.setValue("misc/inspector",
        webView->settings()->testAttribute(QWebSettings::DeveloperExtrasEnabled));
}

// post construction initialization
void Browser::initialize()
{
    // set application data directory
    QString data;
#if QT_VERSION < 0x050000
    data = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#else
    data = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
    if (data.isEmpty()) {
        data = QDir::homePath() + "/." + QCoreApplication::applicationName();
    }
    if (!QFile::exists(data)) {
        QDir dir;
        dir.mkpath(data);
    }

    // set favicon path
    QWebSettings::setIconDatabasePath(data);

    // load settings
    QSettings settings("ICS", "Browser Demo");
    webView->settings()->setFontFamily(QWebSettings::StandardFont,
        settings.value("font/standard").toString());
    webView->settings()->setFontFamily(QWebSettings::FixedFont,
        settings.value("font/fixed").toString());
    webView->settings()->setFontFamily(QWebSettings::SansSerifFont,
        settings.value("font/sansserif").toString());
    webView->settings()->setFontFamily(QWebSettings::SerifFont,
        settings.value("font/serif").toString());
    webView->settings()->setAttribute(QWebSettings::JavascriptEnabled,
        settings.value("misc/javascript").toBool());
    webView->settings()->setAttribute(QWebSettings::JavaEnabled,
        settings.value("misc/java").toBool());
    webView->settings()->setAttribute(QWebSettings::PluginsEnabled,
        settings.value("misc/plugins").toBool());
    webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,
        settings.value("misc/inspector").toBool());
}

// load a given page
void Browser::loadPage(const QString &page)
{
    QUrl url;
    QRegExp scheme("^[a-zA-Z]+\\:.*");
    QString urlstring = page.trimmed();

    // convert string to url
    if (scheme.exactMatch(urlstring)) {
        // full url given
        url.setUrl(urlstring, QUrl::TolerantMode);
    } else if (QFile::exists(urlstring)) {
        // local file
        QFileInfo info(urlstring);
        url = QUrl::fromLocalFile(info.absoluteFilePath());
    } else if (urlstring.indexOf(QLatin1Char('.')) != -1) {
        // looks like a shortened url
        if (urlstring.startsWith(QLatin1String("ftp"))) {
            urlstring = QLatin1String("ftp://") + urlstring;
        } else {
            urlstring = QLatin1String("http://") + urlstring;
        }
        url.setUrl(urlstring, QUrl::TolerantMode);
    } else {
        // everything else
        url.setUrl(urlstring, QUrl::TolerantMode);
    }

    // load url
    webView->load(url);
    webView->setFocus();
}

// return the webview
const QWebView *Browser::view() const
{
    return webView;
}

// open new browser window
void Browser::onNewWindow()
{
    Browser *browser = new Browser(0);
    browser->show();
}

// display configuration dialog
void Browser::onConfigure()
{
    Configure config(webView->settings(), this);
    if (config.exec()) {
        webView->settings()->setFontFamily(QWebSettings::StandardFont,
            config.getStandardFont());
        webView->settings()->setFontFamily(QWebSettings::FixedFont,
            config.getFixedFont());
        webView->settings()->setFontFamily(QWebSettings::SansSerifFont,
            config.getSansSerifFont());
        webView->settings()->setFontFamily(QWebSettings::SerifFont,
            config.getSerifFont());
        webView->settings()->setAttribute(QWebSettings::JavascriptEnabled,
            config.isJavascriptEnabled());
        webView->settings()->setAttribute(QWebSettings::JavaEnabled,
            config.isJavaEnabled());
        webView->settings()->setAttribute(QWebSettings::PluginsEnabled,
            config.isPluginsEnabled());
        webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,
            config.isInspectorEnabled());
    }
}

// favicon has changed
void Browser::onIconChanged()
{
    setWindowIcon(QWebSettings::iconForUrl(webView->url()));
}

// page loading has finished
void Browser::onLoadFinished()
{
    spinner->setAnimation(false);
    setWindowIcon(QWebSettings::iconForUrl(webView->url()));
}

// page loading has started
void Browser::onLoadStarted()
{
    spinner->setAnimation(true);
}

// page title has changed
void Browser::onTitleChanged(const QString &title)
{
    setWindowTitle(title);
}

// page url has changed
void Browser::onUrlChanged(const QUrl &url)
{
    urlEdit->setText(url.toString());
}

// new url entered in edit bar
void Browser::onUrlEntered()
{
    loadPage(urlEdit->text());
}

// update the history menu
void Browser::onHistoryAboutToShow()
{
    QList<QWebHistoryItem> items = webView->history()->items();
    QAction *action;

    historyMenu->clear();
    foreach (QWebHistoryItem item, items) {
        action = new QAction(item.icon(), item.title(), this);
        action->setData(item.url());
        connect(action, SIGNAL(triggered()), this, SLOT(onHistoryItemTriggered()));
        historyMenu->addAction(action);
    }
}

// history menu item has been triggered
void Browser::onHistoryItemTriggered()
{
    QAction *action  = qobject_cast<QAction*>(sender());
    if (action) {
        webView->setUrl(action->data().toUrl());
    }
}


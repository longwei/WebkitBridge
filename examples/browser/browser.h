#ifndef BROWSER_H
#define BROWSER_H

#include <QMainWindow>
#include "ui_browser.h"

class QLineEdit;
class QMenu;
class Spinner;

class Browser : public QMainWindow, private Ui::Browser
{
    Q_OBJECT
public:
    Browser(QWidget *parent=0);
    virtual ~Browser();

    void initialize();
    void loadPage(const QString &page);
    const QWebView *view() const;

private slots:
    void onNewWindow();
    void onConfigure();
    void onUrlEntered();
    void onIconChanged();
    void onLoadFinished();
    void onLoadStarted();
    void onTitleChanged(const QString &title);
    void onUrlChanged(const QUrl &url);
    void onHistoryAboutToShow();
    void onHistoryItemTriggered();


private:
    QLineEdit *urlEdit;
    Spinner *spinner;
    QMenu *historyMenu;
};

#endif // BROWSER_H

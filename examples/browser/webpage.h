#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebPage>

class WebPage : public QWebPage
{
    Q_OBJECT
public:
    WebPage(QObject *parent = 0);

protected:
    virtual QObject *createPlugin(const QString &classId,
                                  const QUrl &url,
                                  const QStringList &paramNames,
                                  const QStringList &paramValues);
    virtual QWebPage *createWindow(WebWindowType type);
};

#endif // WEBPAGE_H

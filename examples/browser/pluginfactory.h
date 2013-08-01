#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H

#include <QWebPluginFactory>

class PluginFactory : public QWebPluginFactory
{
    Q_OBJECT
public:
    PluginFactory(QObject *parent = 0);
    ~PluginFactory();

    QObject *create(const QString &mimeType,
                    const QUrl &url,
                    const QStringList &paramNames,
                    const QStringList &paramValues) const;
    QList<Plugin> plugins() const;
};

#endif // PLUGINFACTORY_H

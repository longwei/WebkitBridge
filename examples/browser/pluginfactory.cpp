#include <QUrl>

#include "pluginfactory.h"
#include "mediaplayer.h"

using namespace Phonon;

// constructor
PluginFactory::PluginFactory(QObject *parent)
    : QWebPluginFactory(parent)
{
}

// destructor
PluginFactory::~PluginFactory()
{
}

// create new plugin
QObject *PluginFactory::create(const QString &mimeType,
                               const QUrl &url,
                               const QStringList &paramNames,
                               const QStringList &paramValues) const
{
    Q_UNUSED(paramNames);
    Q_UNUSED(paramValues);

    // handle phonon capable mimetypes
    if (BackendCapabilities::availableMimeTypes().contains(mimeType)) {
        MediaPlayer *player = new MediaPlayer(url.toString());
        return player;
    }

    return 0;
}

// return list of supported plugins
QList<QWebPluginFactory::Plugin> PluginFactory::plugins() const
{
    Plugin plugin;
    MimeType mimetype;
    QList<Plugin> plugins;

    // create list of phonon supported mimetypes
    plugin.name = "Phonon Plugin";
    foreach (QString name, BackendCapabilities::availableMimeTypes()) {
        mimetype.name = name;
        plugin.mimeTypes << mimetype;
    }
    plugins << plugin;

    return plugins;
}

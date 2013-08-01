#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QDialog>
#include <QWebSettings>
#include "ui_configure.h"

class Configure : public QDialog, private Ui::Configure
{
    Q_OBJECT
public:
    Configure(QWebSettings *settings, QWidget *parent=0);
    virtual ~Configure();

    QWebSettings *webSettings();

    QString getStandardFont() const;
    QString getFixedFont() const;
    QString getSansSerifFont() const;
    QString getSerifFont() const;
    bool isJavascriptEnabled() const;
    bool isJavaEnabled() const;
    bool isPluginsEnabled() const;
    bool isInspectorEnabled() const;
};

#endif // CONFIGURE_H

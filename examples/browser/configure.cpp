#include "configure.h"

// constructor
Configure::Configure(QWebSettings *settings, QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    // init dialog fields
    QFont font;
    font.setFamily(settings->fontFamily(QWebSettings::StandardFont));
    standardFont->setCurrentFont(font);
    font.setFamily(settings->fontFamily(QWebSettings::FixedFont));
    fixedFont->setCurrentFont(font);
    font.setFamily(settings->fontFamily(QWebSettings::SansSerifFont));
    sansSerifFont->setCurrentFont(font);
    font.setFamily(settings->fontFamily(QWebSettings::SerifFont));
    serifFont->setCurrentFont(font);
    javascript->setChecked(settings->testAttribute(QWebSettings::JavascriptEnabled));
    java->setChecked(settings->testAttribute(QWebSettings::JavaEnabled));
    plugins->setChecked(settings->testAttribute(QWebSettings::PluginsEnabled));
    inspector->setChecked(settings->testAttribute(QWebSettings::DeveloperExtrasEnabled));
}

// destructor
Configure::~Configure()
{
}

// return fonts
QString Configure::getStandardFont() const
{
    return standardFont->currentFont().family();
}

QString Configure::getFixedFont() const
{
    return fixedFont->currentFont().family();
}

QString Configure::getSansSerifFont() const
{
    return sansSerifFont->currentFont().family();
}

QString Configure::getSerifFont() const
{
    return serifFont->currentFont().family();
}

bool Configure::isJavascriptEnabled() const
{
    return javascript->isChecked();
}

bool Configure::isJavaEnabled() const
{
    return java->isChecked();
}

bool Configure::isPluginsEnabled() const
{
    return plugins->isChecked();
}

bool Configure::isInspectorEnabled() const
{
    return inspector->isChecked();
}

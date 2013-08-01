#include <QtWebKit>
#include <QWebFrame>
#include "addressbook.h"

const QString showaddress = "showAddress('%1');";

AddressBook::AddressBook(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    QFile file(":/map.html");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    // The following didn't work on Windows and resulted in
    // a Google Maps Key error.
    // map->setHtml(file.readAll(), QUrl(QDir::homePath()));

    map->setHtml(file.readAll(), QUrl("file:///"));

    onRefreshClicked();

    connect(refresh, SIGNAL(clicked()), this, SLOT(onRefreshClicked()));
    connect(map, SIGNAL(loadFinished(bool)), this, SLOT(onRefreshClicked()));
}

AddressBook::~AddressBook()
{
}

void AddressBook::onRefreshClicked()
{
    if (street->text().isEmpty() ||
        city->text().isEmpty() ||
        state->currentText().isEmpty()) {
        return;
    }
        
    QString address = QString("%1, %2, %3")
        .arg(street->text())
        .arg(city->text())
        .arg(state->currentText());

    map->page()->mainFrame()->evaluateJavaScript(showaddress.arg(address));
}

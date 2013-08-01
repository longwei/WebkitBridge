#include <QApplication>
#include "browser.h"

int main(int argc, char **argv)
{
#if QT_VERSION < 0x050000
    Q_INIT_RESOURCE(mediaplayer);
#endif
    QApplication app(argc, argv);

    // set application information
    app.setOrganizationName("Demo");
    app.setApplicationName("browser");

    // create and show browser
    Browser *browser = new Browser();
    if (argc == 2) {
      browser->loadPage(argv[1]);
    }
    browser->show();

    bool status = app.exec();
    delete browser;
    return status;
}
 

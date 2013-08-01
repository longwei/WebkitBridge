#include <QtGui>
#include "addressbook.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    AddressBook widget;
    widget.show();

    return app.exec();
} 

TEMPLATE = app
TARGET =  address
QT += webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

#OBJECTS_DIR = build
#MOC_DIR = build
#UI_DIR = build
#RCC_DIR = build

HEADERS += addressbook.h
SOURCES += addressbook.cpp main.cpp
FORMS += addressbook.ui
RESOURCES += address.qrc

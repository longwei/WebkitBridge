TEMPLATE = app
TARGET = mediaplayer

lessThan(QT_MAJOR_VERSION, 5): QT += phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

FORMS += settings.ui
RESOURCES += mediaplayer.qrc

SOURCES += main.cpp mediaplayer.cpp
HEADERS += mediaplayer.h

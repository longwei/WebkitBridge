TEMPLATE = app
QT += webkit

lessThan(QT_MAJOR_VERSION, 5): CONFIG += uitools
greaterThan(QT_MAJOR_VERSION, 4): QT += uitools widgets webkitwidgets multimedia

lessThan(QT_MAJOR_VERSION, 5): QT += phonon

INCLUDEPATH += .

HEADERS += browser.h \
           configure.h \
           spinner.h \
           webpage.h

SOURCES += main.cpp \
           browser.cpp \
           configure.cpp \
           spinner.cpp \
           webpage.cpp

FORMS += browser.ui \
         configure.ui

### Media player demo stuff (not yet ported to Qt 5)

lessThan(QT_MAJOR_VERSION, 5) {
  INCLUDEPATH += ../mediaplayer
  HEADERS += pluginfactory.h ../mediaplayer/mediaplayer.h
  SOURCES += pluginfactory.cpp ../mediaplayer/mediaplayer.cpp
  FORMS += ../mediaplayer/settings.ui
  RESOURCES += ../mediaplayer/mediaplayer.qrc
}

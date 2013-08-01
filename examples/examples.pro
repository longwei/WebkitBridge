TEMPLATE=subdirs

lessThan(QT_MAJOR_VERSION, 5): SUBDIRS = address browser fetch hello mediaplayer

greaterThan(QT_MAJOR_VERSION, 4): SUBDIRS = address browser fetch hello

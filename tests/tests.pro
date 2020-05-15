TEMPLATE = app
TARGET = fontobene-qt5-tests

QT = core

CONFIG += console c++11 strict_c++
CONFIG -= app_bundle thread

DEFINES += TESTFILEPATH="\\\"$$_PRO_FILE_PWD_/fonto.bene\\\""

SOURCES += \
    main.cpp \

HEADERS += \
    ../fontobene-qt5/exception.h \
    ../fontobene-qt5/font.h \
    ../fontobene-qt5/fontobene.h \
    ../fontobene-qt5/glyph.h \
    ../fontobene-qt5/glyphlist.h \
    ../fontobene-qt5/glyphlistaccessor.h \
    ../fontobene-qt5/glyphlistcache.h \
    ../fontobene-qt5/header.h \
    ../fontobene-qt5/helpers.h \

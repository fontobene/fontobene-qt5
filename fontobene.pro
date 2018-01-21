TEMPLATE = app
TARGET = fontobene-tests

QT += core
QT -= gui widgets

CONFIG += console c++11
CONFIG -= app_bundle

DEFINES += TESTFILEPATH="\\\"$$_PRO_FILE_PWD_/tests/fonto.bene\\\""

SOURCES += \
    tests/main.cpp \

HEADERS += \
    fontobene/exception.h \
    fontobene/font.h \
    fontobene/fontobene.h \
    fontobene/glyph.h \
    fontobene/glyphlist.h \
    fontobene/glyphlistaccessor.h \
    fontobene/header.h \
    fontobene/helpers.h \


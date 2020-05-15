TEMPLATE = lib
TARGET = fontobene-qt5

QT = core

CONFIG += c++11 strict_c++
CONFIG -= thread

HEADERS += \
    exception.h \
    font.h \
    fontobene.h \
    glyph.h \
    glyphlist.h \
    glyphlistaccessor.h \
    glyphlistcache.h \
    header.h \
    helpers.h \

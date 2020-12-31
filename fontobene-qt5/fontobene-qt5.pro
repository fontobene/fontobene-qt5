# fontobene-qt5 is a header-only library, but this qmake config is still useful
# in order to generate an install target for the headers. For some reason, a
# shared library will still be generated, just ignore that when packaging. It
# will not be installed by "make install".

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

INSTALLS += headers

headers.path = $$PREFIX/include/fontobene-qt5/fontobene-qt5
headers.files = $$HEADERS

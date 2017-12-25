#ifndef FONTOBENE_FONT_H
#define FONTOBENE_FONT_H

#include <QtCore>
#include "./header.h"
#include "./glyphlist.h"

namespace fontobene {

struct Font {
    Header header;
    GlyphList glyphs;

    Font() = default;
    Font(const Font& other) = default;

    Font(QTextStream& content) {
        load(content);
    }

    Font(const QString& filepath) {
        loadFromFile(filepath);
    }

    void load(QTextStream& content) {
        header.load(content);
        glyphs.load(content);
    }

    void loadFromFile(const QString& filepath) {
        QFile file(filepath);
        if (!file.open(QFile::ReadOnly)) {
            throw Exception(file.errorString());
        }
        QTextStream stream(&file);
        load(stream);
    }
};

} // namespace fontobene

#endif // FONTOBENE_FONT_H

#ifndef FONTOBENE_GLYPHLIST_H
#define FONTOBENE_GLYPHLIST_H

#include <QtCore>
#include "./glyph.h"

namespace fontobene {

struct GlyphList : public QVector<Glyph> {
    void load(QTextStream& content, bool clearBefore = true, int reserveSize = 200) {
        if (clearBefore) {
            clear();
        }
        if (reserveSize > 0) {
            reserve(reserveSize);
        }
        while (!content.atEnd()) {
            Glyph glyph = Glyph::load(content);
            if (glyph.isValid()) {
                append(glyph);
            }
        }
    }
};

} // namespace fontobene

#endif // FONTOBENE_GLYPHLIST_H


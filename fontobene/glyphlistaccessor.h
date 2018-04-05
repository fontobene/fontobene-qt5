#ifndef FONTOBENE_GLYPHLISTACCESSOR_H
#define FONTOBENE_GLYPHLISTACCESSOR_H

#include <QtCore>
#include "./glyphlistcache.h"

namespace fontobene {

class GlyphListAccessor {
    private:
        const GlyphListCache& _glyphCache;

        QVector<Polyline> getAllPolylinesOfGlyphImpl(const Glyph& glyph, int index) const {
            QVector<Polyline> polylines = glyph.polylines;
            foreach (ushort ref, glyph.references) {
                int refIndex;
                const Glyph& refGlyph = _glyphCache.getGlyph(ref, &refIndex); // can throw
                if (refIndex < index) {
                    polylines += getAllPolylinesOfGlyphImpl(refGlyph, refIndex); // can throw
                } else {
                    // forward references are forbidden (to avoid endless loops)!
                    throw ForwardReferenceException(glyph.codepoint);
                }
            }
            return polylines;
        }

    public:
        GlyphListAccessor() = delete;
        GlyphListAccessor(const GlyphListAccessor& other) = delete;
        GlyphListAccessor(const GlyphListCache& glyphCache) noexcept :
            _glyphCache(glyphCache) {}
        GlyphListAccessor& operator=(const GlyphListAccessor& rhs) = delete;

        QVector<Polyline> getAllPolylinesOfGlyph(ushort codepoint) const {
            int index;
            const Glyph& glyph = _glyphCache.getGlyph(codepoint, &index); // can throw
            return getAllPolylinesOfGlyphImpl(glyph, index); // can throw
        }
};

} // namespace fontobene

#endif // FONTOBENE_GLYPHLISTACCESSOR_H


#ifndef FONTOBENE_GLYPHLISTACCESSOR_H
#define FONTOBENE_GLYPHLISTACCESSOR_H

#include <QtCore>
#include "./glyphlist.h"

namespace fontobene {

class GlyphListAccessor {
    private:
        const GlyphList& _list;
        const Glyph _nullGlyph;
        QHash<ushort, QVector<ushort>> _glyphReplacements;
        mutable QHash<ushort, int> _cachedIndices; // cached GlyphList indices of codeponts

        int findGlyphIndex(ushort codepoint) const noexcept {
            for (int i = 0; i < _list.count(); ++i) {
                if (_list.at(i).codepoint == codepoint) {
                    return i;
                }
            }
            return -1;
        }

        int lookupGlyphIndex(ushort codepoint) const noexcept {
            QVector<ushort> lookup = QVector<ushort>{codepoint} +
                                     _glyphReplacements.value(codepoint);
            foreach (ushort glyph, lookup) {
                int index = findGlyphIndex(glyph);
                if (index >= 0) { return index; }
            }
            return -1;
        }

        int getAndUpdateGlyphIndex(ushort codepoint) const noexcept {
            int index = _cachedIndices.value(codepoint, -2);
            if (index == -2) { // codepoint not found in cache, so add it now
                index = lookupGlyphIndex(codepoint);
                _cachedIndices.insert(codepoint, index);
            }
            if ((index >= 0) && (index < _list.length())) {
                Q_ASSERT((_list.at(index).codepoint == codepoint) ||
                    (_glyphReplacements.value(codepoint).contains(_list.at(index).codepoint)));
                return index;
            } else {
                return -1;
            }
        }

        QVector<Polyline> getAllPolylinesOfGlyphImpl(ushort codepoint, bool* ok) const noexcept {
            QVector<Polyline> polylines;
            int index = getAndUpdateGlyphIndex(codepoint);
            if (index >= 0) {
                const Glyph& glyph = _list.at(index);
                foreach (ushort ref, glyph.references) {
                    int refIndex = getAndUpdateGlyphIndex(ref);
                    if ((refIndex >= 0) && (refIndex < index)) {
                        polylines.append(getAllPolylinesOfGlyph(ref, ok));
                    } else {
                        // forward references are forbidden (to avoid endless loops)!
                        qWarning() << "fontobene::GlyphListAccessor: Ignore invalid "
                                      "reference in glyph" << QChar(codepoint);
                        if (ok) { *ok = false; }
                    }
                }
                polylines.append(glyph.polylines);
            } else if (ok) {
                *ok = false;
            }
            return polylines;
        }

    public:
        GlyphListAccessor() = delete;
        GlyphListAccessor(const GlyphListAccessor& other) = delete;
        GlyphListAccessor(const GlyphList& list) noexcept : _list(list) {}
        GlyphListAccessor& operator=(const GlyphListAccessor& rhs) = delete;

        void addReplacements(ushort codepoint, const QVector<ushort>& replacements) noexcept {
            _glyphReplacements[codepoint].append(replacements);
        }

        void addReplacements(const QVector<ushort>& replacements) noexcept {
            foreach (ushort codepoint, replacements) {
                _glyphReplacements[codepoint].append(replacements);
            }
        }

        void invalidateCache() noexcept {
            _cachedIndices.clear();
        }

        const Glyph& getGlyph(ushort codepoint) const noexcept {
            int index = getAndUpdateGlyphIndex(codepoint);
            return (index >= 0) ? _list.at(index) : _nullGlyph;
        }

        QVector<Polyline> getAllPolylinesOfGlyph(ushort codepoint, bool* ok = nullptr) const noexcept {
            if (ok) { *ok = true; }
            return getAllPolylinesOfGlyphImpl(codepoint, ok);
        }
};

} // namespace fontobene

#endif // FONTOBENE_GLYPHLISTACCESSOR_H


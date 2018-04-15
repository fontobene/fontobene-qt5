#ifndef FONTOBENE_GLYPHLISTCACHE_H
#define FONTOBENE_GLYPHLISTCACHE_H

#include <QtCore>
#include "./glyphlist.h"

namespace fontobene {

class GlyphListCache {
    private:
        const GlyphList& _list;
        ushort _replacementGlyph; // replacement for non-existent glyphs
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
                                     _glyphReplacements.value(codepoint) +
                                     QVector<ushort>{_replacementGlyph};
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
                    (_glyphReplacements.value(codepoint).contains(_list.at(index).codepoint)) ||
                    (_list.at(index).codepoint == _replacementGlyph));
                return index;
            } else {
                return -1;
            }
        }


    public:
        GlyphListCache() = delete;
        GlyphListCache(const GlyphListCache& other) = delete;
        GlyphListCache(const GlyphList& list) noexcept
            : _list(list), _replacementGlyph(0) {}
        GlyphListCache& operator=(const GlyphListCache& rhs) = delete;

        void setReplacementGlyph(ushort codepoint) noexcept {
            _replacementGlyph = codepoint;
        }

        void addReplacements(ushort codepoint, const QVector<ushort>& replacements) noexcept {
            _glyphReplacements[codepoint] += replacements;
        }

        void addReplacements(const QVector<ushort>& replacements) noexcept {
            foreach (ushort codepoint, replacements) {
                _glyphReplacements[codepoint] += replacements;
            }
        }

        void invalidateCache() noexcept {
            _cachedIndices.clear();
        }

        const Glyph& getGlyph(ushort codepoint, int* index = nullptr) const {
            int i = getAndUpdateGlyphIndex(codepoint);
            if (i >= 0) {
                if (index) { *index = i; }
                return _list.at(i);
            } else {
                throw GlyphNotFoundException(codepoint);
            }
        }
};

} // namespace fontobene

#endif // FONTOBENE_GLYPHLISTCACHE_H


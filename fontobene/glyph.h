#ifndef FONTOBENE_GLYPH_H
#define FONTOBENE_GLYPH_H

#include <QtCore>
#include "./helpers.h"

namespace fontobene {

struct Vertex {
    qreal x;
    qreal y;
    qreal bulge;

    qreal scaledX(qreal fullscale) const noexcept {
        return x * fullscale / 9;
    }

    qreal scaledY(qreal fullscale) const noexcept {
        return y * fullscale / 9;
    }

    qreal scaledBulge(qreal fullscale180deg) const noexcept {
        return bulge * fullscale180deg / 9;
    }

    static Vertex fromString(const QString& str) {
        Vertex v;
        QStringList numbers = str.split(',');
        if ((numbers.count() < 2) || (numbers.count() > 3)) {
            throw Exception(QString("Invalid vertex: \"%1\"").arg(str));
        }
        v.x = str2qreal(numbers.at(0));
        v.y = str2qreal(numbers.at(1));
        v.bulge = (numbers.count() > 2) ? str2qreal(numbers.at(2)) : 0;
        return v;
    }
};

struct Polyline : public QVector<Vertex> {
    static Polyline fromString(const QString& str) {
        Polyline p;
        foreach (const QString& vertex, str.split(';', QString::SkipEmptyParts)) {
            p.append(Vertex::fromString(vertex));
        }
        return p;
    }
};

struct Glyph {
    ushort codepoint = 0; // U+0000 (NULL) is considered as invalid glyph
    QVector<ushort> references;
    QVector<Polyline> polylines;

    bool isValid() const noexcept {
        return codepoint > 0;
    }

    QChar getChar() const noexcept {
        return QChar(codepoint);
    }

    static Glyph load(QTextStream& content) {
        Glyph glyph;
        enum class State {Header, Body, End} state = State::Header;
        while ((!content.atEnd()) && (state != State::End)) {
            QString line = content.readLine().trimmed();
            if (line.startsWith('#')) {
                continue;
            }
            switch (state) {
                case State::Header: {
                    if (!line.isEmpty()) {
                        QRegularExpression regex("\\[([0-9a-fA-F]{4,6})\\]");
                        glyph.codepoint = str2codepoint(regex.match(line).captured(1));
                        state = State::Body;
                    } else {
                        continue;
                    }
                    break;
                }

                case State::Body: {
                    if (line.startsWith('@')) {
                        glyph.references.append(str2codepoint(line.mid(1, -1)));
                    } else if (!line.isEmpty()) {
                        glyph.polylines.append(Polyline::fromString(line));
                    } else {
                        state = State::End;
                    }
                    break;
                }

                default: {
                    Q_ASSERT(false);
                    break;
                }
            }
        }
        return glyph;
    }
};

} // namespace fontobene

#endif // FONTOBENE_GLYPH_H


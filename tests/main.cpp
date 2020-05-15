#include <QtCore>
#include "../fontobene-qt5/fontobene.h"

using namespace fontobene;

QString format(ushort codepoint) noexcept {
    return QString("U+%1").arg(codepoint, 4, 16, QLatin1Char('0'));
}

int main(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    try {
        Font font(TESTFILEPATH);
        qDebug() << "ID:          " << font.header.id;
        qDebug() << "Name:        " << font.header.name;
        qDebug() << "Version:     " << font.header.version;
        qDebug() << "Authors:     " << font.header.authors;
        qDebug() << "Licenses:    " << font.header.licenses;
        qDebug() << "User Data:   " << font.header.userData;

        foreach (const Glyph& glyph, font.glyphs) {
            QString str = "\nCodepoint " + format(glyph.codepoint) + ": " + glyph.getChar();
            foreach (ushort codepoint, glyph.references) {
                str += "\n  Reference " + format(codepoint) + " (" + QChar(codepoint) + ")";
            }
            foreach (const Polyline& polyline, glyph.polylines) {
                str += "\n  Polyline ";
                foreach (const Vertex& vertex, polyline) {
                    str += QString("%1,%2,%3; ").arg(vertex.x).arg(vertex.y).arg(vertex.bulge);
                }
            }
            qDebug() << qPrintable(str); // qPrintable() to avoid escaping and quoting
        }

        qDebug() << "\nTotal glyph count: " << font.glyphs.count();
    } catch (const std::exception& e) {
        qCritical() << "Could not load file" << TESTFILEPATH;
        qCritical() << e.what();
    }

    return 0;
}

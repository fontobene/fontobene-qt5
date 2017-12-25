#ifndef FONTOBENE_HELPERS_H
#define FONTOBENE_HELPERS_H

#include <QtCore>
#include "./exception.h"

namespace fontobene {

template <typename T>
T str2qreal(const QString& str, bool* ok) noexcept = delete;

template <>
float str2qreal<float>(const QString& str, bool* ok) noexcept {
    return str.toFloat(ok);
}

template <>
double str2qreal<double>(const QString& str, bool* ok) noexcept {
    return str.toDouble(ok);
}

qreal str2qreal(const QString& str) {
    bool ok = false;
    qreal value = str2qreal<qreal>(str, &ok);
    if (!ok) {
        throw Exception(QString("Invalid number: \"%1\"").arg(str));
    }
    return value;
}

ushort str2codepoint(const QString& str) {
    bool ok = false;
    ushort codepoint = str.toUShort(&ok, 16);
    if (!ok) {
        throw Exception(QString("Invalid codepoint: \"%1\"").arg(str));
    }
    return codepoint;
}

} // namespace fontobene

#endif // FONTOBENE_HELPERS_H


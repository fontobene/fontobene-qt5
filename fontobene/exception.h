#ifndef FONTOBENE_EXCEPTION_H
#define FONTOBENE_EXCEPTION_H

#include <QtCore>

namespace fontobene {

class Exception : public std::runtime_error {
    public:
        Exception(const QString& msg) : std::runtime_error(msg.toStdString()) {}
        QString msg() const noexcept {return QString(what());}
};

} // namespace fontobene

#endif // FONTOBENE_EXCEPTION_H


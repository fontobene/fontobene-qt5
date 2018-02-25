#ifndef FONTOBENE_EXCEPTION_H
#define FONTOBENE_EXCEPTION_H

#include <QtCore>

namespace fontobene {

class Exception : public QException {
        QString _msg;
    public:
        Exception(const QString& msg) : QException(), _msg(msg) {}
        Exception(const Exception& other) : QException(other), _msg(other._msg) {}
        const QString& msg() const noexcept { return _msg; }
        void raise() const override { throw *this; }
        Exception* clone() const override { return new Exception(*this); }
};

} // namespace fontobene

#endif // FONTOBENE_EXCEPTION_H


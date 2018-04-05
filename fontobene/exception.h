#ifndef FONTOBENE_EXCEPTION_H
#define FONTOBENE_EXCEPTION_H

#include <QtCore>

namespace fontobene {

class Exception : public QException {
        QString _msg;
        ushort _codepoint;
    public:
        explicit Exception(const QString& msg, ushort codepoint = 0) :
            QException(), _msg(msg), _codepoint(codepoint) {}
        Exception(const Exception& other) :
            QException(other), _msg(other._msg), _codepoint(other._codepoint) {}
        const QString& msg() const noexcept { return _msg; }
        ushort codepoint() const noexcept { return _codepoint; }
        virtual void raise() const override { throw *this; }
        virtual Exception* clone() const override { return new Exception(*this); }
        static QString cp2str(ushort codepoint) noexcept
            { return QString("U+%1").arg(codepoint, 4, 16, QChar('0')); }
};

class GlyphNotFoundException : public Exception {

    public:
        explicit GlyphNotFoundException(ushort codepoint) :
            Exception(QString("Glyph %1 not found.").arg(cp2str(codepoint)), codepoint) {}
        GlyphNotFoundException(const GlyphNotFoundException& other) :
            Exception(other) {}
        void raise() const override { throw *this; }
        Exception* clone() const override { return new GlyphNotFoundException(*this); }
};

class ForwardReferenceException : public Exception {
        ushort _codepoint;
    public:
        explicit ForwardReferenceException(ushort codepoint) :
            Exception(QString("Forward reference detected in %1.").arg(cp2str(codepoint)),
                      codepoint) {}
        ForwardReferenceException(const ForwardReferenceException& other) :
            Exception(other) {}
        void raise() const override { throw *this; }
        Exception* clone() const override { return new ForwardReferenceException(*this); }
};

} // namespace fontobene

#endif // FONTOBENE_EXCEPTION_H


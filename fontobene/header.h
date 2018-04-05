#ifndef FONTOBENE_HEADER_H
#define FONTOBENE_HEADER_H

#include <QtCore>
#include "./helpers.h"

namespace fontobene {

struct Header {
    QString id;
    QString name;
    QString description;
    QString version;
    QStringList authors;
    QStringList licenses;
    QMap<QString, QString> userData;

    void clear() noexcept {
        id.clear();
        name.clear();
        description.clear();
        version.clear();
        authors.clear();
        licenses.clear();
        userData.clear();
    }

    void load(QTextStream& content) {
        clear();
        enum class Section {None, Format, Font, User, End} section = Section::None;
        QString format, formatVersion;
        while (!content.atEnd() && (section != Section::End)) {
            QString line = content.readLine().trimmed();

            if (line.isEmpty() || line.startsWith('#')) {
                continue;
            }

            QString key = line.contains('=') ? line.section('=', 0, 0).trimmed() : QString();
            QString value = line.contains('=') ? line.section('=', 1, -1).trimmed() : QString();

            switch (section) {
                case Section::None: {
                    if (line == QStringLiteral("[format]")) {
                        section = Section::Format;
                    } else {
                        throw Exception(QString("Unexpected content: \"%1\"").arg(line));
                    }
                    break;
                }

                case Section::Format: {
                    if (line == QStringLiteral("[font]")) {
                        if (format != QStringLiteral("FontoBene")) {
                            throw Exception(QString("Unknown format: \"%1\"").arg(format));
                        }
                        if (formatVersion != QStringLiteral("1.0")) {
                            throw Exception(QString("Unsupported format version: \"%1\"")
                                            .arg(formatVersion));
                        }
                        section = Section::Font;
                    } else if (key == QStringLiteral("format")) {
                        format = value;
                    } else if (key == QStringLiteral("format_version")) {
                        formatVersion = value;
                    } else {
                        throw Exception(QString("Unexpected content: \"%1\"").arg(line));
                    }
                    break;
                }

                case Section::Font: {
                    if (line == QStringLiteral("---")) {
                        section = Section::End;
                    } else if (line == QStringLiteral("[user]")) {
                        section = Section::User;
                    } else if (key == QStringLiteral("id")) {
                        id = value;
                    } else if (key == QStringLiteral("name")) {
                        name = value;
                    } else if (key == QStringLiteral("description")) {
                        description = value;
                    } else if (key == QStringLiteral("version")) {
                        version = value;
                    } else if (key == QStringLiteral("author")) {
                        authors.append(value);
                    } else if (key == QStringLiteral("license")) {
                        licenses.append(value);
                    } else {
                        throw Exception(QString("Unexpected content: \"%1\"").arg(line));
                    }
                    break;
                }

                case Section::User: {
                    if (line == QStringLiteral("---")) {
                        section = Section::End;
                    } else if (!key.isEmpty()) {
                        userData.insert(key, value);
                    } else {
                        throw Exception(QString("Unexpected content: \"%1\"").arg(line));
                    }
                    break;
                }

                default: {
                    Q_ASSERT(false);
                    break;
                }
            }
        }
    }
};

} // namespace fontobene

#endif // FONTOBENE_HEADER_H


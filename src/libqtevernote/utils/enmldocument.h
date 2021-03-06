/*
 * Copyright: 2013 Canonical, Ltd
 *
 * This file is part of reminders
 *
 * reminders is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * reminders is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Michael Zanetti <michael.zanetti@canonical.com>
 */

#ifndef ENMLDOCUMENT_H
#define ENMLDOCUMENT_H

#include <QString>

class EnmlDocument
{
public:
    EnmlDocument(const QString &enml = QString());

    QString enml() const;
    void setEnml(const QString &enml);

    // noteGuid is required to convert en-media tags to urls for image provider
    QString toHtml(const QString &noteGuid) const;
    QString toRichText(const QString &noteGuid) const;
    QString toPlaintext() const;

    void setRichText(const QString &richText);

    // Will insert the file described by hash at position in the plaintext string
    void attachFile(int position, const QString &hash, const QString &type);

    // Convenience functions to insert some text without having a complete Editor attached
    void insertText(int position, const QString &text);
    void insertLink(int position, const QString &url);

    void markTodo(const QString &todoId, bool checked);

    int renderWidth() const;
    void setRenderWidth(int renderWidth);

private:
    enum Type {
        TypeRichText,
        TypeHtml
    };

    QString convert(const QString &noteGuid, Type type) const;

    qreal gu(qreal px) const;

    QString composeMediaTypeUrl(const QString &mediaType, const QString &noteGuid, const QString &hash) const;

private:
    QString m_enml;
    int m_renderWidth;

    static QStringList s_commonTags;
    static QStringList s_argumentBlackListTags;
};

#endif // ENMLDOCUMENT_H

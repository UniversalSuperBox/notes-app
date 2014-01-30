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

#include "resource.h"

#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include <QCryptographicHash>

Resource::Resource(const QByteArray &data, const QString &hash, const QString &fileName, const QString &type, QObject *parent):
    m_hash(hash),
    m_fileName(fileName),
    m_type(type)
{

    m_filePath = QStandardPaths::standardLocations(QStandardPaths::CacheLocation).first() + "/" + hash + "." + type.split('/').last();

    QFile file(m_filePath);
    if (!file.exists()) {

        if (!file.open(QFile::WriteOnly)) {
            qWarning() << "error writing file" << m_filePath;
            return;
        }
        file.write(data);
        file.close();
    }
}

Resource::Resource(const QString &path, QObject *parent):
    m_filePath(path)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        qWarning() << "Cannot open file for reading...";
        return;
    }

    QByteArray fileContent = file.readAll();
    m_hash = QCryptographicHash::hash(fileContent, QCryptographicHash::Md5).toHex();

    m_fileName = path.split('/').last();
    if (m_fileName.endsWith(".png")) {
        m_type = "image/png";
    } else if (m_fileName.endsWith(".jpg") || m_fileName.endsWith(".jpeg")) {
        m_type = "image/jpeg";
    } else {
        qWarning() << "cannot determine mime type of file" << m_fileName;
    }
}

QString Resource::hash() const
{
    return m_hash;
}

QString Resource::type() const
{
    return m_type;
}

QString Resource::fileName() const
{
    return m_fileName;
}

QByteArray Resource::data() const
{
    QFile file(m_filePath);
    if (file.open(QFile::ReadOnly)) {
        return file.readAll();
    }
    return QByteArray();
}

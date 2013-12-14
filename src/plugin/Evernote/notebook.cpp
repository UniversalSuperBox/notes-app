/*
 * Copyright: 2013 Canonical, Ltd
 *
 * This file is part of reminders-app
 *
 * reminders-app is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * reminders-app is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Michael Zanetti <michael.zanetti@canonical.com>
 */

#include "notebook.h"
#include "notesstore.h"
#include "note.h"

#include <QDebug>

Notebook::Notebook(QString guid, QObject *parent) :
    QObject(parent),
    m_guid(guid),
    m_noteCount(0),
    m_published(false)
{
    qDebug() << "notebook created. notes in store" << NotesStore::instance()->notes().count();
    foreach (Note *note, NotesStore::instance()->notes()) {
        if (note->notebookGuid() == m_guid) {
            m_noteCount++;
        }
    }
    connect(NotesStore::instance(), &NotesStore::noteAdded, this, &Notebook::noteAdded);
    connect(NotesStore::instance(), &NotesStore::noteRemoved, this, &Notebook::noteRemoved);
}

QString Notebook::guid() const
{
    return m_guid;
}

QString Notebook::name() const
{
    return m_name;
}

void Notebook::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

int Notebook::noteCount() const
{
    return m_noteCount;
}

bool Notebook::published() const
{
    return m_published;
}

void Notebook::setPublished(bool published)
{
    if (m_published != published) {
        m_published = published;
        emit publishedChanged();
    }
}

void Notebook::noteAdded(const QString &noteGuid, const QString &notebookGuid)
{
    if (notebookGuid == m_guid) {
        m_noteCount++;
        emit noteCountChanged();
    }
}

void Notebook::noteRemoved(const QString &noteGuid, const QString &notebookGuid)
{
    if (notebookGuid == m_guid) {
        m_noteCount--;
        emit noteCountChanged();
    }
}

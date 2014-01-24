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

#ifndef NOTE_H
#define NOTE_H

#include "utils/enmldocument.h"
#include "resource.h"

#include <QObject>
#include <QDateTime>
#include <QStringList>
#include <QImage>

class Note : public QObject
{
    Q_OBJECT

    // Don't forget to update clone() if you add properties!
    Q_PROPERTY(QString guid READ guid CONSTANT)
    Q_PROPERTY(QString notebookGuid READ notebookGuid WRITE setNotebookGuid NOTIFY notebookGuidChanged)
    Q_PROPERTY(QDateTime created READ created CONSTANT)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString htmlContent READ htmlContent NOTIFY contentChanged)
    Q_PROPERTY(QString richTextContent READ richTextContent WRITE setRichTextContent NOTIFY contentChanged)
    Q_PROPERTY(QString enmlContent READ enmlContent WRITE setEnmlContent NOTIFY contentChanged)
    Q_PROPERTY(QString plaintextContent READ plaintextContent NOTIFY contentChanged)
    Q_PROPERTY(QStringList resourceUrls READ resourceUrls NOTIFY contentChanged)
    Q_PROPERTY(bool reminder READ reminder WRITE setReminder NOTIFY reminderChanged)
    Q_PROPERTY(QDateTime reminderTime READ reminderTime WRITE setReminderTime NOTIFY reminderTimeChanged)
    Q_PROPERTY(bool reminderDone READ reminderDone WRITE setReminderDone NOTIFY reminderDoneChanged)
    Q_PROPERTY(QDateTime reminderDoneTime READ reminderDoneTime WRITE setReminderDoneTime NOTIFY reminderDoneChanged)
    Q_PROPERTY(bool isSearchResult READ isSearchResult NOTIFY isSearchResultChanged)
    // Don't forget to update clone() if you add properties!

public:
    explicit Note(const QString &guid, const QDateTime &created, QObject *parent = 0);
    ~Note();

    QString guid() const;

    QString notebookGuid() const;
    void setNotebookGuid(const QString &notebookGuid);

    QDateTime created() const;

    QString title() const;
    void setTitle(const QString &title);

    QString enmlContent() const;
    void setEnmlContent(const QString &enmlContent);

    QString htmlContent() const;

    QString richTextContent() const;
    void setRichTextContent(const QString &richTextContent);

    QString plaintextContent() const;

    // This is the QML representation as we don't want to deal with timestamps there.
    // setting it to false will reset the reminderOrder to 0, setting it to true will
    // create a new timestamp for it.
    bool reminder() const;
    void setReminder(bool reminder);

    qint64 reminderOrder() const;
    void setReminderOrder(qint64 reminderOrder);

    QDateTime reminderTime() const;
    void setReminderTime(const QDateTime &reminderTime);

    // This is the QML representation as we don't want to deal with timestamps there.
    // setting it to false will reset reminderDoneTime to 0, setting it to true will
    // create a new timestamp for it.
    bool reminderDone() const;
    void setReminderDone(bool reminderDone);

    QDateTime reminderDoneTime() const;
    void setReminderDoneTime(const QDateTime &reminderDoneTime);

    bool isSearchResult() const;
    void setIsSearchResult(bool isSearchResult);

    QStringList resourceUrls() const;
    Resource* resource(const QString &hash);
    QList<Resource*> resources() const;
    Resource *addResource(const QByteArray &data, const QString &hash, const QString &fileName, const QString &type);
    Resource *addResource(const QString &fileName);

    Q_INVOKABLE void markTodo(const QString &todoId, bool checked);
    Q_INVOKABLE void attachFile(int position, const QUrl &fileName);

    Note* clone();

public slots:
    void save();
    void remove();

signals:
    void titleChanged();
    void notebookGuidChanged();
    void contentChanged();
    void reminderChanged();
    void reminderTimeChanged();
    void reminderDoneChanged();
    void isSearchResultChanged();

private:
    QString m_guid;
    QString m_notebookGuid;
    QDateTime m_created;
    QString m_title;
    EnmlDocument m_content;
    qint64 m_reminderOrder;
    QDateTime m_reminderTime;
    QDateTime m_reminderDoneTime;
    bool m_isSearchResult;
    QHash<QString, Resource*> m_resources;
};

#endif // NOTE_H

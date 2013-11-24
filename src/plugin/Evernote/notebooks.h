#ifndef NOTEBOOKS_H
#define NOTEBOOKS_H

#include "notesstore.h"

#include <QAbstractListModel>

class Notebooks : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        RoleGuid,
        RoleName
    };
    explicit Notebooks(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void refresh();

private slots:
    void notebookAdded(const QString &guid);

private:
    QList<QString> m_list;
};

#endif // NOTEBOOKS_H

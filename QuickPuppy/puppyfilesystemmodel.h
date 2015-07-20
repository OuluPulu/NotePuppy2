#ifndef PUPPYFILESYSTEMMODEL_H
#define PUPPYFILESYSTEMMODEL_H

#include <QFileSystemModel>

#include "node.h"


// A similar result could be achieved by subclassing the
// QFileSystemModel.
// This is not used because it adds the parent directories
// to the base of the tree, which is something I totally
// don't want. And as you can see, it's not *that* hard
// to add things in.....
// TODO add filesystemwatcher feature.
class PuppyFileSystemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PuppyFileSystemModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QString getFilePath(const QModelIndex index) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    enum Roles {
        FileIconRole = Qt::DecorationRole,
        FilePathRole = Qt::UserRole + 1,
        FileNameRole = Qt::UserRole + 2,
        FilePermissions = Qt::UserRole + 3,
        FileSize = Qt::UserRole + 4,
        FileUpdateTime = Qt::UserRole + 5,
        FullFilePath = Qt::UserRole + 6
    };

public slots:
    void setRootPath(QString rootPath);

protected:
    QModelIndex indexForNode(Node *node) const;
    Node* nodeForIndex(const QModelIndex &index) const;
    int rowForNode(Node *node) const;

private:
    QString m_rootPath;
    QHash<int, QByteArray> omph;

    void createTree();
    void expandNode(Node *n);

    Node *m_rootNode;
};

#endif // PUPPYFILESYSTEMMODEL_H

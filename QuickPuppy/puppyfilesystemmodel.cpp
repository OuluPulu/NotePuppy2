#include "puppyfilesystemmodel.h"

#include <QDateTime>
#include <QDebug>
#include <QHash>

PuppyFileSystemModel::PuppyFileSystemModel(QObject *parent) : QAbstractItemModel(parent)
  , m_rootNode(0)
{
}


QHash<int, QByteArray> PuppyFileSystemModel::roleNames() const
{
    static QHash<int, QByteArray> roles;

    if (roles.size() == 0)
    {
        roles.insert(Qt::DecorationRole, "icon");
        roles.insert(Qt::UserRole + 1, "filepath");
        roles.insert(Qt::UserRole + 2, "filename");
        roles.insert(Qt::UserRole + 3, "permissions");
        roles.insert(Qt::UserRole + 4, "filesize");
        roles.insert(Qt::UserRole + 5, "updateTime");
        roles.insert(Qt::UserRole + 6, "fullFilePath");
    }
    return roles;
}

QString PuppyFileSystemModel::getFilePath(const QModelIndex index) const
{
    return data(index, 262).toString();
}


void PuppyFileSystemModel::setRootPath(QString rootPath)
{
    m_rootPath = rootPath;
    beginResetModel();
    createTree();
    endResetModel();
}

QModelIndex PuppyFileSystemModel::index(int row, int column, const QModelIndex &parent) const
{
    if(hasIndex(row, column, parent)) {
        Node *parentNode = nodeForIndex(parent);
        Node *childNode = parentNode->children.at(row);
        return createIndex(row, column, childNode);
    }
    return QModelIndex();
}

QModelIndex PuppyFileSystemModel::parent(const QModelIndex &child) const
{
    Node *childNode = nodeForIndex(child);
    Node *parentNode = childNode->parent;

    if(parentNode == m_rootNode) {
        return QModelIndex();
    }
    int row = rowForNode(parentNode);
    int column = 0;
    return createIndex(row, column, parentNode);
}

int PuppyFileSystemModel::rowCount(const QModelIndex &parent) const
{
    Node *parentNode = nodeForIndex(parent);
    return parentNode->children.count();
}

int PuppyFileSystemModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant PuppyFileSystemModel::data(const QModelIndex &index, int role) const
{
    QVariant v;

    switch (role)
    {
    case FileIconRole:
        break;
    case FilePathRole:
        v = nodeForIndex(index)->info.absolutePath();
        break;
    case FileNameRole:
        v = nodeForIndex(index)->info.fileName();
        break;
    case FilePermissions:
//        v = nodeForIndex(index)->info.permissions();
        break;
    case FileSize:
        v = nodeForIndex(index)->info.size();
        break;
    case FileUpdateTime:
        v = nodeForIndex(index)->info.lastModified();
        break;
    case FullFilePath:
        v = nodeForIndex(index)->info.canonicalFilePath();
        break;
    }

//    if (role == PuppyFileSystemModel::FileSize)
//    {
//        QFileInfo info = fileInfo(index);
//        if (info.isDir())
//        {
//            QDir d(info.absolutePath());
//            v = d.count();
//        }
//        else
//        {
//            v = info.size();
//        }
//    }
//    else if (role == PuppyFileSystemModel::FileUpdateTime)
//    {
//        QFileInfo info = fileInfo(index);
//        v = info.lastModified().toString();
//    }
//    else if (role == PuppyFileSystemModel::FullFilePath)
//    {
//        QFileInfo info = fileInfo(index);
//        v =  info.absoluteFilePath();
//    }
//    else
//    {
//        v = QFileSystemModel::data(index, role);
//    }
    return v;
}

QModelIndex PuppyFileSystemModel::indexForNode(Node *node) const
{
    if(node == m_rootNode) {
        return QModelIndex();
    }
    int row = rowForNode(node);
    int column = 0;
    return createIndex(row, column, node);
}

Node* PuppyFileSystemModel::nodeForIndex(const QModelIndex &index) const
{
    if(index.isValid()) {
        return static_cast<Node*>(index.internalPointer());
    }
    return m_rootNode;
}

int PuppyFileSystemModel::rowForNode(Node *node) const
{
    return node->parent->children.indexOf(node);
}



void PuppyFileSystemModel::createTree()
{
    // Take the root directory
    QFileInfo rootInfo(m_rootPath);

    if (rootInfo.exists())
    {
        if (!m_rootNode || (rootInfo.path() != m_rootNode->info.path()))
        {
            if (m_rootNode)
                delete (m_rootNode);
            Node *nroot = new Node(m_rootPath, rootInfo);
            m_rootNode = nroot;
            expandNode(nroot);
        }
    }
    else
        delete (m_rootNode);
}

void PuppyFileSystemModel::expandNode(Node *n)
{
    if (n->info.isDir())
    {
        QDir dir(n->info.absoluteFilePath());
        QFileInfoList files = dir.entryInfoList();//QDir::NoDotAndDotDot, QDir::Name);

        for (int i = 0; i < files.length(); i++)
        {
            QFileInfo info = files.at(i);
            // The QDir::NoDotAndDotDot call didn't work. TODO investogate.
            if (info.fileName() != "." && info.fileName() != "..")
            {
                Node *child = new Node(info.fileName(), info, n);
                if (info.isDir())
                {
                    expandNode(child);
                }
            }
        }
    }
}

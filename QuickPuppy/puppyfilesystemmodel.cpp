#include "puppyfilesystemmodel.h"

#include <QDateTime>
#include <QDebug>

PuppyFileSystemModel::PuppyFileSystemModel(QObject *parent) : QFileSystemModel(parent)
{
    omph = QFileSystemModel::roleNames();
    omph.insert(PuppyFileSystemModel::FileSize, "fileSize");
    omph.insert(PuppyFileSystemModel::FileUpdateTime, "fileUpdateTime");
}


QHash<int, QByteArray> PuppyFileSystemModel::roleNames() const
{
    return omph;
}

QString PuppyFileSystemModel::getFilePath(const QModelIndex index) const
{
    return data(index, 262).toString();
}


QVariant PuppyFileSystemModel::data(const QModelIndex &index, int role) const
{
    QVariant v;

    if (role == PuppyFileSystemModel::FileSize)
    {
        QFileInfo info = fileInfo(index);
        if (info.isDir())
        {
            QDir d(info.absolutePath());
            v = d.count();
        }
        else
        {
            v = info.size();
        }
    }
    else if (role == PuppyFileSystemModel::FileUpdateTime)
    {
        QFileInfo info = fileInfo(index);
        v = info.lastModified().toString();
    }
    else if (role == PuppyFileSystemModel::FullFilePath)
    {
        QFileInfo info = fileInfo(index);
        v =  info.absoluteFilePath();
    }
    else
    {
        v = QFileSystemModel::data(index, role);
    }
    return v;
}

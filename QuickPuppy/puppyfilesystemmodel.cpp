#include "puppyfilesystemmodel.h"

#include <QDateTime>

PuppyFileSystemModel::PuppyFileSystemModel(QObject *parent) : QFileSystemModel(parent)
{
    omph = QFileSystemModel::roleNames();
    omph.insert(PuppyFileSystemModel::fileSize, "fileSize");
    omph.insert(PuppyFileSystemModel::fileUpdateTime, "fileUpdateTime");
}


QHash<int, QByteArray> PuppyFileSystemModel::roleNames() const
{
    return omph;
}

QVariant PuppyFileSystemModel::data(const QModelIndex &index, int role) const
{
    QVariant v;

    if (role == PuppyFileSystemModel::fileSize)
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
    else if (role == PuppyFileSystemModel::fileUpdateTime)
    {
        QFileInfo info = fileInfo(index);
        v = info.lastModified().toString();
    }
    else
    {
        v = QFileSystemModel::data(index, role);
    }





    return v;
}

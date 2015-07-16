#ifndef PUPPYFILESYSTEMMODEL_H
#define PUPPYFILESYSTEMMODEL_H

#include <QFileSystemModel>

// QFileSystemModel adds the path to the start of the file tree.
// It makes the FileTree hideous.
// But it's easier to deal with this hideous feature FOR NOW.
// TODO Remove the QFileSystemWatcher's ugly full-path nonsense
// maybe port the original NotePuppy file tree thing over.
class PuppyFileSystemModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit PuppyFileSystemModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    Q_INVOKABLE QString getFilePath(const QModelIndex index) const;

    enum extraRoles {
        FileSize = Qt::UserRole + 4,
        FileUpdateTime = Qt::UserRole + 5,
        FullFilePath = Qt::UserRole + 6
    };

private:

    QHash<int, QByteArray> omph;
};

#endif // PUPPYFILESYSTEMMODEL_H

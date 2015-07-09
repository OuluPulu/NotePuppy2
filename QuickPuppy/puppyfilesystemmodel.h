#ifndef PUPPYFILESYSTEMMODEL_H
#define PUPPYFILESYSTEMMODEL_H

#include <QFileSystemModel>

class PuppyFileSystemModel : public QFileSystemModel
{
public:
    explicit PuppyFileSystemModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;


private:

    enum extraRoles {
        fileSize = Qt::UserRole + 4,
        fileUpdateTime = Qt::UserRole + 5
    };
    QHash<int, QByteArray> omph;
};

#endif // PUPPYFILESYSTEMMODEL_H

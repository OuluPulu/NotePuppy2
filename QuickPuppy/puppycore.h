#ifndef PUPPYCORE_H
#define PUPPYCORE_H

#include "puppyfilesystemmodel.h"

#include <QObject>
#include <QVariant>

class QSettings;

class PuppyCore : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString rootDir READ rootDir WRITE setRootDir NOTIFY rootDirChanged)
public:
    explicit PuppyCore(QObject *parent = 0);

    QString rootDir();
    void setRootDir(QString rootDir);

    PuppyFileSystemModel *fileSystemModel() { return m_fileSystemModel; }

    Q_INVOKABLE QVariant getSetting(QString setting, QString defaultValue = "");
    Q_INVOKABLE bool checkFile(QString filename);
    Q_INVOKABLE QString evaluateFile(QString directory, QString file);

    Q_INVOKABLE QString directorizeFile(QString filename);

signals:
    void rootDirChanged();

public slots:

private:
    QString m_rootDir;
    QSettings *m_settings;
    PuppyFileSystemModel *m_fileSystemModel;
};

#endif // PUPPYCORE_H

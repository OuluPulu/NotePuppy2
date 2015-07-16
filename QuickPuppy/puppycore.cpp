#include "puppycore.h"

#include <QDebug>

#include <QDir>
#include <QSettings>

PuppyCore::PuppyCore(QObject *parent) : QObject(parent)
{
    m_settings = new QSettings("loralora.co.uk", "notepuppy2", this);
    QString defaultDir = QDir::homePath();
    defaultDir.append("/NotePuppy/");
    m_rootDir = m_settings->value("rootDir", defaultDir).toString();
    // check the directory exists, and if not then make it so
    // TODO
    m_fileSystemModel = new PuppyFileSystemModel(this);
    m_fileSystemModel->setRootPath(m_rootDir);
}

QVariant PuppyCore::getSetting(QString setting, QString defaultValue)
{
    return m_settings->value(setting, defaultValue);
}

void PuppyCore::setRootDir(QString rootDir)
{
    // maybe this should check the value is sane.
    m_settings->setValue("rootDir", rootDir);
    m_rootDir = rootDir;
    m_fileSystemModel->setRootPath(m_rootDir);
    emit rootDirChanged();
}

QString PuppyCore::directorizeFile(QString filename)
{
    QFileInfo finfo(filename);
    return finfo.absolutePath();
}

QString PuppyCore::evaluateFile(QString directory, QString file)
{
    QFileInfo dirInfo(directory);
    QString fileName = "";
    if (dirInfo.exists())
    {
        if (dirInfo.isFile())
        {
            directory = dirInfo.absolutePath();
        }
    }
    else
    {
        QDir d(directory);
        d.mkdir(directory);
    }

    fileName += directory + QDir::separator();
    fileName += file;

    QFileInfo fileInfo(fileName);

    while (fileInfo.exists() && fileInfo.isDir())
    {
        fileName += QDir::separator();
        fileName += file;
        fileInfo.setFile(fileName);
    }
    if (!fileInfo.exists())
    {
        QFile f(fileName);
        f.open(QIODevice::ReadWrite);
    }
    return fileName;
}

QString PuppyCore::rootDir()
{
    return m_rootDir;
}

bool PuppyCore::checkFile(QString filename)
{
    bool cool = true;
    QFileInfo info(filename);
    if (!info.exists())
    {
        QFile f(filename);
        if (!f.open(QIODevice::WriteOnly))
        {
            // TODO Could add some better error message handling here.
            cool = !cool;
        }
        else f.close();
    }
    else
    {
        if (info.isDir())
            cool = false;
    }
    return cool;
}

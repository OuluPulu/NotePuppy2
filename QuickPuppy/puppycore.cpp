#include "puppycore.h"

#include <QDir>
#include <QSettings>

PuppyCore::PuppyCore(QObject *parent) : QObject(parent)
{
    m_settings = new QSettings("loralora.co.uk", "notepuppy2", this);
    QDir d;
    QString defaultDir = QDir::homePath();
    defaultDir.append("/NotePuppy/");
    m_rootDir = m_settings->value("rootDir", defaultDir).toString();
    m_fileSystemModel = new PuppyFileSystemModel(this);
    m_fileSystemModel->setRootPath(m_rootDir);
}

QVariant PuppyCore::getSetting(QString setting, QString defaultValue)
{
    return m_settings->value(setting, defaultValue);
}

void PuppyCore::setRootDir(QString rootDir)
{
    m_rootDir = rootDir;
    m_fileSystemModel->setRootPath(m_rootDir);
    emit rootDirChanged();
}

QString PuppyCore::rootDir()
{
    return m_rootDir;
}

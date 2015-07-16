#include "puppyfile.h"

#include <QDebug>

#include <QFile>
#include <QFileInfo>

PuppyFile::PuppyFile(QObject *parent) : QObject(parent)
  , m_file(0)
{

}

PuppyFile::~PuppyFile()
{

}

void PuppyFile::setFile(QString filename)
{
    if (m_file)
    {
        if (m_file->isOpen()) m_file->close();
        m_file->deleteLater();
        m_file = 0;
    }
    m_file = new QFile(filename);
    if (m_file->open(QIODevice::ReadOnly))
    {
        QString contents = m_file->readAll();
        emit fileContentsChanged(contents);
        m_file->close();
    }
    else
    {
        QString error = "Unable to open " + filename + " for reading.";
        emit fileError(error);
    }
}

void PuppyFile::setContents(QString contents)
{
    if (m_file->open(QIODevice::WriteOnly))
    {
        QByteArray data = contents.toUtf8();
        m_file->write(data);
        m_file->flush();
        m_file->close();
    }
    else
    {
        QFileInfo info(*m_file);
        QString error("Unable to open %1 for writing.");
        error.arg(info.fileName());
        emit fileError(error);
    }
}


#ifndef PUPPYFILE_H
#define PUPPYFILE_H

#include <QObject>

class QFile;

class PuppyFile : public QObject
{
    Q_OBJECT
public:
    explicit PuppyFile(QObject *parent = 0);
    ~PuppyFile();

signals:
    void fileContentsChanged(QString contents);
    void fileError(QString message);

public slots:
    void setFile(QString filename);
    void setContents(QString contents);

private:
    QFile *m_file;
};

#endif // PUPPYFILE_H

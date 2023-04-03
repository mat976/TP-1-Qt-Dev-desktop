#include "indexer.h"
#include <QDirIterator>
#include <QRegularExpression>

indexer::indexer()
{

}

void indexer::setStart_path(const QString start_path)
{
    m_start_path = start_path;
}

void indexer::run(){
    QDirIterator it(m_start_path, QDirIterator::Subdirectories);
    QRegularExpression re("^(.*)/([^/]+)\\.([^.]+)$");

    while (it.hasNext()) {
        QString nextPath = it.next();
        QRegularExpressionMatch match = re.match(nextPath);
        QFileInfo fileInfo(nextPath);

        if (match.hasMatch()) {
            QString path = match.captured(1);
            QString fileName = match.captured(2);
            QString extension = match.captured(3);
            qint64 size = fileInfo.size();
            QString lastModified = fileInfo.lastModified().toString();

            emit newPath(path, fileName, extension, size, lastModified);
        }

        QThread::usleep(100);
    }
}

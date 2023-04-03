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
        QFile file(nextPath);

        if (match.hasMatch()) {
            QString path = match.captured(1);
            QString fileName = match.captured(2);
            QString extension = match.captured(3);

            if (file.open(QIODevice::ReadOnly)) {
                // Récupère la taille du fichier en octets
                qint64 size = file.size();

                emit newPath(path, fileName, extension, size);

                // Ferme le fichier
                file.close();
            }


        }

        QThread::usleep(100);
    }
}

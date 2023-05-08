#include "indexer.h"
#include <QDirIterator>
#include <QRegularExpression>
#include <bdd.h>

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

    BDD bdd;

    QList<QVariantList> buffer;
    const int bufferSize = 400;

    while (it.hasNext()) {
        QString nextPath = it.next();
        QRegularExpressionMatch match = re.match(nextPath);
        QFile file(nextPath);

        if (match.hasMatch()) {
            QString path = match.captured(1);
            QString fileName = match.captured(2);
            QString extension = match.captured(3);

            // Vérifie si l'extension du fichier est différente de "dll"
            if (extension.toLower() != "dll") {
                if (file.open(QIODevice::ReadOnly)) {
                    // Récupère la taille du fichier en octets
                    qint64 size = file.size();
                    QString lastModified = fileInfo.lastModified().toString();
                    QString creationDate = fileInfo.birthTime().toString();

                    // Ajoute les informations du fichier au buffer
                    QVariantList rowData;
                    rowData.append(path);
                    rowData.append(fileName);
                    rowData.append(extension);
                    rowData.append(size);
                    
                    /* ajouter ces lignes
                     * rowData.append(lastModified);
                     * rowData.append(creationDate);
                    */  
                   
                    buffer.append(rowData);

                    // Ferme le fichier
                    file.close();
                }
            }
        }

        // Vérifie si le buffer est plein
        if (buffer.size() == bufferSize) {
            qDebug() << "Buffer full, inserting data into database...";
            // Insère les données du buffer dans la base de données
            bdd.insertData(buffer);

            // Vide le buffer
            buffer.clear();
        }

        QThread::usleep(100);
    }

    // Insère les données restantes du buffer dans la base de données
    if (!buffer.isEmpty()) {
        qDebug() << "Inserting remaining data into database...";
        bdd.insertData(buffer);
    }
    qDebug() << "Indexing complete";
}

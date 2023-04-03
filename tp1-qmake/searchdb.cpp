#include "searchdb.h"
#include <QFileInfo>
#include <QDateTime>

SearchDB::SearchDB(QObject *parent) : QObject(parent)
{

}

bool SearchDB::openDB()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("filesearch.db");

    if (!m_db.open()) {
        qDebug() << m_db.lastError().text();
        return false;
    }

    return true;
}

bool SearchDB::createDB()
{
    QString queryStr = "CREATE TABLE IF NOT EXISTS files (id INTEGER PRIMARY KEY AUTOINCREMENT, path TEXT, filename TEXT, size INTEGER, filetype TEXT, last_modified TEXT)";
    QSqlQuery query;
    if (query.exec(queryStr)) {
        return true;
    } else {
        qDebug() << query.lastError().text();
        return false;
    }
}

bool SearchDB::insertFile(QString path, QString filename, qint64 size, QString filetype, QString lastModified)
{
    QString queryStr = QString("INSERT INTO files (path, filename, size, filetype, last_modified) VALUES('%1', '%2', %3, '%4', '%5')")
            .arg(path)
            .arg(filename)
            .arg(size)
            .arg(filetype)
            .arg(lastModified);

    QSqlQuery query;
    if (query.exec(queryStr)) {
        return true;
    } else {
        qDebug() << query.lastError().text();
        return false;
    }
}

bool SearchDB::searchFiles(QString keyword, QString path, QString ext, QString type, QString dateFrom, QString dateTo, QString sortBy, QString sortOrder)
{
    QString queryStr = QString("SELECT * FROM files WHERE (filename LIKE '%%1%' OR filetype LIKE '%%1%') AND path LIKE '%%2%'")
            .arg(keyword)
            .arg(path);

    if (!ext.isEmpty()) {
        queryStr += QString(" AND filetype='%1'").arg(ext);
    }

    if (!type.isEmpty()) {
        queryStr += QString(" AND filetype LIKE '%%1%'").arg(type);
    }

    if (!dateFrom.isEmpty() && !dateTo.isEmpty()) {
        queryStr += QString(" AND last_modified BETWEEN '%1' AND '%2'").arg(dateFrom).arg(dateTo);
    } else if (!dateFrom.isEmpty()) {
        queryStr += QString(" AND last_modified >= '%1'").arg(dateFrom);
    } else if (!dateTo.isEmpty()) {
        queryStr += QString(" AND last_modified <= '%1'").arg(dateTo);
    }

    if (!sortBy.isEmpty() && !sortOrder.isEmpty()) {
        queryStr += QString(" ORDER BY %1 %2").arg(sortBy).arg(sortOrder);
    }

    QSqlQuery query;
    if (query.exec(queryStr)) {
        while (query.next()) {
            QString filePath = query.value("path").toString() + "/" + query.value("filename").toString();
            qint64 fileSize = query.value("size").toLongLong();
            QDateTime lastModified = QDateTime::fromString(query.value("last_modified").toString(), "yyyy-MM-dd hh:mm:ss");

            qDebug() << "File path: " << filePath << " Size: " << fileSize << " Last Modified: " << lastModified.toString("yyyy-MM-dd hh:mm:ss");
        }

        return true;
    } else {
        qDebug() << query.lastError().text();
        return false;
    }
}

void SearchDB::closeDB()
{
    m_db.close();
}


void SearchDB::test(){
    // Créer une instance de la classe SearchDB
    SearchDB searchDB;

    // Ouvrir la base de données
    searchDB.openDB();

    // Insérer un fichier dans la base de données
    QString path = "/chemin/vers/mon/fichier.txt";
    QString filename = "fichier.txt";
    qint64 size = 1024;
    QString filetype = "txt";
    QDateTime lastModified = QDateTime::currentDateTime();
    QString lastModifiedStr = lastModified.toString("yyyy-MM-dd hh:mm:ss");
    searchDB.insertFile(path, filename, size, filetype, lastModifiedStr);

    // Rechercher le fichier dans la base de données
    QString keyword = "fichier";
    QString ext = "txt";
    QString type = "";
    QString dateFrom = "";
    QString dateTo = "";
    QString sortBy = "filename";
    QString sortOrder = "ASC";
    bool result = searchDB.searchFiles(keyword, "", ext, type, dateFrom, dateTo, sortBy, sortOrder);

    if (result) {
        qDebug() << "Le fichier a été trouvé dans la base de données.";
    } else {
        qDebug() << "Le fichier n'a pas été trouvé dans la base de données.";
    }

    // Fermer la base de données
    searchDB.closeDB();

}

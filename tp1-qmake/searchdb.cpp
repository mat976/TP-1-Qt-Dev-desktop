#include "searchdb.h"

SearchDB::SearchDB(QObject *parent) : QObject(parent)
{

}

bool SearchDB::openDB(QString dbName)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbName);
    if (!m_db.open()) {
        qDebug() << "Error: connection with database fail" << dbName << m_db.lastError().text();
        return false;
    } else {
        qDebug() << "Database: connection ok";
        return true;
    }
}

bool SearchDB::createTable()
{
    QSqlQuery query;
    QString queryString = "CREATE TABLE IF NOT EXISTS files ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "path TEXT,"
            "filename TEXT,"
            "size INTEGER"
            ")";
    if (!query.exec(queryString)) {
        qDebug() << "Error: table creation" << query.lastError().text();
        return false;
    }
    return true;
}

bool SearchDB::insertFile(QString path, QString filename, qint64 fileSize)
{
    QString queryStr = QString("INSERT INTO files (path, filename, size) VALUES('%1', '%2', %3)")
            .arg(path)
            .arg(filename)
            .arg(fileSize);

    QSqlQuery query;
    if (query.exec(queryStr)) {
        return true;
    } else {
        qDebug() << query.lastError().text();
        return false;
    }
}

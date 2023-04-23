#include "bdd.h"

BDD::BDD() {
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("myDatabase.db");
    } else {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
}


BDD::~BDD() {
    close();
}

void BDD::open() {
if (!db.open()) {
    qDebug() << "Database error: " << db.lastError();
}
}

void BDD::close() {
    db.close();
}

void BDD::createTable() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS files ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    "path TEXT, "
    "filename TEXT, "
    "extension TEXT, "
    "size INTEGER)"
    );
}
QList<QList<QVariant>> BDD::searchData(const QString& searchString)
{
    QList<QList<QVariant>> result;

    QSqlQuery query(db);
    query.prepare("SELECT path, filename, extension, size FROM files WHERE path LIKE :search OR filename LIKE :search OR extension LIKE :search");
    query.bindValue(":search", "%" + searchString + "%");

    if (!query.exec()) {
        qDebug() << "Error executing search query: " << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QList<QVariant> row;
        row.append(query.value("path"));
        row.append(query.value("filename"));
        row.append(query.value("extension"));
        row.append(query.value("size"));
        result.append(row);
    }

    return result;
}


void BDD::insertData(const QList<QList<QVariant>>& data)
{
    QSqlQuery query(db);

    if (!db.transaction()) {
        qDebug() << "Transaction error: " << db.lastError().text();
        return;
    }

    query.prepare("INSERT INTO files (path, fileName, extension, size) VALUES (:path, :fileName, :extension, :size)");

    for (const auto& row : data) {
        query.bindValue(":path", row[0]);
        query.bindValue(":fileName", row[1]);
        query.bindValue(":extension", row[2]);
        query.bindValue(":size", row[3]);

        if (!query.exec()) {
            qDebug() << "Error inserting data into database: " << query.lastError().text();
            db.rollback();
            return;
        }
    }

    if (!db.commit()) {
        qDebug() << "Commit error: " << db.lastError().text();
        db.rollback();
    }
}




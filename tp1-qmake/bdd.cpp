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

void BDD::insertData(QString path, QString fileName, QString extension, qint64 size)
{
    QSqlQuery query;
    query.prepare("INSERT INTO files (path, fileName, extension, size) VALUES (:path, :fileName, :extension, :size)");
    query.bindValue(":path", path);
    query.bindValue(":fileName", fileName);
    query.bindValue(":extension", extension);
    query.bindValue(":size", size);

    if (!query.exec()) {
        qDebug() << "Error inserting data into database: " << query.lastError().text();
    }
}


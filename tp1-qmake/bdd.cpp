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

void BDD::insertData(const QList<QList<QVariant>>& data) {
    QSqlQuery query;
    query.prepare("INSERT INTO files (path, fileName, extension, size) VALUES (?, ?, ?, ?)");

    for (const auto& record : data) {
        query.addBindValue(record[0]);
        query.addBindValue(record[1]);
        query.addBindValue(record[2]);
        query.addBindValue(record[3]);
        if (!query.exec()) {
            qDebug() << "Error inserting data into database: " << query.lastError().text();
        }
    }
}



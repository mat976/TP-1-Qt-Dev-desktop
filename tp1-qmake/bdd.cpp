#include "bdd.h"

BDD::BDD() {
db = QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("myDatabase.db");
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
"size INTEGER)");
}

void BDD::insertData(QString path, QString filename, QString extension, qint64 size) {
QSqlQuery query;
query.prepare("INSERT INTO files (path, filename, extension, size) "
"VALUES (:path, :filename, :extension, :size)");
query.bindValue(":path", path);
query.bindValue(":filename", filename);
query.bindValue(":extension", extension);
query.bindValue(":size", size);
query.exec();
}
#include "bdd.h"

BDD::BDD() {
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("myDatabase.db");

    } else {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    qDebug() << "BDD object created";
}

BDD::~BDD() {
    close();
    qDebug() << "BDD object destroyed";
}

bool BDD::open() {
    qDebug() << "Opening database";
    // Connexion à la base de données
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("myDatabase.db");
    // Ouvre la base de données
if (!db.open()) {
    qDebug() << "Error: connection with database failed";
    return false;
}
    qDebug() << "Database opened";
    return true;
}

void BDD::close() {
    qDebug() << "Closing database";
    db.close();
    qDebug() << "Database closed";
}

void BDD::createTable() {
    qDebug() << "Creating table";
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS files ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    "path TEXT, "
    "filename TEXT, "
    "extension TEXT, "
    "size INTEGER)"
    );
    qDebug() << "Table created";
}

QList<QList<QVariant>> BDD::searchData(const QString& searchString) {
    qDebug() << "Searching database for" << searchString;
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
    qDebug() << "Search finished with" << result.size() << "results";
    return result;
}

void BDD::insertData(QList<QVariantList> data)
{
    qDebug() << "Inserting data into database";
    if (!db.isOpen()) {
        if (!open()) {
        qWarning() << "Cannot open database:" << db.lastError().text();
    return;
}
    createTable();
}   QSqlQuery query(db);
    query.prepare("INSERT INTO files (path, filename, extension, size) VALUES (:path, :filename, :extension, :size)");

for (const auto& rowData : data) {
    query.bindValue(":path", rowData.at(0).toString());
    query.bindValue(":filename", rowData.at(1).toString());
    query.bindValue(":extension", rowData.at(2).toString());
    query.bindValue(":size", rowData.at(3).toLongLong());

    if (!query.exec()) {
        qWarning() << "Failed to insert data:" << query.lastError().text();
    }
}
    QThread::usleep(500);
    db.close();

    qDebug() << "Data inserted into database";
}

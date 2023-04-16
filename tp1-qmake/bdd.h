#ifndef BDD_H
#define BDD_H

#include <QtSql>

class BDD {
QSqlDatabase db;
public:
BDD();
~BDD();
void open();
void close();
void createTable();
void insertData(QString path, QString filename, QString extension, qint64 size);
};

#endif // BDD_H

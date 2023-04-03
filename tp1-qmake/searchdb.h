#ifndef SEARCHDB_H
#define SEARCHDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class SearchDB : public QObject
{
    Q_OBJECT
public:
    explicit SearchDB(QObject *parent = nullptr);
    bool openDB();
    bool createDB();
    bool insertFile(QString path, QString filename, qint64 size, QString filetype, QString lastModified);
    bool searchFiles(QString keyword, QString path, QString ext, QString type, QString dateFrom, QString dateTo, QString sortBy, QString sortOrder);
    void closeDB();
    void test();

private:
    QSqlDatabase m_db;

signals:

};

#endif // SEARCHDB_H

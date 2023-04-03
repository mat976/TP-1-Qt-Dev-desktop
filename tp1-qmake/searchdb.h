#ifndef SEARCHDB_H
#define SEARCHDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileInfo>

class SearchDB : public QObject
{
    Q_OBJECT
public:
    explicit SearchDB(QObject *parent = nullptr);
    bool openDB(QString dbName);
    bool createTable();
    bool insertFile(QString path, QString filename, qint64 fileSize);

private:
    QSqlDatabase m_db;

signals:

};

#endif // SEARCHDB_H

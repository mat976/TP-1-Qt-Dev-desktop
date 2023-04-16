#ifndef BDD_H
#define BDD_H

#include <QtSql>

class BDD : public QObject {
    Q_OBJECT
public:
    BDD();
    ~BDD();

    void open();
    void close();

    void createTable();
    void insertData(QString path, QString fileName, QString extension, qint64 size);

private:
    QSqlDatabase db;
};


#endif // BDD_H

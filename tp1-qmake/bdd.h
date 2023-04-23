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
    void insertData(const QList<QList<QVariant>>& data);

private:
    QSqlDatabase db;
};


#endif // BDD_H

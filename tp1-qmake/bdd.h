#ifndef BDD_H
#define BDD_H

#include <QtSql>

class BDD : public QObject {
    Q_OBJECT
public:
    BDD();
    ~BDD();

    bool open();
    void close();

    void createTable();
    void insertData(QList<QVariantList> data);
    QList<QList<QVariant>> searchData(const QString& searchString);


private:
    QSqlDatabase db;
};


#endif // BDD_H

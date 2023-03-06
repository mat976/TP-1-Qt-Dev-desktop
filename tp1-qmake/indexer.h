#ifndef INDEXER_H
#define INDEXER_H

#include <QObject>

class indexer : public QObject
{
    Q_OBJECT
public:
    explicit indexer(QObject *parent = nullptr);

signals:

};

#endif // INDEXER_H

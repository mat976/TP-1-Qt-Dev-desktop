#ifndef INDEXER_H
#define INDEXER_H

#include <QThread>

class indexer : public QThread {
    Q_OBJECT;
    public:
        indexer();
        void run() override;

    signals:
        void newPath(QString path);
};

#endif // INDEXER_H

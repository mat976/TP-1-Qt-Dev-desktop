#ifndef INDEXER_H
#define INDEXER_H

#include <QThread>

class indexer : public QThread {
    QString m_start_path;
    Q_OBJECT;

    public:
        indexer();
        void setStart_path(const QString start_path);
        void run() override;

    signals:
        void newPath(QString path, QString filename, QString extension, qint64 size);
};

#endif // INDEXER_H

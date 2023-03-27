#include "indexer.h"
#include <QDirIterator>

indexer::indexer()
{

}

void indexer::run(){
    QDirIterator it("D:/projects/", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString nextPath = it.next();
        emit newPath(nextPath);
        QThread::usleep(100);
    }
}

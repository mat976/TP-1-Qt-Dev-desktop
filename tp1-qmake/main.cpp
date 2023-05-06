#include "mainwindow.h"
#include "server.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Server server;
    server.start(7007);

    MainWindow w;
    w.show();

    return a.exec();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include "bdd.h"
#include "indexer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool m_isBusy = false;
    int m_proBar = 0;
    indexer *_indexer = nullptr;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int proBar() const;
    void setProBar(int newProBar);

private slots:
    void on_btnSearch_clicked();
    void jobStarted();
    void jobFinished();
    void newPath(QString path, QString fileName, QString extension, qint64 size);

private:
    Ui::MainWindow *ui;
    QBuffer _buffer;

    BDD _bdd; // declare an instance of the BDD class

};

#endif // MAINWINDOW_H

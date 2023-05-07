#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "indexer.h"
#include "fsm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    bool m_isBusy = false;
    int m_proBar = 0;
    indexer *_indexer = nullptr;
    Fsm _fsm;
    //QString testQuery = "SEARCH 'testme please' LAST_MODIFIED:05/07/2023 CREATED:12/2020 MAX_SIZE:10M MIN_SIZE:1M SIZE:BETWEEN 10M AND 20M EXT:txt,doc,xlsx TYPE:image OR text";
    QString testQuery = "SEARCH 'testme please' CREATED:12/2020 MAX_SIZE:10M MIN_SIZE:20M TYPE:image OR text LAST_MODIFIED:05/07/2023";

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isBusy() const;
    void setIsBusy(bool newIsBusy);

    int proBar() const;
    void setProBar(int newProBar);

private slots:
    void on_btnSearch_clicked();
    void jobStarted();
    void jobFinished();
    void newPath(QString path, QString fileName, QString extension, qint64 size, QString lastModified);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

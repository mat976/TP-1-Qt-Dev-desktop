#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void newPath(QString v);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

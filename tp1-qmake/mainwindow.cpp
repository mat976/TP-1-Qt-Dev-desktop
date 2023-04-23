#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bdd.h"

#include <indexer.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _indexer(new indexer)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _indexer->setStart_path("C:/");
    _indexer->start();
}

bool MainWindow::isBusy() const
{
    return m_isBusy;
}

void MainWindow::setIsBusy(bool newIsBusy)
{
    m_isBusy = newIsBusy;
}

int MainWindow::proBar() const
{
    return m_proBar;
}

void MainWindow::setProBar(int newProBar)
{
    m_proBar = newProBar;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_btnSearch_clicked()
{




    m_isBusy =! m_isBusy;
    ui->txtSearch->setDisabled(m_isBusy);
    ui->listResult->setDisabled(m_isBusy);
    m_proBar = m_proBar + 10;
    ui->progressBar->setValue(m_proBar);


}

void MainWindow::jobStarted()
{
    qDebug() << __FUNCTION__ << __LINE__;
}

void MainWindow::jobFinished()
{
    qDebug() << __FUNCTION__ << __LINE__;
}

void MainWindow::newPath(QString path, QString fileName, QString extension, qint64 size)
{
    qDebug() << __FUNCTION__ << __LINE__ << path << fileName << extension << "size:" << size;
}


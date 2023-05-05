#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bdd.h"
#include <QStandardItemModel>
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
    QString searchString = ui->txtSearch->toPlainText();
    _bdd.open();
    // Recherche des données correspondantes dans la base de donnees
    QList<QList<QVariant>> searchDataList = _bdd.searchData(searchString);

    // Création d'un modele de données pour la vue
    QStandardItemModel *model = new QStandardItemModel(searchDataList.size(), 4, this);
    model->setHeaderData(0, Qt::Horizontal, "Path");
    model->setHeaderData(1, Qt::Horizontal, "File Name");
    model->setHeaderData(2, Qt::Horizontal, "Extension");
    model->setHeaderData(3, Qt::Horizontal, "Size");

    // Remplissage du modele avec les données de la base de données
    for (int row = 0; row < searchDataList.size(); ++row) {
        for (int col = 0; col < searchDataList[row].size(); ++col) {
            QStandardItem *item = new QStandardItem(searchDataList[row][col].toString());
            model->setItem(row, col, item);
        }
    }

    // Affichage du modèle dans la vue
    ui->tableView->setModel(model);
    _bdd.close();
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


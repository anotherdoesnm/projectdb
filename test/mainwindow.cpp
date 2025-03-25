#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
// #include <QtUiTools>
// #include <QMessageBox>
#include <QSqlQueryModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    setWindowTitle("Test");
    resize(1000,1000);
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    db.open();
    QSqlQueryModel *model = new QSqlQueryModel;
    //model->setHeaderData();
    model->setQuery(QString("SELECT * FROM Person"));
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow() {}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    //model->setHeaderData();
    model->setQuery(QString("SELECT * FROM %1").arg(arg1));
    ui->tableView->setModel(model);
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
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
    QSqlTableModel *model = new QSqlTableModel;
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setTable(arg1);
    model->select();

    ui->tableView->setModel(model);
}


void MainWindow::on_saveButton_clicked() {
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableView->model());
}

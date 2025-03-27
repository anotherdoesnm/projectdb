#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlRecord>
// #include <QtUiTools>
// #include <QMessageBox>
#include <QSqlQueryModel>
#include <QModelIndex>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    setWindowTitle("Test");
    resize(1000,1000);
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    db.open();
    QSqlTableModel *model = new QSqlTableModel;
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("Person");
    model->select();
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow() {}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    // Когда текст в comboBox меняется, эта функция вызывается.
    // создаем новую модель данных (QSqlTableModel) для работы с базой данных.
    this->model->setTable(arg1);// устанавливаем таблицу в модели, которая соответствует выбранному тексту в comboBox.
    this->model->select();// выбираем данные из таблицы и загружаем их в модель.

    ui->tableView->setModel(model);
}


void MainWindow::on_saveButton_clicked() {
    //QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableView->model());
    // Когда кнопка saveButton нажата, эта функция вызывается.
    // Мы получаем модель данных из tableView.
    this->model->submitAll(); // сохраняем данные в базу данных
    // model->database(). commit(); либо такой строкой то же самое
}

void MainWindow::on_pushButton_clicked()
{

    QSqlRecord record = this->model->record();
    record.remove(record.indexOf("id"));
    this->model->insertRecord(-1,record);
    this->model->submitAll();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    //int id = model->data(model->index(row,0)).toInt();
    this->rowId = row;
}


void MainWindow::on_pushButton_2_clicked()
{
    this->model->setTable(ui->comboBox->currentText());
    this->model->removeRow(this->rowId,QModelIndex());

}


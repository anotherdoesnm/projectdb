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
    // Когда текст в comboBox меняется, эта функция вызывается.
    // создаем новую модель данных (QSqlTableModel) для работы с базой данных.
    QSqlTableModel *model = new QSqlTableModel;
    model->setEditStrategy(QSqlTableModel::OnFieldChange); // устанавливаем стратегию редактирования данных в модели.
    model->setTable(arg1);// устанавливаем таблицу в модели, которая соответствует выбранному тексту в comboBox.
    model->select();// выбираем данные из таблицы и загружаем их в модель.

    ui->tableView->setModel(model);
}


void MainWindow::on_saveButton_clicked() {
    QSqlTableModel *model = qobject_cast<QSqlTableModel*>(ui->tableView->model());
    // Когда кнопка saveButton нажата, эта функция вызывается.
    // Мы получаем модель данных из tableView.
    model->submitAll(); // сохраняем данные в базу данных
    // model->database().commit(); либо такой строкой то же самое
}

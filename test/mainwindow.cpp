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
#include <QAbstractItemView>
#include <QSqlRelationalTableModel>

void MainWindow::on_radioButton_toggled(bool checked) {
    if (checked) {
        // Step 1: Retrieve tool_id values from ToolTransfers
        QSqlQuery query;
        query.prepare("SELECT tool_id FROM ToolTransfers");

        if (query.exec()) {
            while (query.next()) {
                QString toolId = query.value(0).toString();

                // Step 2: Lookup the corresponding type from GardenTools
                QSqlQuery typeQuery;
                typeQuery.prepare("SELECT type FROM GardenTools WHERE tool_id = :toolId");
                typeQuery.bindValue(":toolId", toolId);

                if (typeQuery.exec() && typeQuery.next()) {
                    QString type = typeQuery.value(0).toString();

                    // Step 3: Update the ToolTransfers model
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE ToolTransfers SET tool_id = :type WHERE tool_id = :toolId");
                    updateQuery.bindValue(":type", type);
                    updateQuery.bindValue(":toolId", toolId);
                    updateQuery.exec();
                }
            }
        }

        // Step 4: Refresh the model to reflect changes
        this->model->select();
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    setWindowTitle("Test");
    resize(1000, 1000);
    ui->setupUi(this);

    connect(ui->radioButton, &QRadioButton::toggled, this, &MainWindow::on_radioButton_toggled);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    db.open();
    // this->model = new QSqlTableModel(this);
    this->model = new QSqlRelationalTableModel(this);
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->setTable("Person");
    this->model->select();
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow() {}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    // Когда текст в comboBox меняется, эта функция вызывается.
    // создаем новую модель данных (QSqlTableModel) для работы с базой данных.
    this->model->setTable(arg1);// устанавливаем таблицу в модели, которая соответствует выбранному тексту в comboBox.
    this->model->select();// выбираем данные из таблицы и загружаем их в модель.
    if(arg1 == "TransferHistory"){
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->pushButton_2->setEnabled(false);
    } else if (arg1 == "ToolTransfers") {

        // Set up the relation to the GardenTools table
        this->model->setRelation(this->model->fieldIndex("tool_id"), QSqlRelation("GardenTools", "tool_id", "type"));

        // Select data from the ToolTransfers table

        // Set the model to the table view
    }
    else{
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
        ui->pushButton_2->setEnabled(true);
    }
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
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    //int id = model->data(model->index(row,0)).toInt();
    this->rowId = row;
}


void MainWindow::on_pushButton_2_clicked(){
    this->model->removeRow(this->rowId,QModelIndex());

}


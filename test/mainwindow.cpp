#include "mainwindow.h"
#include "ui_mainwindow.h"  // Add this line
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QModelIndex>
#include <QAbstractItemView>
#include <QSqlRelationalTableModel>
#include <QRadioButton>
#include <QCheckBox>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->radioButton, &QRadioButton::toggled, this, &MainWindow::on_radioButton_toggled);
    // connect(ui->zad, &QComboBox::currentTextChanged, this, &MainWindow::on_comboBox_currentTextChanged);
    setupDatabase();
    setupModel();
    setupzad();
    ui->tableView->setModel(model);
}

void MainWindow::setupDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return;
    }
    qDebug() << "Database opened successfully";
}

void MainWindow::setupModel()
{
    model = new QSqlRelationalTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("Person");
    if (!model->select()) {
        qDebug() << "Error loading Person table:" << model->lastError().text();
    }
}


void MainWindow::on_radioButton_toggled(bool checked)
{
    QString currentTable = ui->comboBox->currentText();
    int toolIdIndex = model->fieldIndex("tool_id");
    if(currentTable == "ToolTransfers"){
    if (checked) {
                model->setRelation(toolIdIndex, QSqlRelation("GardenTools", "id", "type"));
                model->select();
    }else{
        //model->setRelation(toolIdIndex, QSqlRelation());
        model->setTable("ToolTransfers");
        model->select();

    }
    ui->tableView->setModel(model);
    ui->tableView->reset();
}
}
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    model->setTable(arg1);
    model->select();
    ui->radioButton->setChecked(false);

    if (arg1 == "TransferHistory") {
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->pushButton_2->setEnabled(false);
    } else {
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
        ui->pushButton_2->setEnabled(true);
    }

    if (!model->select()) {
        qDebug() << "Error selecting data:" << model->lastError().text();
    }
    ui->tableView->setModel(model);
}

void MainWindow::on_saveButton_clicked()
{
    model->submitAll();
    addTransferHistory();
}

void MainWindow::on_pushButton_clicked()
{
    QSqlRecord record = model->record();
    record.remove(record.indexOf("id"));
    model->insertRecord(-1, record);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    rowId = index.row();

    QString toWho = model->data(model->index(rowId, model->fieldIndex("to_who"))).toString();
    qDebug() << "Table: " << model->index(rowId, model->fieldIndex("to_who")).row();
    // from_whoo = model->data(model->index(rowId, model->fieldIndex("from_who"))).toString();
    // Сохраняем значение для дальнейшего использования
    selectedToWho = toWho;

    if (!ui->zad->findText(toWho)) {
        ui->zad->addItem(toWho);
    }
    this->tool_id = model->index(rowId, model->fieldIndex("to_who")).row() + 1;
}
void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(rowId, QModelIndex());
}

void MainWindow::setupzad()
{
    // подтираем zad
    ui->zad->clear();
    QSqlQuery query("SELECT FIO FROM Person");
    while (query.next()) {
        QString toWho = query.value(0).toString();
        ui->zad->addItem(toWho); // впихиваем элемент в zad
    }
}

void MainWindow::addTransferHistory()
{
    QSqlQuery query;
    qDebug() << "SW: " << this->to_whoo;
    qDebug() << "ST: " << this->selectedToWho;
    if(this->to_whoo == "" || this->selectedToWho == "") return;
    query.prepare("INSERT INTO TransferHistory (from_who, transfer_date, to_who,tool_id) VALUES (:to_who, :date, :to_whoo,:tool_id)");
    query.bindValue(":to_who", this->selectedToWho);
    query.bindValue(":date", QDate::currentDate());
    query.bindValue(":to_whoo", this->to_whoo);
    query.bindValue(":tool_id", this->tool_id);

    if (!query.exec()) {
        qDebug() << "Error adding to TransferHistory:" << query.lastError().text();
        qDebug() << QDate::currentDate();
    } else {
        qDebug() << "Transfer history entry added successfully.";
        // UPDATE OR INSERT ToolTransfers SET from_who = to_who, to_who = to_whoo WHERE tool_id = tool_id;
        QSqlQuery updateQuery;
        updateQuery.prepare("INSERT OR REPLACE INTO ToolTransfers (id,from_who, to_who, tool_id,transfer_date) VALUES (:id,:from_who, :to_who, :tool_id,:transfer_date);");
        // Bind the parameters correctly
        updateQuery.bindValue(":from_who", this->selectedToWho); // Assuming this is the correct value for from_who
        updateQuery.bindValue(":to_who", this->to_whoo); // Corrected parameter name
        updateQuery.bindValue(":tool_id", this->id);
        updateQuery.bindValue(":id",this->id);
        updateQuery.bindValue(":transfer_date",QDate::currentDate());
        if (!updateQuery.exec()) {
            qDebug() << "Error updating ToolTransfers:" << updateQuery.lastError().text();
        } else {
            qDebug() << "ToolTransfers updated successfully.";
        }
    }
    this->to_whoo = "";
    this->selectedToWho = "";
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_zad_currentTextChanged(const QString &arg1)
{
    to_whoo = arg1;
    this->id = this->tool_id;
    //this->tool_id = tid;
}
//db updated 15 04

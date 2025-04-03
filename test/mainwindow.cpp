﻿#include "mainwindow.h"
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
#include <QRadioButton>  // Add this line
#include <QCheckBox>     // Add this line

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->radioButton, &QRadioButton::toggled, this, &MainWindow::on_radioButton_toggled);
    setupDatabase();
    setupModel();
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
}

void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(rowId, QModelIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

#include <QMessageBox>
#include <QProcessEnvironment>

#include <QInputDialog>
#include <QLineEdit>
#include "dialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    setupDatabase();
    bool ok;
    QString encryptionKey = QInputDialog::getText(nullptr, "Пароль БД ",
                                                  "Происходит нечто необычное!\nЗапомни мудрость - чтобы передать вещ другому челу, выбери чела в таблице тултрансферс, в колонне справа, у которого эта вещ есть, и второй чел который её получит, его надо выбрать в выпадающем списочке сверху, понятно да?\nА теперь вводи сука пароль", QLineEdit::Password,
                                                  "", &ok);
    qDebug() << encryptionKey;
    if (ok && !encryptionKey.isEmpty()) {
        QSqlQuery query;
        query.exec(QString("PRAGMA key = '%1'").arg(encryptionKey));

        if (!query.exec("SELECT 1;")) {
            qDebug() << "Error: Incorrect encryption key.";
            qDebug() << query.lastError().text();
            return;
        } else {
            qDebug() << "Database opened successfully with the provided key!";
        }
    }

    qDebug() << "Environment USERNAME:" << QProcessEnvironment::systemEnvironment().value("USERNAME");
    QString currentUser  = QProcessEnvironment::systemEnvironment().value("USERNAME"); // For win
    // QString currentUser  = QProcessEnvironment::systemEnvironment().value("USER"); // For mac linux
    QSqlQuery query;
    query.prepare("SELECT * FROM Person WHERE FIO = (:currentUser)");
    qDebug() << currentUser;
    query.bindValue(":currentUser", currentUser); // Use the currentUser  variable
    qDebug() << "Current User:" << currentUser; // Debug output
    QSqlQuery allUsersQuery("SELECT FIO FROM Person");
    while (allUsersQuery.next()) {
        QString fio = allUsersQuery.value(0).toString();
        qDebug() << "FIO in database:" << fio; // Print each FIO in the database
    }
    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            qDebug() << "User match count:" << count; // Debug output for user match count
            if (count > 0) {
                qDebug() << "User exists in the Person table.";
            } else {
                qDebug() << "User does not exist.";
            }
        } else {
            qDebug() << "No results returned from the query.";
        }
    } else {
        qDebug() << "Query execution failed:" << query.lastError().text(); // Debug output for query error
    }
    ui->setupUi(this);
    connect(ui->radioButton, &QRadioButton::toggled, this, &MainWindow::on_radioButton_toggled);
    // connect(ui->zad, &QComboBox::currentTextChanged, this, &MainWindow::on_comboBox_currentTextChanged);
    setupModel();
    setupzad();
    ui->tableView->setModel(model);
}

void MainWindow::setupDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setPassword("1");
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
    if(currentTable == "ToolTransfers" || currentTable == "TransferHistory"){
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
    ui->radioButton->setChecked(true);

    if (arg1 == "TransferHistory" || arg1 == "ToolTransfers") {
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->pushButton_2->setEnabled(false);
    } else {
        ui->radioButton->setChecked(false);
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

void MainWindow::on_pushButton_3_clicked()
{
    Dialog *d = new Dialog();
    d->show();
}


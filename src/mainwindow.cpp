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
#include "OpenXLSX/OpenXLSX.hpp"
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include "dialog.h"
#include "exportexcel.h"
#include <QStyleFactory>
#include <QApplication>
#include <QSqlDriver>
#include <QPluginLoader>


using namespace OpenXLSX;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //QPluginLoader loader("sqldrivers/sqlitecipher");
    //if (!loader.load()) {
    //    qDebug() << "Error loading SQLITECIPHER plugin:" << loader.errorString();
    //} else {
    //    qDebug() << "SQLITECIPHER plugin loaded successfully";
    //}

    setupDatabase();


    qDebug() << "Environment USERNAME:" << QProcessEnvironment::systemEnvironment().value("USERNAME");
    QString currentUser  = QProcessEnvironment::systemEnvironment().value("USERNAME"); // For win
    // QString currentUser  = QProcessEnvironment::systemEnvironment().value("USER"); // For mac linux
    QSqlQuery query;
    query.prepare("SELECT FIO FROM Person WHERE FIO = :currentUser");
    query.bindValue(":currentUser", currentUser);
    if (query.exec()) {
        while (query.next()) {
            QString fio = query.value(0).toString();
            qDebug() << "FIO in database:" << fio; // Print each FIO in the database
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    ui->setupUi(this);
    connect(ui->radioButton, &QRadioButton::toggled, this, &MainWindow::on_radioButton_toggled);
    // connect(ui->zad, &QComboBox::currentTextChanged, this, &MainWindow::on_comboBox_currentTextChanged);
    setupModel();
    ui->tableView->setModel(model);
    for (const QString &style : QStyleFactory::keys()) {
        //qDebug() << style;
        ui->comboBox_2->addItem(style);
    }
}

void MainWindow::setupDatabase()
{
    QString dbPath = QFileInfo("test.db").absoluteFilePath();
    QFileInfo dbFileInfo(dbPath);
    qDebug() << "Database file path:" << dbPath;
    qDebug() << "Database file exists:" << dbFileInfo.exists() << ", size:" << dbFileInfo.size() << "bytes";
    qDebug() << QSqlDatabase::drivers();

    // QSqlDatabase db = QSqlDatabase::addDatabase("SQLITECIPHER");
    // db.setDatabaseName(dbPath);

    bool ok;
    QString encryptionKey = QInputDialog::getText(nullptr, "Пароль БД ",
                                                  "Происходит нечто необычное!\nА теперь вводи сука пароль", QLineEdit::Password,
                                                  "", &ok);
    qDebug() << encryptionKey;


    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/plugins/sqldrivers");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setConnectOptions("QSQLITE_USE_CIPHER=sqlcipher; SQLCIPHER_LEGACY=1");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return;
    }
    QSqlQuery query(db);
    query.exec(QString("PRAGMA key = '%1';").arg(encryptionKey));
    QSqlQuery query_pomogite(db);
    query_pomogite.exec("PRAGMA cipher_page_size = 4096;");
    query_pomogite.exec("PRAGMA kdf_iter = 256000;");
    query_pomogite.exec("PRAGMA cipher_hmac_algorithm = HMAC_SHA512;");
    query_pomogite.exec("PRAGMA cipher_kdf_algorithm = PBKDF2_HMAC_SHA512;");

    // Test query to check database accessibility
}
void MainWindow::setupModel()
{
    model = new QSqlRelationalTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("Person");
    if (!model->select()) {
        qDebug() << "Error loading Person table:" << model->lastError().text();
    } else {
        qDebug() << "Person table loaded successfully";
    }
    ui->tableView->setModel(model);
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
}

void MainWindow::on_pushButton_clicked()
{
    QSqlRecord record = model->record();
    record.remove(record.indexOf("id"));
    model->insertRecord(-1, record);
}
void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(rowId, QModelIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    Dialog *d = new Dialog();
    d->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    ExportExcel *ex = new ExportExcel();
    ex->show();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    this->rowId = index.row();
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QApplication::setStyle(QStyleFactory::create(arg1));
}


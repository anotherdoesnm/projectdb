#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
// #include <QtUiTools>
// #include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    setWindowTitle("Test");
    resize(1000,1000);
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test.db");
    db.open();
    QSqlQuery q;
    q.exec("CREATE TABLE (test text);");
    db.close();
}

MainWindow::~MainWindow() {}

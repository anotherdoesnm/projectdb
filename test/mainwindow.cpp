#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
//#include <QtUiTools>
//#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow) {
    setWindowTitle("Test");
    resize(1000,1000);
    ui->setupUi(parent);
}

MainWindow::~MainWindow() {}

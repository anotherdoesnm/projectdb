#include "mainwindow.h"
#include <QFile>
#include <QtUiTools>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Test");
    resize(1000,1000);
    QFile f("mainwindow.ui");
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen()) QMessageBox::information(this,"Error!","Can't open ui file");
    QUiLoader loader;
    QWidget* newWidget = loader.load(&f, this );
    setCentralWidget( newWidget );
}

MainWindow::~MainWindow() {}

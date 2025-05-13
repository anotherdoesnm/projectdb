#include "exportexcel.h"
#include "ui_exportexcel.h"

ExportExcel::ExportExcel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ExportExcel)
{
    ui->setupUi(this);
}

ExportExcel::~ExportExcel()
{
    delete ui;
}

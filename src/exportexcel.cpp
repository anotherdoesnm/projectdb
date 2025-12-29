#include "exportexcel.h"
#include "../ui/ui_exportexcel.h"
#include "OpenXLSX/OpenXLSX.hpp"
#include <QFileDialog>
#include <QSqlQuery>
#include <QMessageBox>
using namespace OpenXLSX;
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

void ExportExcel::on_pushButton_clicked()
{
    if(!ui->checkBox->isChecked() && !ui->checkBox_4->isChecked() && !ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked()){
        QMessageBox::warning(nullptr, "Упс", "Вы не выбрали ничего для экспорта", QMessageBox::Ok);
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Excel Files (*.xlsx);;All Files (*)"));
    if(fileName == "") return;
    XLDocument doc;
    doc.create(fileName.toUtf8().constData(),true);
    if(ui->checkBox->isChecked()){
    if(!doc.workbook().sheetExists("Person")) doc.workbook().addWorksheet("Person");
    auto wks = doc.workbook().worksheet("Person");
    wks.cell("A1").value() = "id";
    wks.cell("B1").value() = "fio";
    wks.cell("C1").value() = "address";
    wks.cell("D1").value() = "profession";
    wks.cell("E1").value() = "tab_number";

    QSqlQuery q;
    int i = 2;
    q.exec("SELECT * from Person");
    while(q.next()){
        wks.cell(("A" + QString::number(i)).toUtf8().constData()) = q.value("id").toString().toUtf8().constData();
        wks.cell(("B" + QString::number(i)).toUtf8().constData()) = q.value("fio").toString().toUtf8().constData();
        wks.cell(("C" + QString::number(i)).toUtf8().constData()) = q.value("address").toString().toUtf8().constData();
        wks.cell(("D" + QString::number(i)).toUtf8().constData()) = q.value("profession").toString().toUtf8().constData();
        wks.cell(("E" + QString::number(i)).toUtf8().constData()) = q.value("tab_number").toString().toUtf8().constData();
        i++;
    }
    }

    if(ui->checkBox_2->isChecked()){
        if(!doc.workbook().sheetExists("GardenTools")) doc.workbook().addWorksheet("GardenTools");
        auto wks = doc.workbook().worksheet("GardenTools");
        wks.cell("A1").value() = "id";
        wks.cell("B1").value() = "type";
        wks.cell("C1").value() = "brand";
        wks.cell("D1").value() = "model";
        wks.cell("E1").value() = "price";
        wks.cell("F1").value() = "serial_number";

        QSqlQuery q;
        int i = 2;
        q.exec("SELECT * from GardenTools");
        while(q.next()){
            wks.cell(("A" + QString::number(i)).toUtf8().constData()) = q.value("id").toString().toUtf8().constData();
            wks.cell(("B" + QString::number(i)).toUtf8().constData()) = q.value("type").toString().toUtf8().constData();
            wks.cell(("C" + QString::number(i)).toUtf8().constData()) = q.value("brand").toString().toUtf8().constData();
            wks.cell(("D" + QString::number(i)).toUtf8().constData()) = q.value("model").toString().toUtf8().constData();
            wks.cell(("E" + QString::number(i)).toUtf8().constData()) = q.value("price").toString().toUtf8().constData();
            wks.cell(("F" + QString::number(i)).toUtf8().constData()) = q.value("serial_number").toString().toUtf8().constData();
            i++;
        }
    }
    if(ui->checkBox_3->isChecked()){
        if(!doc.workbook().sheetExists("ToolTransfers")) doc.workbook().addWorksheet("ToolTransfers");
        auto wks = doc.workbook().worksheet("ToolTransfers");
        wks.cell("A1").value() = "id";
        wks.cell("B1").value() = "transfer_date";
        wks.cell("C1").value() = "from_who";
        wks.cell("D1").value() = "to_who";
        wks.cell("E1").value() = "tool_id";

        QSqlQuery q;
        int i = 2;
        q.exec("SELECT * from ToolTransfers");
        while(q.next()){
            wks.cell(("A" + QString::number(i)).toUtf8().constData()) = q.value("id").toString().toUtf8().constData();
            wks.cell(("B" + QString::number(i)).toUtf8().constData()) = q.value("transfer_date").toString().toUtf8().constData();
            wks.cell(("C" + QString::number(i)).toUtf8().constData()) = q.value("from_who").toString().toUtf8().constData();
            wks.cell(("D" + QString::number(i)).toUtf8().constData()) = q.value("to_who").toString().toUtf8().constData();
            wks.cell(("E" + QString::number(i)).toUtf8().constData()) = q.value("tool_id").toString().toUtf8().constData();
            i++;
        }
    }
    if(ui->checkBox_4->isChecked()){
        if(!doc.workbook().sheetExists("TransferHistory")) doc.workbook().addWorksheet("TransferHistory");
        auto wks = doc.workbook().worksheet("TransferHistory");
        wks.cell("A1").value() = "id";
        wks.cell("B1").value() = "fio";
        wks.cell("C1").value() = "address";
        wks.cell("D1").value() = "profession";
        wks.cell("E1").value() = "tab_number";

        QSqlQuery q;
        int i = 2;
        q.exec("SELECT * from TransferHistory");
        while(q.next()){
            wks.cell(("A" + QString::number(i)).toUtf8().constData()) = q.value("id").toString().toUtf8().constData();
            wks.cell(("B" + QString::number(i)).toUtf8().constData()) = q.value("transfer_date").toString().toUtf8().constData();
            wks.cell(("C" + QString::number(i)).toUtf8().constData()) = q.value("from_who").toString().toUtf8().constData();
            wks.cell(("D" + QString::number(i)).toUtf8().constData()) = q.value("to_who").toString().toUtf8().constData();
            wks.cell(("E" + QString::number(i)).toUtf8().constData()) = q.value("tool_id").toString().toUtf8().constData();
            i++;
        }
    }
    doc.workbook().deleteSheet("Sheet1");
    doc.save();
}


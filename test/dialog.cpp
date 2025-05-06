#include "dialog.h"
#include "ui_dialog.h"
#include <QSqlQuery>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QSqlQuery query("SELECT FIO FROM Person");
    while (query.next()) {
        QString toWho = query.value(0).toString();
        ui->comboBox->addItem(toWho);
        ui->comboBox_2->addItem(toWho);
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->comboBox_3->clear();
    QSqlQuery q;
    q.prepare("SELECT gt.type FROM ToolTransfers tt JOIN GardenTools gt ON tt.tool_id = gt.id WHERE tt.to_who = :arg");
    q.bindValue(":arg",arg1);
    q.exec();
    while(q.next()){
        ui->comboBox_3->addItem(q.value(0).toString());
    }
}


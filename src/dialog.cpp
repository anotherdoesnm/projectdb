#include "dialog.h"
#include "../ui/ui_dialog.h"
#include <QSqlQuery>
#include <QDate>
#include <QSqlError>
#include <QDebug>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Склад 1");
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

void Dialog::addTransferHistory()
{
    QSqlQuery query2;
    query2.prepare("SELECT id FROM GardenTools WHERE type = :type");
    qDebug() << "C3: " << ui->comboBox_3->currentText();
    query2.bindValue(":type",ui->comboBox_3->currentText());
    query2.exec();
    query2.next();
    int tool_id = query2.value("id").toInt();
    qDebug() << "Tool id: " << tool_id;
    QString from = ui->comboBox->currentText();
    QString to = ui->comboBox_2->currentText();
    QSqlQuery query;
    if(to == "" || from == "") return;
    query.prepare("INSERT INTO TransferHistory (from_who, transfer_date, to_who,tool_id) VALUES (:to_who, :date, :to_whoo,:tool_id)");
    query.bindValue(":to_who", from);
    query.bindValue(":date", QDate::currentDate());
    query.bindValue(":to_whoo", to);
    query.bindValue(":tool_id", tool_id);

    if (!query.exec()) {
        qDebug() << "Error adding to TransferHistory:" << query.lastError().text();
        qDebug() << QDate::currentDate();
    } else {
        qDebug() << "Transfer history entry added successfully.";
        // UPDATE OR INSERT ToolTransfers SET from_who = to_who, to_who = to_whoo WHERE tool_id = tool_id;
        QSqlQuery updateQuery;
        updateQuery.prepare("INSERT OR REPLACE INTO ToolTransfers (id,from_who, to_who, tool_id,transfer_date) VALUES (:id,:from_who, :to_who, :tool_id,:transfer_date);");
        // Bind the parameters correctly
        updateQuery.bindValue(":from_who", from); // Assuming this is the correct value for from_who
        updateQuery.bindValue(":to_who", to); // Corrected parameter name
        updateQuery.bindValue(":tool_id", tool_id);
        updateQuery.bindValue(":id",tool_id);
        updateQuery.bindValue(":transfer_date",QDate::currentDate());
        if (!updateQuery.exec()) {
            qDebug() << "Error updating ToolTransfers:" << updateQuery.lastError().text();
        } else {
            qDebug() << "ToolTransfers updated successfully.";
        }
    }
}

void Dialog::on_buttonBox_accepted()
{
addTransferHistory();
}


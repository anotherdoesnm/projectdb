/********************************************************************************
** Form generated from reading UI file 'exportexcel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTEXCEL_H
#define UI_EXPORTEXCEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ExportExcel
{
public:
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QPushButton *pushButton;

    void setupUi(QDialog *ExportExcel)
    {
        if (ExportExcel->objectName().isEmpty())
            ExportExcel->setObjectName(QString::fromUtf8("ExportExcel"));
        ExportExcel->resize(179, 137);
        checkBox = new QCheckBox(ExportExcel);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(40, 10, 78, 22));
        checkBox_2 = new QCheckBox(ExportExcel);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(40, 30, 91, 22));
        checkBox_3 = new QCheckBox(ExportExcel);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(40, 50, 91, 22));
        checkBox_4 = new QCheckBox(ExportExcel);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(40, 70, 111, 22));
        pushButton = new QPushButton(ExportExcel);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 100, 121, 24));

        retranslateUi(ExportExcel);

        QMetaObject::connectSlotsByName(ExportExcel);
    } // setupUi

    void retranslateUi(QDialog *ExportExcel)
    {
        ExportExcel->setWindowTitle(QCoreApplication::translate("ExportExcel", "\320\255\320\232\320\241\320\237\320\236\320\240\320\242", nullptr));
        checkBox->setText(QCoreApplication::translate("ExportExcel", "Person", nullptr));
        checkBox_2->setText(QCoreApplication::translate("ExportExcel", "GardenTools", nullptr));
        checkBox_3->setText(QCoreApplication::translate("ExportExcel", "ToolTransfers", nullptr));
        checkBox_4->setText(QCoreApplication::translate("ExportExcel", "TransferHistory", nullptr));
        pushButton->setText(QCoreApplication::translate("ExportExcel", "\320\255\320\232\320\241\320\237\320\236\320\240\320\242\320\230\320\240\320\236\320\222\320\220\320\242\320\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ExportExcel: public Ui_ExportExcel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTEXCEL_H

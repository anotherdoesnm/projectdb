/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QComboBox *comboBox;
    QTableView *tableView;
    QPushButton *saveButton;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QCheckBox *radioButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(992, 647);
        MainWindow->setMaximumSize(QSize(992, 16777215));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 972, 605));
        comboBox = new QComboBox(scrollAreaWidgetContents);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(10, 10, 91, 24));
        comboBox->setMinimumSize(QSize(0, 24));
        tableView = new QTableView(scrollAreaWidgetContents);
        tableView->setObjectName("tableView");
        tableView->setGeometry(QRect(15, 51, 941, 531));
        saveButton = new QPushButton(scrollAreaWidgetContents);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(110, 10, 91, 24));
        pushButton = new QPushButton(scrollAreaWidgetContents);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(210, 10, 80, 24));
        pushButton_2 = new QPushButton(scrollAreaWidgetContents);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(300, 10, 80, 24));
        radioButton = new QCheckBox(scrollAreaWidgetContents);
        radioButton->setObjectName("radioButton");
        radioButton->setGeometry(QRect(390, 10, 78, 22));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Qt + GCC/G++ Template", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Person", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "GardenTools", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "ToolTransfers", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "TransferHistory", nullptr));

        saveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\236\320\245\320\240\320\220\320\235\320\230\320\242\320\254", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\236\320\227\320\224\320\220\320\242\320\254", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\243\320\224\320\220\320\233\320\230\320\242\320\254", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

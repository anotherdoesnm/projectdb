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
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QComboBox *comboBox_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(992, 647);
        MainWindow->setMinimumSize(QSize(992, 647));
        MainWindow->setMaximumSize(QSize(992, 647));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setMinimumSize(QSize(974, 607));
        scrollArea->setMaximumSize(QSize(974, 607));
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
        radioButton->setGeometry(QRect(390, 10, 171, 22));
        pushButton_3 = new QPushButton(scrollAreaWidgetContents);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(560, 10, 161, 24));
        pushButton_4 = new QPushButton(scrollAreaWidgetContents);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(720, 10, 131, 24));
        comboBox_2 = new QComboBox(scrollAreaWidgetContents);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(860, 10, 101, 24));
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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\237\320\240\320\220\320\255\320\232\320\242 \320\224\320\230\320\221\320\230", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Person", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "GardenTools", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "ToolTransfers", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "TransferHistory", nullptr));

        saveButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\236\320\245\320\240\320\220\320\235\320\230\320\242\320\254", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\236\320\227\320\224\320\220\320\242\320\254", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\243\320\224\320\220\320\233\320\230\320\242\320\254", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \320\270\320\274\320\265\320\275\320\260 \320\277\321\200\320\265\320\264\320\274\320\265\321\202\320\276\320\262", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\237\320\225\320\240\320\225\320\224\320\220\320\242\320\254 \320\222\320\225\320\251\320\252", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\320\255\320\232\320\241\320\237\320\236\320\240\320\242\320\230\320\240\320\236\320\222\320\220\320\242\320\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

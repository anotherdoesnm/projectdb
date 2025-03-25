#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel> // Include QSqlTableModel

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1); // Slot for ComboBox selection change
    void on_saveButton_clicked(); // Slot for saving changes

private:
    Ui::MainWindow *ui;
    QSqlTableModel *model; // Model for the QTableView
    void loadData(const QString &tableName); // Function to load data into the model based on the selected table
};

#endif // MAINWINDOW_H

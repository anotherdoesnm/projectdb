#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // Этот конструктор класса MainWindow принимает один параметр - родительский виджет (QWidget).
    // Параметр parent по умолчанию равен nullptr, что означает, что этот виджет не имеет родителя.
    // Слово explicit означает, что этот конструктор не может быть использован для неявного преобразования типов.

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_saveButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_radioButton_toggled(bool checked);
    void on_pushButton_3_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_4_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    void setupDatabase();
    void setupModel();
    void updateToolDisplay();
    int rowId;
    Ui::MainWindow *ui;
    QSqlRelationalTableModel *model;
    void loadData(const QString &tableName);
}; // Это функция, которая загружает данные из базы данных в модель данных (QSqlTableModel) на основе имени таблицы (tableName).
    // Параметр tableName представляет собой имя таблицы, данные из которой необходимо загрузить.


#endif // MAINWINDOW_H

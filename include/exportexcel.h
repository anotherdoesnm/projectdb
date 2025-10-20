#ifndef EXPORTEXCEL_H
#define EXPORTEXCEL_H

#include <QDialog>

namespace Ui {
class ExportExcel;
}

class ExportExcel : public QDialog
{
    Q_OBJECT

public:
    explicit ExportExcel(QWidget *parent = nullptr);
    ~ExportExcel();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ExportExcel *ui;
};

#endif // EXPORTEXCEL_H

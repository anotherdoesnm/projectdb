#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_buttonBox_accepted();
    void addTransferHistory();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

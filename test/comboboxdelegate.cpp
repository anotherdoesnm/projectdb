#include "comboboxdelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QComboBox *comboBox = new QComboBox(parent);
    // Add items to the combo box
    comboBox->addItem("Option 1");
    comboBox->addItem("Option 2");
    comboBox->addItem("Option 3");
    // Add more options as needed
    return comboBox;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    if (comboBox) {
        // Set the current value of the combo box
        comboBox->setCurrentText(index.model()->data(index, Qt::EditRole).toString());
    }
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
    if (comboBox) {
        // Save the selected value back to the model
        model->setData(index, comboBox->currentText(), Qt::EditRole);
    }
}

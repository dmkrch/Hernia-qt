#ifndef OPERATIONADDFORM_H
#define OPERATIONADDFORM_H

#include <QDialog>
#include <QComboBox>
#include <QAbstractItemView>

#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "sequenceform.h"
#include "dateform.h"
#include "classes_model/handled_operation.h"

namespace Ui
{
class OperationAddForm;
}

class OperationAddForm : public QDialog
{
    Q_OBJECT

public:
    explicit OperationAddForm(QWidget *parent = nullptr);
    ~OperationAddForm();

private slots:
    void on_pushButton_choose_date_clicked();
    void date_chosen();
    void seq_form_closed();
    void on_pushButton_sequela_clicked();

private:
    Ui::OperationAddForm *ui;

    // forms
    DateForm* date_form;
    SequenceForm* seq_form;

    // database settings
    QString db_name;

    Handled_Operation* operation_to_add;
};

#endif // OPERATIONADDFORM_H

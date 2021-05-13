#ifndef OPERATIONADDFORM_H
#define OPERATIONADDFORM_H

#include <QDialog>
#include <QComboBox>
#include <QAbstractItemView>
#include <QMessageBox>

#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "sequenceform.h"
#include "dateform.h"
#include "classes_model/handled_operation.h"
#include "inguinalherniaform.h"
#include "postventralherniaform.h"
#include "pventralherniaform.h"

namespace Ui
{
class OperationAddForm;
}

class OperationAddForm : public QDialog
{
    Q_OBJECT

public:
    explicit OperationAddForm(QWidget *parent = nullptr);
    void Set_Surgeons_List();
    ~OperationAddForm();

signals:
    void operation_added();

private slots:
    void on_pushButton_choose_date_clicked();
    void date_chosen();
    void seq_form_closed();
    void on_pushButton_sequela_clicked();
    void on_horizontalSlider_pat_age_valueChanged(int value);
    void on_horizontalSlider_valueChanged(int value);
    void open_diagnosis_form(QString diagnosis_type);
    void inguinal_form_closed();
    void primary_ventral_form_closed();
    void post_ventral_form_closed();

    void on_pushButton_add_op_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::OperationAddForm *ui;

    // forms
    DateForm* date_form;
    SequenceForm* seq_form;
    InguinalHerniaForm* inguinalHerniaform;
    PostVentralHerniaForm* postVentralHerniaform;
    PVentralHerniaForm* pventralHerniaform;

    // database settings
    QString db_name;

    Handled_Operation* operation_to_add;
};

#endif // OPERATIONADDFORM_H

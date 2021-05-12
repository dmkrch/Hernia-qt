#ifndef POSTVENTRALHERNIAFORM_H
#define POSTVENTRALHERNIAFORM_H

#include <QDialog>
#include "classes_model/diagnosis.h"


namespace Ui {
class PostVentralHerniaForm;
}

class PostVentralHerniaForm : public QDialog
{
    Q_OBJECT

public:
    explicit PostVentralHerniaForm(QWidget *parent = nullptr);
    Postoperative_Ventral_Hernia* Get_Hernia() { return postop_hernia;}
    void Set_Only_Conrete_Choice();

    ~PostVentralHerniaForm();
signals:
    void form_was_closed();

private slots:
    void on_pushButton_choose_op_clicked();

private:
    Ui::PostVentralHerniaForm *ui;
    Postoperative_Ventral_Hernia* postop_hernia;
};

#endif // POSTVENTRALHERNIAFORM_H

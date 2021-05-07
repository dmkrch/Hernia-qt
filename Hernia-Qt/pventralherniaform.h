#ifndef PVENTRALHERNIAFORM_H
#define PVENTRALHERNIAFORM_H

#include <QDialog>
#include "classes_model/diagnosis.h"

namespace Ui {
class PVentralHerniaForm;
}

class PVentralHerniaForm : public QDialog
{
    Q_OBJECT

public:
    explicit PVentralHerniaForm(QWidget *parent = nullptr);
    Primary_Ventral_Hernia* Get_Hernia() { return ventral_hernia; }
    ~PVentralHerniaForm();
signals:
    void form_was_closed();

private slots:
    void set_diagnosis_ventral_type(QString ventral_type);

    void on_pushButton_choose_clicked();

private:
    Ui::PVentralHerniaForm *ui;
    Primary_Ventral_Hernia* ventral_hernia;
};

#endif // PVENTRALHERNIAFORM_H

#ifndef INGUINALHERNIAFORM_H
#define INGUINALHERNIAFORM_H

#include <QDialog>
#include "classes_model/diagnosis.h"

namespace Ui {
class InguinalHerniaForm;
}

class InguinalHerniaForm : public QDialog
{
    Q_OBJECT

signals:
    void form_was_closed();

public:
    explicit InguinalHerniaForm(QWidget *parent = nullptr);
    Inguinal_Hernia* Get_Hernia() { return inguinal_hernia; }
    ~InguinalHerniaForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::InguinalHerniaForm *ui;
    Inguinal_Hernia* inguinal_hernia;
};

#endif // INGUINALHERNIAFORM_H

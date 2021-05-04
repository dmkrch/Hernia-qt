#ifndef PVENTRALHERNIAFORM_H
#define PVENTRALHERNIAFORM_H

#include <QDialog>

namespace Ui {
class PVentralHerniaForm;
}

class PVentralHerniaForm : public QDialog
{
    Q_OBJECT

public:
    explicit PVentralHerniaForm(QWidget *parent = nullptr);
    ~PVentralHerniaForm();

private slots:
    void set_diagnosis_ventral_type(QString ventral_type);

    void on_pushButton_choose_clicked();

private:
    Ui::PVentralHerniaForm *ui;
};

#endif // PVENTRALHERNIAFORM_H

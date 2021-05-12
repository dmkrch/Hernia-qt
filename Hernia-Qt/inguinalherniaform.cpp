#include "inguinalherniaform.h"
#include "ui_inguinalherniaform.h"

InguinalHerniaForm::InguinalHerniaForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InguinalHerniaForm)
{
    this->inguinal_hernia = new Inguinal_Hernia("паховая");
    ui->setupUi(this);
}

void InguinalHerniaForm::Set_Only_Conrete_Choice()
{
    ui->radioButton_all_lmf->setEnabled(false);
    ui->radioButton_all_pr->setEnabled(false);
    ui->radioButton_all_size->setEnabled(false);
}

InguinalHerniaForm::~InguinalHerniaForm()
{
    delete ui;
}

void InguinalHerniaForm::on_pushButton_clicked()
{
    // setting PR
    if (ui->radioButton_all_pr->isChecked())
        inguinal_hernia->Set_PR(Inguinal_Hernia_PR::ANY_PR);
    else if (ui->radioButton_p->isChecked())
        inguinal_hernia->Set_PR(Inguinal_Hernia_PR::P);
    else if (ui->radioButton_r->isChecked())
        inguinal_hernia->Set_PR(Inguinal_Hernia_PR::R);


    // setting LMF
    if (ui->radioButton_all_lmf->isChecked())
        inguinal_hernia->Set_LMF(Inguinal_Hernia_LMF::ANY_LMF);
    else if (ui->radioButton_l->isChecked())
        inguinal_hernia->Set_LMF(Inguinal_Hernia_LMF::L);
    else if (ui->radioButton_m->isChecked())
        inguinal_hernia->Set_LMF(Inguinal_Hernia_LMF::M);
    else if (ui->radioButton_f->isChecked())
        inguinal_hernia->Set_LMF(Inguinal_Hernia_LMF::F);

    // setting SIZES
    if (ui->radioButton_all_size->isChecked())
        inguinal_hernia->Set_Size(Inguinal_Hernia_SIZE::ANY_INGUINAL_SIZE);
    else if (ui->radioButton_size1->isChecked())
        inguinal_hernia->Set_Size(Inguinal_Hernia_SIZE::S1);
    else if (ui->radioButton_size2->isChecked())
        inguinal_hernia->Set_Size(Inguinal_Hernia_SIZE::S2);
    else if (ui->radioButton_size3->isChecked())
        inguinal_hernia->Set_Size(Inguinal_Hernia_SIZE::S3);
    else if (ui->radioButton_size4->isChecked())
        inguinal_hernia->Set_Size(Inguinal_Hernia_SIZE::S4);
    else if (ui->radioButton_size5->isChecked())
        inguinal_hernia->Set_Size(Inguinal_Hernia_SIZE::S5);


    emit form_was_closed();
    this->close();
}

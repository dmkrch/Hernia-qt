#include "postventralherniaform.h"
#include "ui_postventralherniaform.h"

PostVentralHerniaForm::PostVentralHerniaForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostVentralHerniaForm)
{
    this->postop_hernia = new Postoperative_Ventral_Hernia("послеоперационная");
    ui->setupUi(this);
}

PostVentralHerniaForm::~PostVentralHerniaForm()
{
    delete ui;
}

void PostVentralHerniaForm::on_pushButton_choose_op_clicked()
{
    // setting M
    if (ui->radioButton_any_m->isChecked())
        postop_hernia->Set_M(Postoperative_Ventral_Hernia_M::ANY_M);
    else if (ui->radioButton_m1->isChecked())
        postop_hernia->Set_M(Postoperative_Ventral_Hernia_M::M1);
    else if (ui->radioButton_m2->isChecked())
        postop_hernia->Set_M(Postoperative_Ventral_Hernia_M::M2);
    else if (ui->radioButton_m3->isChecked())
        postop_hernia->Set_M(Postoperative_Ventral_Hernia_M::M3);
    else if (ui->radioButton_m4->isChecked())
        postop_hernia->Set_M(Postoperative_Ventral_Hernia_M::M4);
    else if (ui->radioButton_m5->isChecked())
        postop_hernia->Set_M(Postoperative_Ventral_Hernia_M::M5);


    // setting L
    if (ui->radioButton_any_l->isChecked())
        postop_hernia->Set_L(Postoperative_Ventral_Hernia_L::ANY_L);
    else if (ui->radioButton_l1->isChecked())
        postop_hernia->Set_L(Postoperative_Ventral_Hernia_L::L1);
    else if (ui->radioButton_l2->isChecked())
        postop_hernia->Set_L(Postoperative_Ventral_Hernia_L::L2);
    else if (ui->radioButton_l3->isChecked())
        postop_hernia->Set_L(Postoperative_Ventral_Hernia_L::L3);
    else if (ui->radioButton_l4->isChecked())
        postop_hernia->Set_L(Postoperative_Ventral_Hernia_L::L4);


    // setting W
    if (ui->radioButton_any_w->isChecked())
        postop_hernia->Set_W(Postoperative_Ventral_Hernia_W::ANY_W);
    else if (ui->radioButton_w1->isChecked())
        postop_hernia->Set_W(Postoperative_Ventral_Hernia_W::W1);
    else if (ui->radioButton_w2->isChecked())
        postop_hernia->Set_W(Postoperative_Ventral_Hernia_W::W2);
    else if (ui->radioButton_w3->isChecked())
        postop_hernia->Set_W(Postoperative_Ventral_Hernia_W::W3);


    // setting R
    if (ui->radioButton_any_r->isChecked())
        postop_hernia->Set_R(Postoperative_Ventral_Hernia_R::ANY_R);
    else if (ui->radioButton_r1->isChecked())
        postop_hernia->Set_R(Postoperative_Ventral_Hernia_R::R1);
    else if (ui->radioButton_r2->isChecked())
        postop_hernia->Set_R(Postoperative_Ventral_Hernia_R::R2);
    else if (ui->radioButton_r3->isChecked())
        postop_hernia->Set_R(Postoperative_Ventral_Hernia_R::R3);
    else if (ui->radioButton_r4->isChecked())
        postop_hernia->Set_R(Postoperative_Ventral_Hernia_R::R4);


    emit form_was_closed();
    this->close();
}

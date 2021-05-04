#include "inguinalherniaform.h"
#include "ui_inguinalherniaform.h"

InguinalHerniaForm::InguinalHerniaForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InguinalHerniaForm)
{
    ui->setupUi(this);
}

InguinalHerniaForm::~InguinalHerniaForm()
{
    delete ui;
}

void InguinalHerniaForm::on_pushButton_clicked()
{
    this->close();
}

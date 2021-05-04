#include "postventralherniaform.h"
#include "ui_postventralherniaform.h"

PostVentralHerniaForm::PostVentralHerniaForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PostVentralHerniaForm)
{
    ui->setupUi(this);
}

PostVentralHerniaForm::~PostVentralHerniaForm()
{
    delete ui;
}

void PostVentralHerniaForm::on_pushButton_clicked()
{
    this->close();
}

#include "pventralherniaform.h"
#include "ui_pventralherniaform.h"

PVentralHerniaForm::PVentralHerniaForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PVentralHerniaForm)
{
    ui->setupUi(this);
}

PVentralHerniaForm::~PVentralHerniaForm()
{
    delete ui;
}

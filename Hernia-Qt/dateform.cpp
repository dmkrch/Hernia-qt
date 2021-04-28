#include "dateform.h"
#include "ui_dateform.h"

DateForm::DateForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateForm)
{
    ui->setupUi(this);
}

DateForm::~DateForm()
{
    delete ui;
}

void DateForm::on_calendarWidget_clicked(const QDate &date)
{
    date1 = date;
    emit date_setted();
    this->close();
}

QDate DateForm::GetDate()
{
    return this->date1;
}

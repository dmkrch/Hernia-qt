#include "pventralherniaform.h"
#include "ui_pventralherniaform.h"
#include <QAbstractItemView>

PVentralHerniaForm::PVentralHerniaForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PVentralHerniaForm)
{
    ui->setupUi(this);


    QStringList pventral_diagnosises = {"---любая---","срединная", "боковая"};


    ui->comboBox_type_pventral_hernia->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_type_pventral_hernia->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox_type_pventral_hernia->addItems(pventral_diagnosises);

    connect(ui->comboBox_type_pventral_hernia, &QComboBox::currentTextChanged, this,
            &PVentralHerniaForm::set_diagnosis_ventral_type);
}

PVentralHerniaForm::~PVentralHerniaForm()
{
    delete ui;
}


void PVentralHerniaForm::set_diagnosis_ventral_type(QString ventral_type)
{
     if (ventral_type == "---любая---")
     {
        ui->comboBox_subtype_pventral_hernia->clear();
     }
     else if (ventral_type == "срединная")
     {
         ui->comboBox_subtype_pventral_hernia->clear();
        QStringList pventral_middle = {"эпигистральная", "пупочная"};
        ui->comboBox_subtype_pventral_hernia->addItems(pventral_middle);
     }
     else if (ventral_type == "боковая")
     {
        ui->comboBox_subtype_pventral_hernia->clear();
        QStringList pventral_side = {"спигелевой линии", "поясничная"};
        ui->comboBox_subtype_pventral_hernia->addItems(pventral_side);
     }
}

void PVentralHerniaForm::on_pushButton_choose_clicked()
{
    this->close();
}

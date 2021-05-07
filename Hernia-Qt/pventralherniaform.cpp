#include "pventralherniaform.h"
#include "ui_pventralherniaform.h"
#include <QAbstractItemView>

PVentralHerniaForm::PVentralHerniaForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PVentralHerniaForm)
{
    this->ventral_hernia = new Primary_Ventral_Hernia("первичная");
    ui->setupUi(this);


    QStringList pventral_diagnosises = {"--любая--","срединная", "боковая"};


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
     if (ventral_type == "--любая--")
     {
        ui->comboBox_subtype_pventral_hernia->clear();
     }
     else if (ventral_type == "срединная")
     {
        ui->comboBox_subtype_pventral_hernia->clear();
        QStringList pventral_middle = {"--любая срединная--", "эпигистральная", "пупочная"};
        ui->comboBox_subtype_pventral_hernia->addItems(pventral_middle);
     }
     else if (ventral_type == "боковая")
     {
        ui->comboBox_subtype_pventral_hernia->clear();
        QStringList pventral_side = {"--любая боковая--", "спигелевой линии", "поясничная"};
        ui->comboBox_subtype_pventral_hernia->addItems(pventral_side);
     }
}

void PVentralHerniaForm::on_pushButton_choose_clicked()
{
    // setting not chosen to every component
    this->ventral_hernia->Set_Type(Primary_Ventral_Hernia_Types::TYPE_NOT_CHOSEN);
    this->ventral_hernia->Set_Subtitle(Primary_Ventral_Hernia_SubTypes::SUBTYPE_NOT_CHOSEN);
    this->ventral_hernia->Set_Size(Primary_Ventral_Hernia_Sizes::SIZE_NOT_CHOSEN);


    // setting type
    if (ui->comboBox_type_pventral_hernia->currentText() == "--любая--")
        this->ventral_hernia->Set_Type(Primary_Ventral_Hernia_Types::ANY_PRIMARY_VENTRAL_TYPE);
    else if (ui->comboBox_type_pventral_hernia->currentText() == "срединная")
        this->ventral_hernia->Set_Type(Primary_Ventral_Hernia_Types::MIDDLE);
    else if (ui->comboBox_type_pventral_hernia->currentText() == "боковая")
        this->ventral_hernia->Set_Type(Primary_Ventral_Hernia_Types::SIDE);

    // setting subtitle
    if (ui->comboBox_subtype_pventral_hernia->currentText() == "--любая срединная--")
        this->ventral_hernia->Set_Subtitle(Primary_Ventral_Hernia_SubTypes::ANY_PRIMARY_VENTRAL_SUBTYPE);
    else if (ui->comboBox_subtype_pventral_hernia->currentText() == "--любая боковая--")
        this->ventral_hernia->Set_Subtitle(Primary_Ventral_Hernia_SubTypes::ANY_PRIMARY_VENTRAL_SUBTYPE);
    else if (ui->comboBox_subtype_pventral_hernia->currentText() == "эпигистральная")
        this->ventral_hernia->Set_Subtitle(Primary_Ventral_Hernia_SubTypes::EPIGASTRIC);
    else if (ui->comboBox_subtype_pventral_hernia->currentText() == "пупочная")
        this->ventral_hernia->Set_Subtitle(Primary_Ventral_Hernia_SubTypes::UMBICIAL);
    else if (ui->comboBox_subtype_pventral_hernia->currentText() == "спигелевой линии")
        this->ventral_hernia->Set_Subtitle(Primary_Ventral_Hernia_SubTypes::SPIGEL);
    else if (ui->comboBox_subtype_pventral_hernia->currentText() == "поясничная")
        this->ventral_hernia->Set_Subtitle(Primary_Ventral_Hernia_SubTypes::LUMBAR);

    // setting size
    if (ui->radioButton_all_size->isChecked())
        this->ventral_hernia->Set_Size(Primary_Ventral_Hernia_Sizes::ANY_PRIMARY_VENTRAL_SIZE);
    else if (ui->radioButton_small->isChecked())
        this->ventral_hernia->Set_Size(Primary_Ventral_Hernia_Sizes::SMALL);
    else if (ui->radioButton_middle->isChecked())
        this->ventral_hernia->Set_Size(Primary_Ventral_Hernia_Sizes::MEDIUM);
    else if (ui->radioButton_big->isChecked())
        this->ventral_hernia->Set_Size(Primary_Ventral_Hernia_Sizes::LARGE);


    emit form_was_closed();
    this->close();
}

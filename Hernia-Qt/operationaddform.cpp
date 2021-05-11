#include "operationaddform.h"
#include "ui_operationaddform.h"

OperationAddForm::OperationAddForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OperationAddForm)
{
    ui->setupUi(this);

    // setting db name
    db_name = "/home/dmkrch/Programming/Hernia-qt/Hernia-Qt/hernia.db";

    // setting date form
    date_form = new DateForm();
    date_form->setModal(true);
    connect(this->date_form, &DateForm::date_setted, this, &OperationAddForm::date_chosen);


    // adding operations to op_combobox
    QStringList operations = {"----все операции----", "Постемпский", "Жиррару-Спасоккукоцкому", "Сапежко",
                              "Мейо", "Напалков", "Полиспасными швами", "SUBLAY",
                              "RIVES", "STOPPA", "RIVES-STOPPA-Wanz", "ONLAY",
                              "Novitsky", "TAR-technique", "Carbonelli", "Ramirez",
                              "IPOM", "IPOM+", "МILOS", "E MILOS", "E TEP"};

    ui->comboBox_operations->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_operations->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox_operations->addItems(operations);


    // adding surgeons to surgeons_combobox from db
    ui->comboBox_surgeons->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_surgeons->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(QSqlDatabase::database(db_name));

    qry->prepare("select surg_name from surgeons;");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_surgeons->setModel(modal);


    // setting sequence form
    seq_form = new SequenceForm();
    seq_form->setModal(true);

    connect(seq_form, &SequenceForm::form_was_closed, this, &OperationAddForm::seq_form_closed);

    // intializing operation to add
    operation_to_add = new Handled_Operation();
}

OperationAddForm::~OperationAddForm()
{
    delete ui;
}

void OperationAddForm::seq_form_closed()
{
    operation_to_add->Set_Sequela(seq_form->Get_Sequela());

    QString type = operation_to_add->Get_Sequela()->Get_Type();
    QString title = operation_to_add->Get_Sequela()->Get_Title();

    if (title != "")
        ui->label_sequela->setText("Осложнение: " + title);
    else
        ui->label_sequela->setText("Осложнение: " + type);
}

void OperationAddForm::on_pushButton_choose_date_clicked()
{
    date_form->show();
}

void OperationAddForm::date_chosen()
{
    QDate date = date_form->GetDate();
    ui->dateEdit->setDate(date);
}

void OperationAddForm::on_pushButton_sequela_clicked()
{
    seq_form->show();
}

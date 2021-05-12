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
    QStringList operations = {"не указано", "Постемпский", "Жиррару-Спасоккукоцкому", "Сапежко",
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
    seq_form->Set_Only_Concrete();

    connect(seq_form, &SequenceForm::form_was_closed, this, &OperationAddForm::seq_form_closed);

    // intializing operation to add
    operation_to_add = new Handled_Operation();


    // setting diagnosis form open connection
    QStringList diagnosises = {"паховая грыжа", "первичная вентральная грыжа",
                               "послеоперационная вентральная грыжа"};

    ui->comboBox_diagnosis->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_diagnosis->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox_diagnosis->addItems(diagnosises);

    connect(ui->comboBox_diagnosis, &QComboBox::currentTextChanged, this, &OperationAddForm::open_diagnosis_form);


    // setting inguinal, pventraд, postventral forms
    // inguinalform setup
    inguinalHerniaform = new InguinalHerniaForm();
    inguinalHerniaform->setModal(true);
    inguinalHerniaform->Set_Only_Conrete_Choice();

    connect(inguinalHerniaform, &InguinalHerniaForm::form_was_closed, this,
            &OperationAddForm::inguinal_form_closed);



    // pventralHerniaForm setup
    pventralHerniaform = new PVentralHerniaForm();
    pventralHerniaform->setModal(true);
    pventralHerniaform->Set_Only_Conrete_Choice();


    connect(pventralHerniaform, &PVentralHerniaForm::form_was_closed, this,
            &OperationAddForm::primary_ventral_form_closed);



    // post ventral hernia form setup
    postVentralHerniaform = new PostVentralHerniaForm();
    postVentralHerniaform->setModal(true);
    postVentralHerniaform->Set_Only_Conrete_Choice();

    // connecting postoperative ventral form closed
    connect(postVentralHerniaform, &PostVentralHerniaForm::form_was_closed, this,
            &OperationAddForm::post_ventral_form_closed);


}

OperationAddForm::~OperationAddForm()
{
    delete ui;
}

void OperationAddForm::inguinal_form_closed()
{
    operation_to_add->Set_Diagnosis(inguinalHerniaform->Get_Hernia());

    QString result = this->operation_to_add->Get_Diagnosis()->Get_String();
    ui->label_diagnosis->setText("Диагноз: " + result);
}

void OperationAddForm::primary_ventral_form_closed()
{
    operation_to_add->Set_Diagnosis(pventralHerniaform->Get_Hernia());

    QString result = this->operation_to_add->Get_Diagnosis()->Get_String();
    ui->label_diagnosis->setText("Диагноз: " + result);
}

void OperationAddForm::post_ventral_form_closed()
{
    operation_to_add->Set_Diagnosis(postVentralHerniaform->Get_Hernia());

    QString result = this->operation_to_add->Get_Diagnosis()->Get_String();
    ui->label_diagnosis->setText("Диагноз: " + result);
}



void OperationAddForm::open_diagnosis_form(QString diagnosis_type)
{
    if (diagnosis_type == "паховая грыжа")
    {
        inguinalHerniaform->show();
    }
    else if (diagnosis_type == "первичная вентральная грыжа")
    {
        pventralHerniaform->show();
    }
    else if (diagnosis_type == "послеоперационная вентральная грыжа")
    {
        postVentralHerniaform->show();
    }
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

void OperationAddForm::on_horizontalSlider_pat_age_valueChanged(int value)
{
    ui->label_pat_age->setText(QString::number(value));
}

void OperationAddForm::on_horizontalSlider_valueChanged(int value)
{
    ui->label_days->setText(QString::number(value));
}

void OperationAddForm::on_pushButton_add_op_clicked()
{
    // getting date and checking
    QDate date = ui->dateEdit->date();


    // getting op title and checking if not null
    QString op_title = ui->comboBox_operations->currentText();
    if (op_title == "не указано")
    {
        QMessageBox::warning(this, "добавление операции", "Укажите название операции");
        return;
    }

    // getting surgeon name
    QString  surg_name = ui->comboBox_surgeons->currentText();

    // getting recovering days
    int rec_days = ui->horizontalSlider->value();

    // getting patient age
    int pat_age = ui->horizontalSlider_pat_age->value();


    QString gender;
    // getting patient gender
    if (ui->radioButton_gender_f->isChecked())
        gender = "ж";
    else if (ui->radioButton_gender_m->isChecked())
        gender = "м";
    else
        QMessageBox::warning(this, "Добавление операции", "Укажите пол пациента");



}

#include "operationaddform.h"
#include "ui_operationaddform.h"

#include <QDebug>


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
    QStringList diagnosises = {"не указано", "паховая грыжа", "первичная вентральная грыжа",
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
    if (diagnosis_type == "не указано")
    {
        ui->label_diagnosis->setText("Диагноз: " + diagnosis_type);
    }
    else if (diagnosis_type == "паховая грыжа")
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
    operation_to_add->Set_Date(date);
    QString date_str = date.toString("yyyy-MM-dd");


    // getting op title and checking if not null
    QString op_title = ui->comboBox_operations->currentText();
    if (op_title == "не указано")
    {
        QMessageBox::warning(this, "добавление операции", "Укажите название операции");
        return;
    }
    operation_to_add->Set_Title(op_title);


    // getting surgeon name
    QString  surg_name = ui->comboBox_surgeons->currentText();
    operation_to_add->Set_Surgeon(surg_name);

    QSqlQuery* get_surg_id = new QSqlQuery(db_name);
    get_surg_id->prepare("SELECT surg_id FROM surgeons WHERE surg_name='"+surg_name+"'");
    get_surg_id->exec();
    get_surg_id->next();

    QString surg_id = get_surg_id->value(0).toString();



    // getting recovering days
    int rec_days = ui->horizontalSlider->value();
    QString rec_days_str = QString::number(rec_days);
    operation_to_add->Set_Rec_Days(rec_days);

    // getting patient age
    int pat_age = ui->horizontalSlider_pat_age->value();
    QString pat_age_str = QString::number(pat_age);

    Gender gender;
    QString gender_str;
    // getting patient gender
    if (ui->radioButton_gender_f->isChecked())
    {
        gender = Gender::FEMALE;
        gender_str = "ж";
    }
    else if (ui->radioButton_gender_m->isChecked())
    {
        gender = Gender::MALE;
        gender_str = "м";
    }
    else
    {
        QMessageBox::warning(this, "Добавление операции", "Укажите пол пациента");
        return;
    }

    Patient* patient = new Patient(gender, pat_age);
    operation_to_add->Set_Patient(patient);


    if (ui->comboBox_diagnosis->currentText() == "не указано")
    {
        QMessageBox::warning(this, "Добавление операции", "Укажите диагноз");
        return;
    }

    // checking sequela
    if (ui->checkBox->isChecked())
    {
        if (operation_to_add->Get_Sequela() == NULL)
        {
            QMessageBox::warning(this, "Добавление операции", "Укажите осложнение");
            return;
        }
    }

    // now we can insert the operation into db and then refresh viewing of operations
    // first we need to instert diagnosis and remember its id and type

    QString diagn_type = operation_to_add->Get_Diagnosis()->Get_Title();

    int ing_id = 0;
    int post_id = 0;
    int pr_id = 0;

    if (diagn_type == "паховая")
    {
        Inguinal_Hernia_LMF lmf = this->inguinalHerniaform->Get_Hernia()->Get_LMF();
        Inguinal_Hernia_PR pr = this->inguinalHerniaform->Get_Hernia()->Get_PR();
        Inguinal_Hernia_SIZE size = this->inguinalHerniaform->Get_Hernia()->Get_Size();

        // now we set strings so that we can add info in query
        QString lmf_str;
        switch(lmf)
        {
        case Inguinal_Hernia_LMF::L:
            lmf_str = "l";
            break;
        case Inguinal_Hernia_LMF::M:
            lmf_str = "m";
            break;
        case Inguinal_Hernia_LMF::F:
            lmf_str = "f";
            break;
        }

        QString pr_str;
        switch(pr)
        {
        case Inguinal_Hernia_PR::P:
            pr_str = "p";
            break;
        case Inguinal_Hernia_PR::R:
            pr_str = "r";
            break;
        }

        QString size_str;
        switch(size)
        {
        case Inguinal_Hernia_SIZE::S1:
            size_str = "s1";
            break;
        case Inguinal_Hernia_SIZE::S2:
            size_str = "s2";
            break;
        case Inguinal_Hernia_SIZE::S3:
            size_str = "s3";
            break;
        case Inguinal_Hernia_SIZE::S4:
            size_str = "s4";
            break;
        case Inguinal_Hernia_SIZE::S5:
            size_str = "s5";
            break;
        }

        QSqlQuery* add_ing_diagnosis_qry = new QSqlQuery(QSqlDatabase::database(db_name));

        add_ing_diagnosis_qry->prepare("INSERT INTO ing_diagnosis(ing_lmf, ing_pr, ing_size) VALUES(:lmf, :pr, :size)");
        add_ing_diagnosis_qry->bindValue(":lmf", lmf_str);
        add_ing_diagnosis_qry->bindValue(":pr", pr_str);
        add_ing_diagnosis_qry->bindValue(":size", size_str);
        add_ing_diagnosis_qry->exec();

        QSqlQuery* get_max_ing_id = new QSqlQuery(QSqlDatabase::database(db_name));
        get_max_ing_id->prepare("SELECT max(ing_id) from ing_diagnosis");
        get_max_ing_id->exec();
        get_max_ing_id->next();

        ing_id = get_max_ing_id->value(0).toInt();
        QString ing_id_str = QString::number(ing_id);

        // now we can set operation, because we created inguinal diagnosis and know its id in ing_id

        // but before this, we need to check whether sequela is null or not
         if (operation_to_add->Get_Sequela() == NULL)
         {
             // if sequela is null
             QSqlQuery* operation_add = new QSqlQuery(QSqlDatabase::database(db_name));

             operation_add->prepare("INSERT INTO operations(op_date, op_title, surg_id, op_rec_days, \
                                     pat_age, pat_gender, ing_id, diagn_title) VALUES(:date, :op_title, \
                                    :surg_id, :rec_days, :pat_age, :pat_gender, :ing_id, :diagn_title);");

             operation_add->bindValue(":date", date_str);
             operation_add->bindValue(":op_title", op_title);
             operation_add->bindValue(":surg_id", surg_id);
             operation_add->bindValue(":rec_days", rec_days_str);
             operation_add->bindValue(":pat_age", pat_age_str);
             operation_add->bindValue(":pat_gender", gender_str);
             operation_add->bindValue(":ing_id", ing_id_str);
             operation_add->bindValue(":diagn_title", diagn_type);


             if (operation_add->exec())
             {
                 QMessageBox::information(this, "Добавление операции", "Операция успешно добавлена");
             }
             else
             {
                 QMessageBox::warning(this, "Добавление операции", "Не удалось добавить операцию");
             }


         }
         else
         {
             // if sequela is not null
             QString seq_type = operation_to_add->Get_Sequela()->Get_Type();
             QString seq_title = operation_to_add->Get_Sequela()->Get_Title();

             QSqlQuery* operation_add = new QSqlQuery(QSqlDatabase::database(db_name));

             operation_add->prepare("INSERT INTO operations(op_date, op_title, surg_id, op_rec_days, \
                                     pat_age, pat_gender, ing_id, diagn_title, seq_type, seq_title) VALUES \
                                    (:date, :op_title, :surg_id, :rec_days, :pat_age, :pat_gender, :ing_id,\
                                     :diagn_title, :seq_type, :seq_title);");

             operation_add->bindValue(":date", date_str);
             operation_add->bindValue(":op_title", op_title);
             operation_add->bindValue(":surg_id", surg_id);
             operation_add->bindValue(":rec_days", rec_days_str);
             operation_add->bindValue(":pat_age", pat_age_str);
             operation_add->bindValue(":pat_gender", gender_str);
             operation_add->bindValue(":ing_id", ing_id_str);
             operation_add->bindValue(":diagn_title", diagn_type);
             operation_add->bindValue(":seq_type", seq_type);
             operation_add->bindValue(":seq_title", seq_title);


             if (operation_add->exec())
             {
                 QMessageBox::information(this, "Добавление операции", "Операция успешно добавлена");
             }
             else
             {
                 QMessageBox::warning(this, "Добавление операции", "Не удалось добавить операцию");
             }
         }



    }
    else if (diagn_type == "первичная")
    {
        Primary_Ventral_Hernia_Types type = this->pventralHerniaform->Get_Hernia()->Get_Type();
        Primary_Ventral_Hernia_SubTypes subtitle = this->pventralHerniaform->Get_Hernia()->Get_Subtitle();
        Primary_Ventral_Hernia_Sizes size = this->pventralHerniaform->Get_Hernia()->Get_Size();

        QString p_type;
        switch(type)
        {
        case Primary_Ventral_Hernia_Types::SIDE:
            p_type = "боковая";
            break;
        case Primary_Ventral_Hernia_Types::MIDDLE:
            p_type = "срединная";
            break;
        }

        QString p_subtitle;
        switch(subtitle)
        {
        case Primary_Ventral_Hernia_SubTypes::EPIGASTRIC:
            p_subtitle = "эпигистральная";
            break;
        case Primary_Ventral_Hernia_SubTypes::UMBICIAL:
            p_subtitle = "пупочная";
            break;
        case Primary_Ventral_Hernia_SubTypes::SPIGEL:
            p_subtitle = "спигелевой линии";
            break;
        case Primary_Ventral_Hernia_SubTypes::LUMBAR:
            p_subtitle = "поясничная";
            break;
        }

        QString p_size;
        switch(size)
        {
        case Primary_Ventral_Hernia_Sizes::SMALL:
            p_size = "малая";
            break;
        case Primary_Ventral_Hernia_Sizes::MEDIUM:
            p_size = "средняя";
            break;
        case Primary_Ventral_Hernia_Sizes::LARGE:
            p_size = "большая";
            break;
        }

        QSqlQuery* add_pr_diagnosis_qry = new QSqlQuery(QSqlDatabase::database(db_name));

        add_pr_diagnosis_qry->prepare("INSERT INTO pr_diagnosis(pr_type, pr_subtitle, pr_size) \
                                        VALUES(:pr_type, :pr_subtitle, :pr_size)");
        add_pr_diagnosis_qry->bindValue(":pr_type", p_type);
        add_pr_diagnosis_qry->bindValue(":pr_subtitle", p_subtitle);
        add_pr_diagnosis_qry->bindValue(":pr_size", p_size);


        if (add_pr_diagnosis_qry->exec())
            qDebug() << "success seq";

        QSqlQuery* get_max_pr_id = new QSqlQuery(QSqlDatabase::database(db_name));
        get_max_pr_id->prepare("SELECT max(pr_id) from pr_diagnosis");
        get_max_pr_id->exec();
        get_max_pr_id->next();

        pr_id = get_max_pr_id->value(0).toInt();
        QString pr_id_str = QString::number(pr_id);

        // now we can set operation, because we created primary diagnosis and know its id in pr_id

        // but before this, we need to check whether sequela is null or not
         if (operation_to_add->Get_Sequela() == NULL)
         {
             // if sequela is null
             QSqlQuery* operation_add = new QSqlQuery(QSqlDatabase::database(db_name));

             operation_add->prepare("INSERT INTO operations(op_date, op_title, surg_id, op_rec_days, \
                                     pat_age, pat_gender, pr_id, diagn_title) VALUES(:date, :op_title, \
                                    :surg_id, :rec_days, :pat_age, :pat_gender, :pr_id, :diagn_title);");

             operation_add->bindValue(":date", date_str);
             operation_add->bindValue(":op_title", op_title);
             operation_add->bindValue(":surg_id", surg_id);
             operation_add->bindValue(":rec_days", rec_days_str);
             operation_add->bindValue(":pat_age", pat_age_str);
             operation_add->bindValue(":pat_gender", gender_str);
             operation_add->bindValue(":pr_id", pr_id_str);
             operation_add->bindValue(":diagn_title", diagn_type);


             if (operation_add->exec())
             {
                 QMessageBox::information(this, "Добавление операции", "Операция успешно добавлена");
             }
             else
             {
                 QMessageBox::warning(this, "Добавление операции", "Не удалось добавить операцию");
             }


         }
         else
         {
             // if sequela is not null
             QString seq_type = operation_to_add->Get_Sequela()->Get_Type();
             QString seq_title = operation_to_add->Get_Sequela()->Get_Title();

             QSqlQuery* operation_add = new QSqlQuery(QSqlDatabase::database(db_name));

             operation_add->prepare("INSERT INTO operations(op_date, op_title, surg_id, op_rec_days, \
                                     pat_age, pat_gender, pr_id , diagn_title, seq_type, seq_title) VALUES \
                                    (:date, :op_title, :surg_id, :rec_days, :pat_age, :pat_gender, :pr_id,\
                                     :diagn_title, :seq_type, :seq_title);");

             operation_add->bindValue(":date", date_str);
             operation_add->bindValue(":op_title", op_title);
             operation_add->bindValue(":surg_id", surg_id);
             operation_add->bindValue(":rec_days", rec_days_str);
             operation_add->bindValue(":pat_age", pat_age_str);
             operation_add->bindValue(":pat_gender", gender_str);
             operation_add->bindValue(":pr_id", pr_id_str);
             operation_add->bindValue(":diagn_title", diagn_type);
             operation_add->bindValue(":seq_type", seq_type);
             operation_add->bindValue(":seq_title", seq_title);


             if (operation_add->exec())
             {
                 QMessageBox::information(this, "Добавление операции", "Операция успешно добавлена");
             }
             else
             {
                 QMessageBox::warning(this, "Добавление операции", "Не удалось добавить операцию");
             }
         }
    }
    else if (diagn_type == "послеоперационная")
    {
        Postoperative_Ventral_Hernia_L l = this->postVentralHerniaform->Get_Hernia()->Get_L();
        Postoperative_Ventral_Hernia_M m = this->postVentralHerniaform->Get_Hernia()->Get_M();
        Postoperative_Ventral_Hernia_R r = this->postVentralHerniaform->Get_Hernia()->Get_R();
        Postoperative_Ventral_Hernia_W w = this->postVentralHerniaform->Get_Hernia()->Get_W();

        QString l_str;
        switch(l)
        {
        case Postoperative_Ventral_Hernia_L::L1:
            l_str = "l1";
            break;
        case Postoperative_Ventral_Hernia_L::L2:
            l_str = "l2";
            break;
        case Postoperative_Ventral_Hernia_L::L3:
            l_str = "l3";
            break;
        case Postoperative_Ventral_Hernia_L::L4:
            l_str = "l4";
            break;
        }

        QString m_str;
        switch(m)
        {
        case Postoperative_Ventral_Hernia_M::M1:
            m_str = "m1";
            break;
        case Postoperative_Ventral_Hernia_M::M2:
            m_str = "m2";
            break;
        case Postoperative_Ventral_Hernia_M::M3:
            m_str = "m3";
            break;
        case Postoperative_Ventral_Hernia_M::M4:
            m_str = "m4";
            break;
        case Postoperative_Ventral_Hernia_M::M5:
            m_str = "m5";
            break;
        }

        QString w_str;
        switch(w)
        {
        case Postoperative_Ventral_Hernia_W::W1:
            w_str = "w1";
            break;
        case Postoperative_Ventral_Hernia_W::W2:
            w_str = "w2";
            break;
        case Postoperative_Ventral_Hernia_W::W3:
            w_str = "w3";
            break;
        }

        QString r_str;
        switch(r)
        {
        case Postoperative_Ventral_Hernia_R::R1:
            r_str = "r1";
            break;
        case Postoperative_Ventral_Hernia_R::R2:
            r_str = "r2";
            break;
        case Postoperative_Ventral_Hernia_R::R3:
            r_str = "r3";
            break;
        case Postoperative_Ventral_Hernia_R::R4:
            r_str = "r4";
            break;
        }
    }

    emit operation_added();
    this->close();
}

void OperationAddForm::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        ui->pushButton_sequela->setEnabled(true);
    }
    else
    {
        ui->pushButton_sequela->setEnabled(false);
    }
}

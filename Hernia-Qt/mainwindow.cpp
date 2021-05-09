#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QAbstractItemView>
#include <QInputDialog>

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // some settings with forms
    ui->setupUi(this);

    this->db = new DbManager("/home/dmkrch/Programming/Hernia-qt/Hernia-Qt/hernia.db");

    Set_Surgeons_Combobox();
    Set_Surgeons_List();
    Set_Operations_List();

    // dateform setup
    dateform = new DateForm();
    dateform->setModal(true);

    // sequenceform setup
    sequenceform = new SequenceForm();
    sequenceform->setModal(true);

    // inguinalform setup
    inguinalHerniaform = new InguinalHerniaForm();
    inguinalHerniaform->setModal(true);

    // pventralHerniaForm setup
    pventralHerniaform = new PVentralHerniaForm();
    pventralHerniaform->setModal(true);

    // post ventral hernia form setup
    postVentralHerniaform = new PostVentralHerniaForm();
    postVentralHerniaform->setModal(true);



    // creating toolbar with 2 options: statistics and editing
    toolbar = addToolBar("tool bar");
    QAction* statistics_tool = toolbar->addAction("О программе");
    toolbar->addSeparator();
    QAction* editing_tool = toolbar->addAction("Выход");


    // connecting slots to signals of toolbar
    connect(statistics_tool, &QAction::triggered, qApp, &QApplication::quit); // here i need to set showing statistics form
    connect(editing_tool, &QAction::triggered, qApp, &QApplication::quit); // here i need to set showing editing form



    // creating slider for days
    days_rSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, this);
    ui->verticalLayout_4->addWidget(days_rSlider);

    // creating slider for age
    age_rSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, this);
    ui->verticalLayout_8->addWidget(age_rSlider);

    // connecting lower value change of date range slider
    connect(days_rSlider, &RangeSlider::lowerValueChanged,
            this, &MainWindow::slider_date_lower_value_changed);

    // connecting higher value change of date range slider
    connect(days_rSlider, &RangeSlider::upperValueChanged,
            this, &MainWindow::slider_date_upper_value_changed);

    connect(age_rSlider, &RangeSlider::lowerValueChanged,
            this, &MainWindow::slider_age_lower_value_changed);

    connect(age_rSlider, &RangeSlider::upperValueChanged,
            this, &MainWindow::slider_age_upper_value_changed);


    // connecting calendar
    connect(dateform, SIGNAL(date_setted()), this, SLOT(set_date_edit()));


//    // adding surgeons
//    QStringList surgeons = {"----все хирурги----", "Кулага Сергей Алексеевич", "Кухта Андрей Викторович",
//                           "Карпович Вячеслав Евгеньевич", "Мещеня Антон Николаевич",
//                           "Лапковский Александр Александрович", "Щемелев Максим Юрьевич",
//                           "Бутома Николай Николаевич", "Изгачев Максим Павлович",
//                           "Панцевич Никита Юрьевич", "Толкин Юрий Олегович",
//                           "Пунько Алексей Николаевич"};

    ui->comboBox_surgeons->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_surgeons->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    ui->comboBox_surgeons->addItems(surgeons);


    // adding operations
    QStringList operations = {"----все операции----", "Постемпский", "Жиррару-Спасоккукоцкому", "Сапежко",
                              "Мейо", "Напалков", "Полиспасными швами", "SUBLAY",
                              "RIVES", "STOPPA", "RIVES-STOPPA-Wanz", "ONLAY",
                              "Novitsky", "TAR-technique", "Carbonelli", "Ramirez",
                              "IPOM", "IPOM+", "МILOS", "E MILOS", "E TEP"};

    ui->comboBox_op_names->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_op_names->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox_op_names->addItems(operations);


    // adding diagnosises
    QStringList diagnosises = {"----все диагнозы----","паховая грыжа", "первичная вентральная грыжа",
                               "послеоперационная вентральная грыжа"};

    ui->comboBox_diagnosis->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_diagnosis->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox_diagnosis->addItems(diagnosises);

    connect(ui->comboBox_diagnosis, &QComboBox::currentTextChanged, this, &MainWindow::open_diagnosis_form);


    // connecting sequela form closed
    connect(sequenceform, &SequenceForm::form_was_closed, this, &MainWindow::sequela_form_closed);


    // connecting inguinal form closed
    connect(inguinalHerniaform, &InguinalHerniaForm::form_was_closed, this,
            &MainWindow::inguinal_form_closed);

    // connecting postoperative ventral form closed
    connect(postVentralHerniaform, &PostVentralHerniaForm::form_was_closed, this,
            &MainWindow::post_ventral_form_closed);

    connect(pventralHerniaform, &PVentralHerniaForm::form_was_closed, this,
            &MainWindow::primary_ventral_form_closed);

    this->operation_to_find = new Operation_To_Find_Model();
}



// -------------PRIVATE SLOTS--------------------
void MainWindow::slider_date_lower_value_changed()
{
    int date_from = days_rSlider->GetLowerValue();
    ui->label_days_from->setText(QString::number(date_from));
}

void MainWindow::slider_date_upper_value_changed()
{
    int date_to = days_rSlider->GetUpperValue();
    ui->label_days_to->setText(QString::number(date_to));
}

void MainWindow::slider_age_lower_value_changed()
{
    int age_from = age_rSlider->GetLowerValue();
    ui->label_age_from->setText(QString::number(age_from));
}

void MainWindow::slider_age_upper_value_changed()
{
    int age_to = age_rSlider->GetUpperValue();
    ui->label_age_to->setText(QString::number(age_to));
}



void MainWindow::on_pushButton_from_clicked()
{
    is_date_from_pressed = true;
    dateform->show();
}

void MainWindow::on_pushButton_to_clicked()
{
    is_date_from_pressed = false;
    dateform->show();
}

void MainWindow::set_date_edit()
{
    QDate date = dateform->GetDate();

    if(is_date_from_pressed)
        ui->dateEdit_from->setDate(date);
    else
        ui->dateEdit_to->setDate(date);
}

void MainWindow::open_diagnosis_form(QString diagnosis_type)
{
    if (diagnosis_type == "----все диагнозы----")
    {
        this->operation_to_find->diagnosis = new Diagnosis("----все диагнозы----");
        ui->label_diagnosis->setText("Диагноз: " + this->operation_to_find->diagnosis->Get_String());
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

void MainWindow::sequela_form_closed()
{
    operation_to_find->sequela = sequenceform->Get_Sequela();

    QString type = operation_to_find->sequela->Get_Type();
    QString title = operation_to_find->sequela->Get_Title();

    if (title != "")
        ui->label_sequence->setText("Осложнение: " + title);
    else
        ui->label_sequence->setText("Осложнение: " + type);
}

void MainWindow::inguinal_form_closed()
{
    operation_to_find->diagnosis = inguinalHerniaform->Get_Hernia();

    QString result = this->operation_to_find->diagnosis->Get_String();
    ui->label_diagnosis->setText("Диагноз: " + result);
}

void MainWindow::post_ventral_form_closed()
{
    operation_to_find->diagnosis = postVentralHerniaform->Get_Hernia();

    QString result = this->operation_to_find->diagnosis->Get_String();
    ui->label_diagnosis->setText("Диагноз: " + result);
}

void MainWindow::primary_ventral_form_closed()
{
    operation_to_find->diagnosis = pventralHerniaform->Get_Hernia();

    QString result = this->operation_to_find->diagnosis->Get_String();
    ui->label_diagnosis->setText("Диагноз: " + result);
}


// -------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_sequence_clicked()
{
    sequenceform->show();
}


void MainWindow::on_pushButton_search_op_clicked()
{
    // date
    QDate date_from = ui->dateEdit_from->date();
    QDate date_to = ui->dateEdit_to->date();

    // title of operation
    QString op_title = ui->comboBox_op_names->currentText();

    // name of surgeon
    QString surgeon_name = ui->comboBox_surgeons->currentText();

    // sequence already setted in mainform->sequenceform

    // recovering days
    int days_from = ui->label_days_from->text().toInt();
    int days_to = ui->label_days_to->text().toInt();

    // gender
    Gender g;

    if (ui->checkBox_male->isChecked() && !ui->checkBox_female->isChecked())
        g = Gender::MALE;
    else if (!ui->checkBox_male->isChecked() && ui->checkBox_female->isChecked())
        g = Gender::FEMALE;
    else if (ui->checkBox_male->isChecked() && ui->checkBox_female->isChecked())
        g = Gender::ANY_MALE;


    // age of patient
    int age_from = ui->label_age_from->text().toInt();
    int age_to = ui->label_age_to->text().toInt();

    // diagnosis already setted in mainwindow->diagnosis


//    ui->listWidget_output->addItem(date_from.toString());
//    ui->listWidget_output->addItem(date_to.toString());
//    ui->listWidget_output->addItem(op_title);
//    ui->listWidget_output->addItem(surgeon_name);
//    ui->listWidget_output->addItem(QString::number(days_from));
//    ui->listWidget_output->addItem(QString::number(days_to));
//    ui->listWidget_output->addItem(operation_to_find->sequela->Get_Type() + operation_to_find->sequela->Get_Title());
//    ui->listWidget_output->addItem("diagnosis: " + this->operation_to_find->diagnosis->Get_String());
//    ui->listWidget_output->addItem("sequela: " + this->operation_to_find->sequela->Get_Title() +
//                                   this->operation_to_find->sequela->Get_Type());
}

void MainWindow::on_pushButton_add_surgeon_clicked()
{
    // here i need to add surgeon to db
    // and then refresh all information

    QString c_text = QInputDialog::getText(this, "Добавление хирурга", "Введите имя хирурга");
    QString s_text = c_text.simplified();

    if (!s_text.isEmpty())
    {
        db->addSurgeon(s_text);
        // add to bd
        Set_Surgeons_List();
        Set_Surgeons_Combobox();
    }
}

void MainWindow::Set_Surgeons_Combobox()
{
    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(db->m_db);

    qry->prepare("select surg_name from surgeons;");
    qry->exec();
    modal->setQuery(*qry);
    ui->comboBox_surgeons->setModel(modal);
    qDebug() << modal->rowCount();
}

void MainWindow::Set_Surgeons_List()
{
    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(db->m_db);

    qry->prepare("select surg_name from surgeons;");
    qry->exec();
    modal->setQuery(*qry);
    ui->listView_surgeons->setModel(modal);
    qDebug() << modal->rowCount();
}

void MainWindow::Set_Operations_List()
{
    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(db->m_db);

    qry->prepare("SELECT \
                 op_date as \"дата операции\", \
                 op_title as \"название операции\", \
                 surg_name as \"имя хирурга\", \
                 op_rec_days as \"койко-дни\", \
                 op_pat_gender as \"пол пациента\", \
                 op_pat_age as \"возраст пациента\",\
                 diagnosises.ing_id,\
                 diagnosises.post_id,\
                 diagnosises.pr_id\
             FROM \
                 operations\
             INNER JOIN surgeons\
                 ON surgeons.surg_id = operations.surg_id\
             INNER JOIN diagnosises\
                 ON diagnosises.diagn_id = operations.diagn_id");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView_operations->setModel(modal);
    qDebug() << modal->rowCount();
}

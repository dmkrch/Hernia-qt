#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QAbstractItemView>
#include <QInputDialog>

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>

#include <QHeaderView>
#include <QDebug>

#include <QMessageBox>

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

    operationAddform = new OperationAddForm(this);
    operationAddform->setModal(true);

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
    days_rSlider->SetMaximum(200);

    // creating slider for age
    age_rSlider = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, this);
    ui->verticalLayout_8->addWidget(age_rSlider);
    age_rSlider->setMinimum(1);
    age_rSlider->setMaximum(120);

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


    // adding surgeons
    ui->comboBox_surgeons->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_surgeons->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);


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

    connect(operationAddform, &OperationAddForm::operation_added, this, &MainWindow::Set_Operations_List);
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
    // checking sequela
    if (operation_to_find->sequela == NULL && ui->checkBox->isChecked())
    {
        QMessageBox::warning(this, "Поиск операций", "Укажите осложнение");
        return;
    }

    // checking gender
    if (!ui->checkBox_male->isChecked() && !ui->checkBox_female->isChecked())
    {
        QMessageBox::warning(this, "Поиск операций", "Укажите пол");
    }

    // now everyting is fine and we can build our request to db

    QDate date_from = ui->dateEdit_from->date();
    QDate date_to = ui->dateEdit_to->date();

    QString date_str_from = date_from.toString("yyyy-MM-dd");
    QString date_str_to = date_to.toString("yyyy-MM-dd");

    QString age_str_from = QString::number(this->age_rSlider->GetLowerValue());
    QString age_str_to = QString::number(this->age_rSlider->GetUpperValue());

    QString rec_days_from = QString::number(this->days_rSlider->GetLowerValue());
    QString rec_days_to = QString::number(this->days_rSlider->GetUpperValue());

    QString test;

    QSqlQuery* search_qry = new QSqlQuery(db->m_db);
    QString search_str = "SELECT \
                            op_id, \
                            op_date, \
                            surg_name, \
                            op_title, \
                            pat_gender, \
                            pat_age, \
                            seq_type, \
                            seq_title, \
                            diagn_title, \
                            op_rec_days \
                          FROM operations \
                          INNER JOIN surgeons on surgeons.surg_id=operations.surg_id \
                          WHERE 	(op_date BETWEEN '"+date_str_from+"' AND '"+date_str_to+"') AND \
                                    (pat_age BETWEEN '"+age_str_from+"' AND '"+age_str_to+"') AND \
                                    (op_rec_days BETWEEN '"+rec_days_from+"' AND '"+rec_days_to+"')";

    search_qry->prepare(search_str);
    if(search_qry->exec())
    {
        qDebug() << "asfdasfd";
    }

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
        operationAddform->Set_Surgeons_List();
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
}

void MainWindow::Set_Surgeons_List()
{
    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery* qry = new QSqlQuery(db->m_db);

    qry->prepare("select surg_name from surgeons;");
    qry->exec();
    modal->setQuery(*qry);
    ui->listView_surgeons->setModel(modal);
}

void MainWindow::Set_Operations_List()
{
    ui->tableWidget_operations->setRowCount(0);

    QSqlQuery* qry = new QSqlQuery(db->m_db);

    qry->prepare("SELECT op_id,\
                 op_date,\
                 surg_name, \
                 op_title,\
                 pat_gender, \
                 pat_age, \
                 seq_type, \
                 seq_title,  \
                 diagn_title, \
                 ing_lmf,\
                 ing_pr, \
                 ing_size, \
                 op_rec_days \
          FROM operations\
          INNER JOIN surgeons on surgeons.surg_id=operations.surg_id \
          INNER JOIN ing_diagnosis on ing_diagnosis.ing_id = operations.ing_id");
    if (qry->exec())
    {
        while(qry->next())
        {
            int row_count = ui->tableWidget_operations->rowCount();

            ui->tableWidget_operations->insertRow(row_count);

            QTableWidgetItem* op_id = new QTableWidgetItem;
            QTableWidgetItem* op_date = new QTableWidgetItem;
            QTableWidgetItem* surg_name = new QTableWidgetItem;
            QTableWidgetItem* op_title = new QTableWidgetItem;
            QTableWidgetItem* pat_gender = new QTableWidgetItem;
            QTableWidgetItem* pat_age = new QTableWidgetItem;
            QTableWidgetItem* seq = new QTableWidgetItem;
            QTableWidgetItem* diagnosis = new QTableWidgetItem;
            QTableWidgetItem* rec_days = new QTableWidgetItem;

            op_id->setText(qry->value(0).toString());
            op_date->setText(qry->value(1).toString());
            surg_name->setText(qry->value(2).toString());
            op_title->setText(qry->value(3).toString());
            pat_gender->setText(qry->value(4).toString());
            pat_age->setText(qry->value(5).toString());
            seq->setText(qry->value(6).toString() + " " + qry->value(7).toString());
            diagnosis->setText(qry->value(8).toString() + " " + qry->value(9).toString() + " " + qry->value(10).toString()
                               + " " + qry->value(11).toString());
            rec_days->setText(qry->value(12).toString());

            ui->tableWidget_operations->setItem(row_count, 0, op_id);
            ui->tableWidget_operations->setItem(row_count, 1, op_date);
            ui->tableWidget_operations->setItem(row_count, 2, surg_name);
            ui->tableWidget_operations->setItem(row_count, 3, op_title);
            ui->tableWidget_operations->setItem(row_count, 4, pat_gender);
            ui->tableWidget_operations->setItem(row_count, 5, pat_age);
            ui->tableWidget_operations->setItem(row_count, 6, seq);
            ui->tableWidget_operations->setItem(row_count, 7, diagnosis);
            ui->tableWidget_operations->setItem(row_count, 8, rec_days);
        }
    }

    QSqlQuery* qry1 = new QSqlQuery(db->m_db);
    qry1->prepare("SELECT op_id,\
                 op_date,\
                 surg_name, \
                 op_title,\
                 pat_gender, \
                 pat_age, \
                 seq_type, \
                 seq_title,  \
                 diagn_title, \
                 post_m,\
                 post_l, \
                 post_w, \
                 post_r, \
                 op_rec_days \
          FROM operations\
          INNER JOIN surgeons on surgeons.surg_id=operations.surg_id \
          INNER JOIN post_diagnosis on post_diagnosis.post_id = operations.post_id");

    if (qry1->exec())
    {
        while(qry1->next())
        {
            int row_count = ui->tableWidget_operations->rowCount();

            ui->tableWidget_operations->insertRow(row_count);

            QTableWidgetItem* op_id = new QTableWidgetItem;
            QTableWidgetItem* op_date = new QTableWidgetItem;
            QTableWidgetItem* surg_name = new QTableWidgetItem;
            QTableWidgetItem* op_title = new QTableWidgetItem;
            QTableWidgetItem* pat_gender = new QTableWidgetItem;
            QTableWidgetItem* pat_age = new QTableWidgetItem;
            QTableWidgetItem* seq = new QTableWidgetItem;
            QTableWidgetItem* diagnosis = new QTableWidgetItem;
            QTableWidgetItem* rec_days = new QTableWidgetItem;

            op_id->setText(qry1->value(0).toString());
            op_date->setText(qry1->value(1).toString());
            surg_name->setText(qry1->value(2).toString());
            op_title->setText(qry1->value(3).toString());
            pat_gender->setText(qry1->value(4).toString());
            pat_age->setText(qry1->value(5).toString());
            seq->setText(qry1->value(6).toString() + " " + qry1->value(7).toString());
            diagnosis->setText(qry1->value(8).toString() + " " + qry1->value(9).toString() + " " +
                               qry1->value(10).toString() + " " + qry1->value(11).toString() + " " +
                               qry1->value(12).toString());

            rec_days->setText(qry1->value(13).toString());

            ui->tableWidget_operations->setItem(row_count, 0, op_id);
            ui->tableWidget_operations->setItem(row_count, 1, op_date);
            ui->tableWidget_operations->setItem(row_count, 2, surg_name);
            ui->tableWidget_operations->setItem(row_count, 3, op_title);
            ui->tableWidget_operations->setItem(row_count, 4, pat_gender);
            ui->tableWidget_operations->setItem(row_count, 5, pat_age);
            ui->tableWidget_operations->setItem(row_count, 6, seq);
            ui->tableWidget_operations->setItem(row_count, 7, diagnosis);
            ui->tableWidget_operations->setItem(row_count, 8, rec_days);
        }
    }
    QSqlQuery* qry2 = new QSqlQuery(db->m_db);
    qry2->prepare("SELECT op_id,\
                 op_date,\
                 surg_name, \
                 op_title,\
                 pat_gender, \
                 pat_age, \
                 seq_type, \
                 seq_title,  \
                 diagn_title, \
                 pr_type,\
                 pr_subtitle, \
                 pr_size, \
                 op_rec_days \
          FROM operations\
          INNER JOIN surgeons on surgeons.surg_id=operations.surg_id \
          INNER JOIN pr_diagnosis on pr_diagnosis.pr_id = operations.pr_id");

    if (qry2->exec())
    {
        while(qry2->next())
        {
            int row_count = ui->tableWidget_operations->rowCount();

            ui->tableWidget_operations->insertRow(row_count);

            QTableWidgetItem* op_id = new QTableWidgetItem;
            QTableWidgetItem* op_date = new QTableWidgetItem;
            QTableWidgetItem* surg_name = new QTableWidgetItem;
            QTableWidgetItem* op_title = new QTableWidgetItem;
            QTableWidgetItem* pat_gender = new QTableWidgetItem;
            QTableWidgetItem* pat_age = new QTableWidgetItem;
            QTableWidgetItem* seq = new QTableWidgetItem;
            QTableWidgetItem* diagnosis = new QTableWidgetItem;
            QTableWidgetItem* rec_days = new QTableWidgetItem;

            op_id->setText(qry2->value(0).toString());
            op_date->setText(qry2->value(1).toString());
            surg_name->setText(qry2->value(2).toString());
            op_title->setText(qry2->value(3).toString());
            pat_gender->setText(qry2->value(4).toString());
            pat_age->setText(qry2->value(5).toString());
            seq->setText(qry2->value(6).toString() + " " + qry2->value(7).toString());
            diagnosis->setText(qry2->value(8).toString() + " " + qry2->value(9).toString() + " " +
                               qry2->value(10).toString() + qry2->value(11).toString());

            rec_days->setText(qry2->value(12).toString());

            ui->tableWidget_operations->setItem(row_count, 0, op_id);
            ui->tableWidget_operations->setItem(row_count, 1, op_date);
            ui->tableWidget_operations->setItem(row_count, 2, surg_name);
            ui->tableWidget_operations->setItem(row_count, 3, op_title);
            ui->tableWidget_operations->setItem(row_count, 4, pat_gender);
            ui->tableWidget_operations->setItem(row_count, 5, pat_age);
            ui->tableWidget_operations->setItem(row_count, 6, seq);
            ui->tableWidget_operations->setItem(row_count, 7, diagnosis);
            ui->tableWidget_operations->setItem(row_count, 8, rec_days);
        }
    }
}

void MainWindow::on_pushButton_delete_op_clicked()
{
    // here i need to delete operation by its id from db
    // and then refresh all information about operations

    QString c_text = QInputDialog::getText(this, "Удаление операции", "Введите номер операции");
    QString op_id = c_text.simplified(); // we got id of operation

    if (!op_id.isEmpty())
    {
        QSqlQuery qry_count_op;
        qry_count_op.prepare("SELECT COUNT(*) FROM operations WHERE op_id='"+op_id+"'");
        qry_count_op.exec();

        qry_count_op.next();

        int count = qry_count_op.value(0).toInt();

        if (count == 1) // if operation exists with such id
        {
            QSqlQuery qry_find_diagnosis;
            qry_find_diagnosis.prepare("select ing_id, post_id, pr_id from operations where op_id='"+op_id+"'");
            qry_find_diagnosis.exec();
            qry_find_diagnosis.next();

            int ing_id = qry_find_diagnosis.value(0).toInt();
            int post_id = qry_find_diagnosis.value(1).toInt();
            int pr_id = qry_find_diagnosis.value(2).toInt();

            // now deleting diagnosis
            if (ing_id != 0)
            {
                QSqlQuery qry_delete_ing;
                qry_delete_ing.prepare("DELETE FROM ing_diagnosis WHERE ing_id='"+QString::number(ing_id)+"'");
                qry_delete_ing.exec();
            }
            else if (post_id != 0)
            {
                QSqlQuery qry_delete_post;
                qry_delete_post.prepare("DELETE FROM post_diagnosis WHERE post_id='"+QString::number(post_id)+"'");
                qry_delete_post.exec();
            }
            else if (pr_id != 0)
            {
                QSqlQuery qry_delete_pr;
                qry_delete_pr.prepare("DELETE FROM pr_diagnosis WHERE pr_id='"+QString::number(pr_id)+"'");
                qry_delete_pr.exec();
            }


            // now deleting operation
            QSqlQuery qry1;
            qry1.prepare("DELETE FROM operations WHERE op_id='"+op_id+"'");

            if(qry1.exec())
            {
                QMessageBox::information(this, "Удаление операции", "Удаление прошло успешно");
                Set_Operations_List();
            }
            else
            {
                QMessageBox::warning(this, "Удаление операции", "Не удалось удалить операцию");
            }
        }
        else
        {
            QMessageBox::warning(this, "Удаление операции", "Не существует операции с заданным номером");
        }
    }




}

void MainWindow::on_pushButton_add_new_op_clicked()
{
    operationAddform->show();
}
void MainWindow::on_checkBox_clicked(bool checked)
{

    if (checked)
    {
        ui->pushButton_sequence->setEnabled(true);
    }
    else
    {
        ui->pushButton_sequence->setEnabled(false);
    }
}

void MainWindow::on_checkBox_2_clicked(bool checked)
{
    if (checked)
    {
        ui->comboBox_surgeons->setEnabled(false);
    }
    else
    {
        ui->comboBox_surgeons->setEnabled(true);
    }
}

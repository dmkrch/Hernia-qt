#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // some settings with forms
    ui->setupUi(this);

    // dateform setup
    dateform = new DateForm();
    dateform->setModal(true);

    // sequenceform setup
    sequenceform = new SequenceForm();
    sequenceform->setModal(true);

    // inguinanform setup
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
    QAction* statistics_tool = toolbar->addAction("Статистика");
    toolbar->addSeparator();
    QAction* editing_tool = toolbar->addAction("Редактирование");

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


    // adding surgeons
    QStringList surgeons = {"----все хирурги----", "Кулага Сергей Алексеевич", "Кухта Андрей Викторович",
                           "Карпович Вячеслав Евгеньевич", "Мещеня Антон Николаевич",
                           "Лапковский Александр Александрович", "Щемелев Максим Юрьевич",
                           "Бутома Николай Николаевич", "Изгачев Максим Павлович",
                           "Панцевич Никита Юрьевич", "Толкин Юрий Олегович",
                           "Пунько Алексей Николаевич"};

    ui->comboBox_surgeons->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_surgeons->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox_surgeons->addItems(surgeons);


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

    connect(ui->comboBox_diagnosis, &QComboBox::currentTextChanged, this, &MainWindow::set_diagnosis);



    // connecting sequela form closed
    connect(sequenceform, &SequenceForm::form_was_closed, this, &MainWindow::sequela_form_closed);


    // connecting diagnosis form closed

}



// -------------PRIVATE SLOTS--------------------
void MainWindow::slider_date_lower_value_changed()
{
    int date_from = days_rSlider->GetLowerValue();
    ui->label_date_from->setText(QString::number(date_from));
}

void MainWindow::slider_date_upper_value_changed()
{
    int date_to = days_rSlider->GetUpperValue();
    ui->label_date_to->setText(QString::number(date_to));
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

void MainWindow::set_diagnosis(QString diagnosis_type)
{
    if (diagnosis_type == "паховая грыжа")
        inguinalHerniaform->show();
    else if (diagnosis_type == "первичная вентральная грыжа")
        pventralHerniaform->show();
    else if (diagnosis_type == "послеоперационная вентральная грыжа")
        postVentralHerniaform->show();
}

void MainWindow::sequela_form_closed()
{

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

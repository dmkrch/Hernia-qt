#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // some settings with forms
    ui->setupUi(this);
    dateform = new DateForm();
    dateform->setModal(true);


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


    QStringList distros = {"Arch", "Xubuntu", "Redhat", "Debian",
          "Mandriva", "Hello", "Hello world how are you?", "ok",
          "asdfasfd", "asfdfhsgfsaf", "asfdgfhsrydhfhdg", "sagh"};


    ui->comboBox_surgeons->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_surgeons->addItems(distros);
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

// -------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

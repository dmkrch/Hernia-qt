#include "sequenceform.h"
#include "ui_sequenceform.h"
#include <QAbstractItemView>


SequenceForm::SequenceForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SequenceForm)
{
    ui->setupUi(this);

    only_concrete = false;

    sequela = new Sequela();

    QStringList seq_types = {"----любое осложнение----", "интраоперационное", "послеоперационное"};
    ui->comboBox_seq_type->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_seq_type->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox_seq_type->addItems(seq_types);

    connect(ui->comboBox_seq_type, &QComboBox::currentTextChanged, this, &SequenceForm::set_seq_type);
}

void SequenceForm::Set_Only_Concrete()
{
    ui->comboBox_seq_type->removeItem(0);
    ui->comboBox_seq_name->removeItem(0);
    only_concrete = true;
}

void SequenceForm::set_seq_type(QString seq_type)
{
    if (seq_type == "не указано")
    {
        ui->comboBox_seq_name->clear();
    }


    else if(seq_type == "интраоперационное")
    {
        if (!only_concrete)
        {
            QStringList intr_seq_names = {"--любое интрооперационное--", "кровотечение",
                                      "перфорация полого органа", "конверсия в открытую"};
            ui->comboBox_seq_name->clear();
            ui->comboBox_seq_name->addItems(intr_seq_names);
        }
        else
        {
            QStringList intr_seq_names = {"кровотечение", "перфорация полого органа",
                                          "конверсия в открытую"};
            ui->comboBox_seq_name->clear();
            ui->comboBox_seq_name->addItems(intr_seq_names);
        }
    }
    else if(seq_type == "послеоперационное")
    {
        if (!only_concrete)
        {
            QStringList post_seq_names = {"--любое послеоперационное--", "внутрибрюшое кровотечение ",
                                      "ранняя спаечная непроходимость", "перитонит", "повреждение полого органа",
                                      "нагноение раны", "серома послеоперационной раны", "гематома раны ",
                                      "ранний рецидив", "поздний рецидив", "лигатурный свищ"};
            ui->comboBox_seq_name->clear();
            ui->comboBox_seq_name->addItems(post_seq_names);
        }
        else
        {
            QStringList post_seq_names = {"внутрибрюшое кровотечение ",
                                      "ранняя спаечная непроходимость", "перитонит", "повреждение полого органа",
                                      "нагноение раны", "серома послеоперационной раны", "гематома раны ",
                                      "ранний рецидив", "поздний рецидив", "лигатурный свищ"};
            ui->comboBox_seq_name->clear();
            ui->comboBox_seq_name->addItems(post_seq_names);
        }
    }
}


SequenceForm::~SequenceForm()
{
    delete ui;
}

void SequenceForm::on_pushButton_clicked()
{
    sequela->Set_Type(ui->comboBox_seq_type->currentText());

    if (sequela->Get_Type() == "----любое осложнение----")
        sequela->Set_Title("");

    if (ui->comboBox_seq_type->currentText() != "----любое осложнение----")
        sequela->Set_Title(ui->comboBox_seq_name->currentText());

    emit form_was_closed();
    this->close();
}


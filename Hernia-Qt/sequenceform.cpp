#include "sequenceform.h"
#include "ui_sequenceform.h"
#include <QAbstractItemView>


SequenceForm::SequenceForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SequenceForm)
{
    ui->setupUi(this);

    QStringList seq_types = {"----любое осложнение----", "интраоперационное", "послеоперационное"};
    ui->comboBox_seq_type->setStyleSheet("combobox-popup: 0;");
    ui->comboBox_seq_type->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->comboBox_seq_type->addItems(seq_types);

    connect(ui->comboBox_seq_type, &QComboBox::currentTextChanged, this, &SequenceForm::set_seq_names);
}

void SequenceForm::set_seq_names(QString seq_type)
{
    if (seq_type == "----любое осложнение----")
    {   ui->comboBox_seq_name->clear();

    }
    else if(seq_type == "интраоперационное")
    {
        QStringList intr_seq_names = {"--любое интрооперационное осложнение--", "кровотечение",
                                      "перфорация полого органа", "конверсия в открытую"};
        ui->comboBox_seq_name->clear();
        ui->comboBox_seq_name->addItems(intr_seq_names);
    }
    else if(seq_type == "послеоперационное")
    {
        QStringList post_seq_names = {"--любое постоперационное осложнение--", "внутрибрюшое кровотечение ",
                                      "ранняя спаечная непроходимость", "перитонит", "повреждение полого органа",
                                      "нагноение раны", "серома послеоперационной раны", "гематома раны ",
                                      "ранний рецидив", "поздний рецидив", "лигатурный свищ"};
        ui->comboBox_seq_name->clear();
        ui->comboBox_seq_name->addItems(post_seq_names);
    }
}

SequenceForm::~SequenceForm()
{
    delete ui;
}

void SequenceForm::on_pushButton_clicked()
{
    this->close();
}

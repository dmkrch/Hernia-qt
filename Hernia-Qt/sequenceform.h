#ifndef SEQUENCEFORM_H
#define SEQUENCEFORM_H

#include <QDialog>
#include "classes_model/sequela.h"

namespace Ui {
class SequenceForm;
}

class SequenceForm : public QDialog
{
    Q_OBJECT
signals:
    void form_was_closed();

public:
    explicit SequenceForm(QWidget *parent = nullptr);
    Sequela* Get_Sequela() { return sequela; }
    ~SequenceForm();

private slots:
    void set_seq_type(QString seq_type);
    void on_pushButton_clicked();

private:
    Sequela* sequela;
    Ui::SequenceForm *ui;
};

#endif // SEQUENCEFORM_H

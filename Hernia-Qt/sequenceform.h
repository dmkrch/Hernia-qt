#ifndef SEQUENCEFORM_H
#define SEQUENCEFORM_H

#include <QDialog>

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
    enum class SequelaType { ANY_SEQ_TYPE, POSTOP_SEQ, INTROP_SEQ };
    ~SequenceForm();

private slots:
    void set_seq_names(QString seq_type);

    void on_pushButton_clicked();

private:
    Ui::SequenceForm *ui;
};

#endif // SEQUENCEFORM_H

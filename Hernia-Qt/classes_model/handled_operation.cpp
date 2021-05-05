#include "handled_operation.h"

Handled_Operation::Handled_Operation(Patient* p, QDate d,
        Sequela* seq, QString t, int days) : patient(p),
            date(d), sequela(seq), op_title(t), recovering_days(days) {}


Handled_Operation::Handled_Operation(const Handled_Operation& op)
{
    this->date = op.date;
    this->op_title = op.op_title;
    this->patient = op.patient;
    this->recovering_days = op.recovering_days;
    this->sequela = new Sequela(op.sequela->Get_Title());
}

Handled_Operation::~Handled_Operation()
{
    delete sequela;
    delete patient;
}

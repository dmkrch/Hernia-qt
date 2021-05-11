#include "handled_operation.h"

Handled_Operation::Handled_Operation(const Handled_Operation& op)
{
    this->date = op.date;
    this->op_title = op.op_title;
    this->patient = op.patient;
    this->recovering_days = op.recovering_days;
    this->sequela = new Sequela();
    this->sequela->Set_Title(op.sequela->Get_Title());
}

Handled_Operation::~Handled_Operation()
{
    delete sequela;
    delete patient;
}

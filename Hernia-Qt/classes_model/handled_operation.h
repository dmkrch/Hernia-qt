#ifndef HANDLED_OPERATION_SENTRY
#define HANDLED_OPERATION_SENTRY

#include "patient.h"
#include "sequela.h"
#include "diagnosis.h"
#include <QDate>

class Handled_Operation
{
public:
    Handled_Operation() {}

    Handled_Operation(const Handled_Operation& op);
    
    Patient* Get_Patient() { return patient; }
    QDate Get_Date() { return date; }
    Sequela* Get_Sequela() { return sequela; }
    QString Get_Title() { return op_title; }
    int Get_Rec_Days() { return recovering_days; }
    QString Get_Surgeon() { return surgeon; }

    void Set_Sequela(Sequela* seq) { this->sequela = seq; }

    ~Handled_Operation();
    
private:
    QString surgeon;
    Patient* patient;
    QDate date;
    Sequela* sequela;
    QString op_title;
    int recovering_days;
};


#endif

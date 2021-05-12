#ifndef HANDLED_OPERATION_SENTRY
#define HANDLED_OPERATION_SENTRY

#include "patient.h"
#include "sequela.h"
#include "diagnosis.h"
#include <QDate>

class Handled_Operation
{
public:
    Handled_Operation();

    Handled_Operation(const Handled_Operation& op);
    
    Patient* Get_Patient() { return patient; }
    QDate Get_Date() { return date; }
    Sequela* Get_Sequela() { return sequela; }
    QString Get_Title() { return op_title; }
    int Get_Rec_Days() { return recovering_days; }
    QString Get_Surgeon() { return surgeon; }
    Diagnosis* Get_Diagnosis() { return diagnosis; }

    void Set_Sequela(Sequela* seq) { this->sequela = seq; }
    void Set_Diagnosis(Diagnosis* d) { this->diagnosis = d; }
    void Set_Patient(Patient* p) { this->patient = p; }
    void Set_Date(QDate date) { this->date = date; }
    void Set_Title(QString t) { this->op_title = t; }
    void Set_Rec_Days(int days) { this->recovering_days = days; }
    void Set_Surgeon(QString s) { this->surgeon = s; }

    ~Handled_Operation();
    
private:
    QString surgeon;
    Patient* patient;
    QDate date;
    Sequela* sequela;
    QString op_title;
    int recovering_days;
    Diagnosis* diagnosis;
};


#endif

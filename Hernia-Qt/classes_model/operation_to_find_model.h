#ifndef OPERATION_TO_FIND_MODEL_SENTRY
#define OPERATION_TO_FIND_MODE_SENTRY

#include "patient.h"
#include "diagnosis.h"
#include "sequela.h"
#include <QString>
#include <QDate>

class Operation_To_Find_Model
{
public: 
    Operation_To_Find_Model(Gender g, int af, int at,
         QDate dat, QString sn, QString op_title,
        int rec_df, int rec_dt) :
            gender(g), age_from(af), age_to(at),
            date(dat), surgeon_name(sn), operation_title(op_title), 
            recovering_days_from(rec_df), recovering_days_to(rec_dt) {}

    Operation_To_Find_Model()
    {
        diagnosis = NULL;
        sequela = NULL;
    }
            

    Gender gender;
    int age_from;
    int age_to;
    QDate date;
    QString surgeon_name;
    Diagnosis* diagnosis;
    Sequela* sequela;
    QString operation_title;
    int recovering_days_from;
    int recovering_days_to;
};




#endif

#include "diagnosis.h"


Diagnosis::Diagnosis(QString t) : title(t) {}



Inguinal_Hernia::Inguinal_Hernia(QString t) : Diagnosis(t)
{
    this->lmf = Inguinal_Hernia_LMF::ANY_LMF;
    this->pr = Inguinal_Hernia_PR::ANY_PR;
    this->size = Inguinal_Hernia_SIZE::ANY_INGUINAL_SIZE;
}

QString Inguinal_Hernia::Get_String()
{
    QString result_str;

    result_str += this->Get_Title();
    result_str += " ";

    switch(this->Get_PR())
    {
    case ANY_PR:
        result_str += "PR";
        break;

    case P:
        result_str += "P";
        break;

    case R:
        result_str += "R";
        break;
    }

    result_str += ", ";

    switch(this->Get_LMF())
    {
    case ANY_LMF:
        result_str += "LMF";
        break;

    case L:
        result_str += "L";
        break;
    case M:
        result_str += "M";
        break;
    case F:
        result_str += "F";
        break;
    }

    result_str += ", ";
    switch(this->Get_Size())
    {
    case ANY_INGUINAL_SIZE:
        result_str += "S-12345";
        break;
    case S1:
        result_str += "S-1";
        break;
    case S2:
        result_str += "S-2";
        break;
    case S3:
        result_str += "S-3";
        break;
    case S4:
        result_str += "S-4";
        break;
    case S5:
        result_str += "S-5";
        break;
    }

    return result_str;
}



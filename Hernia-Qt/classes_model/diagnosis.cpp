#include "diagnosis.h"


Diagnosis::Diagnosis(QString t) : title(t) {}



Inguinal_Hernia::Inguinal_Hernia(QString t) : Diagnosis(t)
{
    this->lmf = Inguinal_Hernia_LMF::ANY_LMF;
    this->pr = Inguinal_Hernia_PR::ANY_PR;
    this->size = Inguinal_Hernia_SIZE::ANY_INGUINAL_SIZE;
}

Postoperative_Ventral_Hernia::Postoperative_Ventral_Hernia(QString t) : Diagnosis(t)
{
    this->m = Postoperative_Ventral_Hernia_M::ANY_M;
    this->l = Postoperative_Ventral_Hernia_L::ANY_L;
    this->w = Postoperative_Ventral_Hernia_W::ANY_W;
    this->r = Postoperative_Ventral_Hernia_R::ANY_R;
}

Primary_Ventral_Hernia::Primary_Ventral_Hernia(QString t) : Diagnosis(t)
{
    this->size = Primary_Ventral_Hernia_Sizes::ANY_PRIMARY_VENTRAL_SIZE;
//    this->
}


// get string for inguinal hernia
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


// get string for postopereative verntral hernia
QString Postoperative_Ventral_Hernia::Get_String()
{
    QString result_str;

    result_str += this->Get_Title();
    result_str += " ";

    switch(this->Get_M())
    {
    case ANY_M:
        result_str += "M-12345";
        break;
    case M1:
        result_str += "M-1";
        break;
    case M2:
        result_str += "M-2";
        break;
    case M3:
        result_str += "M-3";
        break;
    case M4:
        result_str += "M-4";
        break;
    case M5:
        result_str += "M-5";
        break;
    }

    result_str += ", ";

    switch(this->Get_L())
    {
    case ANY_L:
        result_str += "L-1234";
        break;

    case L1:
        result_str += "L-1";
        break;
    case L2:
        result_str += "L-2";
        break;
    case L3:
        result_str += "L-3";
        break;
    case L4:
        result_str += "L-4";
        break;
    }

    result_str += ", ";

    switch(this->Get_W())
    {
    case ANY_W:
        result_str += "W-123";
        break;
    case W1:
        result_str += "W-1";
        break;
    case W2:
        result_str += "W-2";
        break;
    case W3:
        result_str += "W-3";
        break;
    }

    result_str += ", ";

    switch(this->Get_R())
    {
    case ANY_R:
        result_str += "R-1234";
        break;

    case R1:
        result_str += "R-1";
        break;
    case R2:
        result_str += "R-2";
        break;
    case R3:
        result_str += "R-3";
        break;
    case R4:
        result_str += "R-4";
        break;
    }

    return result_str;
}


QString Primary_Ventral_Hernia::Get_String()
{
    QString result;

    return result;
}

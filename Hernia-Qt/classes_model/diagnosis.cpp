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
    this->type = Primary_Ventral_Hernia_Types::TYPE_NOT_CHOSEN;
    this->subtitle = Primary_Ventral_Hernia_SubTypes::SUBTYPE_NOT_CHOSEN;
    this->size = Primary_Ventral_Hernia_Sizes::SIZE_NOT_CHOSEN;
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

    if (this->Get_Size() != Primary_Ventral_Hernia_Sizes::SIZE_NOT_CHOSEN)
    {
        switch(this->Get_Size())
        {
        case Primary_Ventral_Hernia_Sizes::ANY_PRIMARY_VENTRAL_SIZE:
            result += "любой размер";
            break;
        case Primary_Ventral_Hernia_Sizes::SMALL:
            result += "малая";
            break;
        case Primary_Ventral_Hernia_Sizes::MEDIUM:
            result += "средняя";
            break;
        case Primary_Ventral_Hernia_Sizes::LARGE:
            result += "большая";
            break;
        }

    result += " ";
    }

    if (this->Get_Subtitle() != Primary_Ventral_Hernia_SubTypes::SUBTYPE_NOT_CHOSEN)
    {
        switch(this->Get_Subtitle())
        {
        case Primary_Ventral_Hernia_SubTypes::ANY_PRIMARY_VENTRAL_SUBTYPE:
            result += "любая срединная/боковая";
            break;
        case Primary_Ventral_Hernia_SubTypes::EPIGASTRIC:
            result += "эпигистральная";
            break;
        case Primary_Ventral_Hernia_SubTypes::UMBICIAL:
            result += "пупочная";
            break;
        case Primary_Ventral_Hernia_SubTypes::SPIGEL:
            result += "спигелевой линии";
            break;
        case Primary_Ventral_Hernia_SubTypes::LUMBAR:
            result += "поясничная";
            break;
        }

        return result;
    }

    else if (this->Get_Type() != Primary_Ventral_Hernia_Types::TYPE_NOT_CHOSEN)
    {
        switch(this->Get_Type())
        {
        case Primary_Ventral_Hernia_Types::ANY_PRIMARY_VENTRAL_TYPE:
            result += "любая первичная";
            break;
        case Primary_Ventral_Hernia_Types::SIDE:
            result += "боковая";
            break;
        case Primary_Ventral_Hernia_Types::MIDDLE:
            result += "срединная";
            break;
        }

        return result;
    }

    else
    {
        result += this->Get_Title();
        return result;
    }
}

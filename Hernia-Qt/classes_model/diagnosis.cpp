#include "diagnosis.h"


Diagnosis::Diagnosis(QString t) : title(t) {}


Inguinal_Hernia::Inguinal_Hernia(Inguinal_Hernia_PR p, Inguinal_Hernia_LMF l, 
    Inguinal_Hernia_Size s, QString t) :
        Diagnosis(t), pr(p), lmf(l), size(s) {}

#ifndef DIAGNOSIS_SENTRY
#define DIAGNOSIS_SENTRY

#include <QString>

class Diagnosis
{
public:
    Diagnosis(QString t);
    Diagnosis() {}

    virtual QString Get_String() { return title; }

    QString Get_Title() { return title; }

private:
    QString title;
};


enum Inguinal_Hernia_PR { ANY_PR, P, R };
enum Inguinal_Hernia_LMF { ANY_LMF, L, M, F };
enum Inguinal_Hernia_SIZE { ANY_INGUINAL_SIZE, S1, S2, S3, S4, S5 };


/* 1st type of hernia: inguinal hernia */
class Inguinal_Hernia : public Diagnosis
{
public:
    Inguinal_Hernia(QString t);

    Inguinal_Hernia_LMF Get_LMF() { return lmf; }
    Inguinal_Hernia_PR Get_PR() { return pr; }
    Inguinal_Hernia_SIZE Get_Size() { return size; }

    void Set_LMF(Inguinal_Hernia_LMF lmf1) { lmf = lmf1; }
    void Set_PR(Inguinal_Hernia_PR pr1) { pr = pr1; }
    void Set_Size(Inguinal_Hernia_SIZE size1) {size = size1; }

    QString Get_String() override;

private:
    Inguinal_Hernia_PR pr;
    Inguinal_Hernia_LMF lmf;
    Inguinal_Hernia_SIZE size;
};





enum Primary_Ventral_Hernia_Sizes { ANY_PRIMARY_VENTRAL_SIZE, SMALL, MEDIUM, LARGE };


/* 2nd type of hernia: primary ventral hernia */
class Primary_Ventral_Hernia : public Diagnosis
{
public:
    Primary_Ventral_Hernia(QString t);

    QString Get_Type() { return type; }
    QString Get_Subtitle() { return subtitle; }
    Primary_Ventral_Hernia_Sizes Get_Size() { return size; }

    void Set_Type(QString type) { this->type = type; }
    void Set_Subtitle(QString subt) { this->subtitle = subt; }
    void Set_Size(Primary_Ventral_Hernia_Sizes s) { this->size = s; }

    QString Get_String() override;

private:
    QString type;
    QString subtitle;
    Primary_Ventral_Hernia_Sizes size;
};



enum Postoperative_Ventral_Hernia_M { ANY_M, M1, M2, M3, M4, M5 };
enum Postoperative_Ventral_Hernia_L { ANY_L, L1, L2, L3, L4 };
enum Postoperative_Ventral_Hernia_W { ANY_W, W1, W2, W3 };
enum Postoperative_Ventral_Hernia_R { ANY_R, R1, R2, R3, R4 };


/* 3rd type of hernia: post operative ventral hernia */
class Postoperative_Ventral_Hernia : public Diagnosis
{
public:
    Postoperative_Ventral_Hernia(QString title);

    Postoperative_Ventral_Hernia_M Get_M() { return m; }
    Postoperative_Ventral_Hernia_L Get_L() { return l; }
    Postoperative_Ventral_Hernia_W Get_W() { return w; }
    Postoperative_Ventral_Hernia_R Get_R() { return r; }

    void Set_M(Postoperative_Ventral_Hernia_M m1) { m = m1; }
    void Set_L(Postoperative_Ventral_Hernia_L l1) { l = l1; }
    void Set_W(Postoperative_Ventral_Hernia_W w1) { w = w1; }
    void Set_R(Postoperative_Ventral_Hernia_R r1) { r = r1; }

    QString Get_String() override;
private:
    Postoperative_Ventral_Hernia_M m;
    Postoperative_Ventral_Hernia_L l;
    Postoperative_Ventral_Hernia_W w;
    Postoperative_Ventral_Hernia_R r;
};



#endif

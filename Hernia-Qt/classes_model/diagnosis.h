#ifndef DIAGNOSIS_SENTRY
#define DIAGNOSIS_SENTRY

#include <QString>

class Diagnosis
{
public:
    Diagnosis(QString t);

    QString Get_Title() { return title; }
private:
    QString title;
};

enum Inguinal_Hernia_PR { ANY_PR, P, R };
enum Inguinal_Hernia_LMF { ANY_LMF, L, M, F };
enum Inguinal_Hernia_Size { ANY_INGUINAL_SIZE, S1, S2, S3, S4, S5 };


/* 1st type of hernia: inguinal hernia */
class Inguinal_Hernia : public Diagnosis
{
public:
    Inguinal_Hernia(Inguinal_Hernia_PR p, Inguinal_Hernia_LMF l,
        Inguinal_Hernia_Size s, QString title);

private:
    Inguinal_Hernia_PR pr;
    Inguinal_Hernia_LMF lmf;
    Inguinal_Hernia_Size size;
};





enum Primary_Ventral_Hernia_Sizes { ANY_PRIMARY_VENTRAL_SIZE, SMALL, MEDIUM, LARGE };


/* 2nd type of hernia: primary ventral hernia */
class Primary_Ventral_Hernia : public Diagnosis
{
public:
    Primary_Ventral_Hernia(QString t);
private:   

};


enum Middle_Primary_Ventral_Hernia_Subtitles { ANY_MID_SUBTITLE, EPIGASTRIC, UMBILICIAL };
// enum Primary_Ventral_Hernia_Sizes { ANY_SIZE_VENTRAL, 

class Middle_Primary_Ventral_Hernia : public Primary_Ventral_Hernia
{
public:

private:

};

class Side_Primary_Ventral_Hernia : public Primary_Ventral_Hernia
{
public:

private:

};



enum Postoperative_Ventral_Hernia_M { ANY_M, M1, M2, M3, M4, M5 };
enum Postoperative_Ventral_Hernia_L { ANY_L, L1, L2, L3, L4 };
enum Postoperative_Ventral_Hernia_W { ANY_W, W1, W2, W3 };
enum Postoperative_Ventral_Hernia_R { ANY_R, R1, R2, R3, R4 };


/* 3rd type of hernia: post operative ventral hernia */
class Postoperative_Ventral_Hernia : public Diagnosis
{
public:
    Postoperative_Ventral_Hernia(std::string t);    
private:        
    Postoperative_Ventral_Hernia_M m;
    Postoperative_Ventral_Hernia_L l;
    Postoperative_Ventral_Hernia_W w;
    Postoperative_Ventral_Hernia_R r;
};



#endif

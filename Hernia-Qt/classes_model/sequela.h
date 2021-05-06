#ifndef SEQUELA_SENTRY
#define SEQUELA_SENTRY

#include <QString>


class Sequela
{
public:
    Sequela() { type = "----любое осложнение-----"; }

    void Set_Title(QString t) { title = t; }
    QString Get_Title() const { return title; }

    void Set_Type(QString t) { type = t; }
    QString Get_Type() { return type; }


private:
    QString type;
    QString title;
};


#endif

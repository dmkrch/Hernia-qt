#ifndef SEQUELA_SENTRY
#define SEQUELA_SENTRY

#include <QString>


class Sequela
{
public:
    Sequela(QString t) : title(t) {}
    Sequela(const Sequela& s);

    void Set_Title(QString t) { title = t; }
    QString Get_Title() const { return title; }

    void Set_SubTitle(QString t) { subtitle = t; }
    QString Get_Subtitle() { return subtitle; }
private:
    QString subtitle;
    QString title;
};


#endif

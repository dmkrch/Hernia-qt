#ifndef DATEFORM_H
#define DATEFORM_H

#include <QDialog>
#include <QDate>

namespace Ui {
class DateForm;
}

class DateForm : public QDialog
{
    Q_OBJECT

public:
    explicit DateForm(QWidget *parent = nullptr);
    QDate GetDate();

    ~DateForm();

signals:
    void date_setted();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::DateForm *ui;
    QDate date1;
};

#endif // DATEFORM_H

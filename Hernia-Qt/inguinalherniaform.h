#ifndef INGUINALHERNIAFORM_H
#define INGUINALHERNIAFORM_H

#include <QDialog>

namespace Ui {
class InguinalHerniaForm;
}

class InguinalHerniaForm : public QDialog
{
    Q_OBJECT

public:
    explicit InguinalHerniaForm(QWidget *parent = nullptr);
    ~InguinalHerniaForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::InguinalHerniaForm *ui;
};

#endif // INGUINALHERNIAFORM_H

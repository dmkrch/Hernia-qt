#ifndef POSTVENTRALHERNIAFORM_H
#define POSTVENTRALHERNIAFORM_H

#include <QDialog>

namespace Ui {
class PostVentralHerniaForm;
}

class PostVentralHerniaForm : public QDialog
{
    Q_OBJECT

public:
    explicit PostVentralHerniaForm(QWidget *parent = nullptr);
    ~PostVentralHerniaForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PostVentralHerniaForm *ui;
};

#endif // POSTVENTRALHERNIAFORM_H

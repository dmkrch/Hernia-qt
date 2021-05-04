#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "rangeslider.h"
#include <QSlider>
#include "dateform.h"
#include "sequenceform.h"
#include "inguinalherniaform.h"
#include "pventralherniaform.h"
#include "postventralherniaform.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slider_date_lower_value_changed();
    void slider_date_upper_value_changed();
    void slider_age_lower_value_changed();
    void slider_age_upper_value_changed();
    void on_pushButton_from_clicked();
    void on_pushButton_to_clicked();
    void set_date_edit();
    void on_pushButton_sequence_clicked();
    void set_diagnosis(QString diagnosis_type);
    void sequela_form_closed();

private:
    Ui::MainWindow *ui;
    DateForm* dateform;
    SequenceForm* sequenceform;
    InguinalHerniaForm* inguinalHerniaform;
    PVentralHerniaForm* pventralHerniaform;
    PostVentralHerniaForm* postVentralHerniaform;

    QToolBar* toolbar;
    RangeSlider* days_rSlider;
    RangeSlider* age_rSlider;
    QSlider* slider;

    bool is_date_from_pressed;
};
#endif // MAINWINDOW_H

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
#include "classes_model/handled_operation.h"
#include "classes_model/operation_to_find_model.h"
#include "dbmanager.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void Set_Surgeons_Combobox();
    void Set_Surgeons_List();
    void Set_Operations_List();
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
    void open_diagnosis_form(QString diagnosis_type);
    void sequela_form_closed();
    void inguinal_form_closed();
    void primary_ventral_form_closed();
    void post_ventral_form_closed();
    void on_pushButton_search_op_clicked();
    void on_pushButton_add_surgeon_clicked();

private:
    //forms
    Ui::MainWindow *ui;
    DateForm* dateform;
    SequenceForm* sequenceform;
    InguinalHerniaForm* inguinalHerniaform;
    PVentralHerniaForm* pventralHerniaform;
    PostVentralHerniaForm* postVentralHerniaform;

    // widgets
    QToolBar* toolbar;
    RangeSlider* days_rSlider;
    RangeSlider* age_rSlider;
    QSlider* slider;

    // classes models
    Handled_Operation* new_handled_operation;
    Operation_To_Find_Model* operation_to_find;
    Diagnosis* diagnosis;

    // db manager
    DbManager* db;

    bool is_date_from_pressed;
};
#endif // MAINWINDOW_H

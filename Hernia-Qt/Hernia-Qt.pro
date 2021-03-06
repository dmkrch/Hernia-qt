QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    classes_model/diagnosis.cpp \
    classes_model/handled_operation.cpp \
    classes_model/patient.cpp \
    classes_model/sequela.cpp \
    dateform.cpp \
    dbmanager.cpp \
    inguinalherniaform.cpp \
    main.cpp \
    mainwindow.cpp \
    operationaddform.cpp \
    postventralherniaform.cpp \
    pventralherniaform.cpp \
    rangeslider.cpp \
    sequenceform.cpp

HEADERS += \
    classes_model/diagnosis.h \
    classes_model/handled_operation.h \
    classes_model/operation_to_find_model.h \
    classes_model/patient.h \
    classes_model/sequela.h \
    dateform.h \
    dbmanager.h \
    inguinalherniaform.h \
    mainwindow.h \
    operationaddform.h \
    postventralherniaform.h \
    pventralherniaform.h \
    rangeslider.h \
    sequenceform.h

FORMS += \
    dateform.ui \
    inguinalherniaform.ui \
    mainwindow.ui \
    operationaddform.ui \
    postventralherniaform.ui \
    pventralherniaform.ui \
    sequenceform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2018-06-03T13:59:34
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET =EEGviewer #EMG_GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    subjectmanagement.cpp \
    handmovement.cpp \
    muscleselect.cpp \
    showwave.cpp \
    recorddata.cpp \
    qcustomplot.cpp \
    systemsetting.cpp \
    EDFlib-master/edflib.c

HEADERS  += mainwindow.h \
    subjectmanagement.h \
    handmovement.h \
    muscleselect.h \
    showwave.h \
    recorddata.h \
    qcustomplot.h \
    systemsetting.h \
    EDFlib-master/edflib.h

RESOURCES += \
    image.qrc

RC_ICONS = test7.ico

FORMS += \
    systemsetting.ui

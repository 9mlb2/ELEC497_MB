#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T16:58:18
#
#-------------------------------------------------

QT       += core gui widgets multimedia multimediawidgets #Make sure all your major functionalities are here

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ELEC497_UI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    playbackmode.cpp \
    playbacksettings.cpp \
    heatmap.cpp \
    datapoint.cpp

HEADERS  += mainwindow.h \
    playbackmode.h \
    playbacksettings.h \
    heatmap.h \
    datapoint.h

INCLUDEPATH += "C:\boost\boost_1_52_0" #Change this to wherever your boost directory resides

LIBS += "C:\boost\boost_1_52_0\stage\lib\libboost_system-mgw48-mt-1_52.a" #Make sure this boost library matches above - change the number of mgw to be whatever version of MinGW you have (I have 4.8) - this can also be checked in the folder
LIBS += "C:\MinGW\lib\libws2_32.a" #Should match your MinGW location - DO NOT change file name

FORMS    += mainwindow.ui \
    playbackmode.ui \
    playbacksettings.ui

RESOURCES += \
    ELEC497Resources.qrc

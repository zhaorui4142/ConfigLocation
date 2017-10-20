#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T14:28:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Configuration
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

#包含头文件的搜索路径
INCLUDEPATH += $$PWD

#包含自定义模块
include(glwidget/glwidget.pri)
include(detector/detector.pri)
include(videosource/videosource.pri)
include(cpuusage/cpuusage.pri)
include(gpuusage/gpuusage.pri)
include(netflow/netflow.pri)


SOURCES += main.cpp\
        mainwindow.cpp \

HEADERS  += mainwindow.h \
    struct-data.h \

FORMS    += mainwindow.ui

RESOURCES += \
    resource/shaders.qrc


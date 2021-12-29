#-------------------------------------------------
#
# Project created by QtCreator 2021-12-28T08:40:28
#
#-------------------------------------------------

QT       += gui widgets multimedia multimediawidgets sql

TARGET = Widgets
TEMPLATE = lib



DEFINES += WIDGETS_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        scannerWidget.cpp \
        masterWidget.cpp \
        cameraWidget.cpp \
    savePuzzleWidget.cpp \
    envLocal.cpp \
    validationWidget.cpp

HEADERS += \
        scannerWidget.h \
        widgets_global.h \
        masterWidget.h \
        cameraWidget.h \
    savePuzzleWidget.h \
    envLocal.h \
    validationWidget.h



unix {
    target.path = /usr/lib
    INSTALLS += target
}

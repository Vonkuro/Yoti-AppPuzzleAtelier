QT += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += \
        main.cpp \
        masterWidget.cpp \
        cameraWidget.cpp

HEADERS += \
        masterWidget.h \
        cameraWidget.h

FORMS += \
        masterWidget.ui \
        cameraWidget.ui

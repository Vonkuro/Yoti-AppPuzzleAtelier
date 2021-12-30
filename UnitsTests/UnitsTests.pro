QT += testlib
QT += gui core widgets multimedia multimediawidgets sql
CONFIG += qt warn_on depend_includepath testcase

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES +=  tst_accesscamera.cpp \
    main.cpp \
    tst_masterwidget.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Widgets/release/ -lWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Widgets/debug/ -lWidgets
else:unix: LIBS += -L$$OUT_PWD/../Widgets/ -lWidgets

INCLUDEPATH += $$PWD/../Widgets
DEPENDPATH += $$PWD/../Widgets

HEADERS += \
    tst_accesscamera.h \
    tst_masterwidget.h

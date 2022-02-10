QT += core gui multimedia multimediawidgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = Yoti-AppPuzzle

SOURCES += \
        main.cpp \


HEADERS += \



win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Widgets/release/ -lWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Widgets/debug/ -lWidgets
else:unix: LIBS += -L$$OUT_PWD/../Widgets/ -lWidgets

INCLUDEPATH += $$PWD/../Widgets
DEPENDPATH += $$PWD/../Widgets

#-------------------------------------------------
#
# Project created by QtCreator 2017-02-09T21:58:34
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Painter
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
        main_window.cpp \
    main_view.cpp \
    ellipse_t.cpp \
    line_t.cpp \
    shape_t.cpp \
    rect_t.cpp \
    pen_t.cpp \
    shape_com.cpp \
    text_t.cpp \
    client.cpp \
    client_window.cpp \
    network_sett_ui.cpp

HEADERS  += main_window.h \
    main_view.h \
    ellipse_t.h \
    line_t.h \
    rect_t.h \
    shape_t.h \
    pen_t.h \
    shape_com.h \
    text_t.h \
    client.h \
    client_window.h \
    network_sett_ui.h

FORMS    += main_window.ui \
    client_window.ui \
    network_sett_ui.ui

DISTFILES += \
    icons/rectangle.png

RESOURCES += \
    resources.qrc

TARGET = myOpenGL
TEMPLATE = app

HEADERS += \
    myglwidget.h

SOURCES += \
    main.cpp \
    myglwidget.cpp

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT       += opengl

win32:LIBS += -lOpengl32 \
                -lglu32 \
                -lglut

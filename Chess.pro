#-------------------------------------------------
#
# Project created by QtCreator 2019-05-11T12:11:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

SOURCES += \
        field.cpp \
        figures/bishop.cpp \
        figures/figure.cpp \
        figures/king.cpp \
        figures/knight.cpp \
        figures/pawn.cpp \
        figures/queen.cpp \
        figures/rook.cpp \
        main.cpp \
        generator.cpp \
    board.cpp

HEADERS += \
        color.h \
        field.h \
        figures/bishop.h \
        figures/figure.h \
        figures/king.h \
        figures/knight.h \
        figures/pawn.h \
        figures/queen.h \
        figures/rook.h \
        generator.h \
    board.h \
    figures/figure_types.h

FORMS += \
        generator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    chess.qrc

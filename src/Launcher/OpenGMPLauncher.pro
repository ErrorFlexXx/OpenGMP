#-------------------------------------------------
#
# Project created by QtCreator 2018-08-14T17:18:53
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGMPLauncher
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

# Backward compatibility for XP and wine (fixes QtWidgets unimpl. call).
QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01

DEFINES += LAUNCHER

SOURCES += main.cpp \
        ../Shared/Systems/versionSystem.cpp \
        ../Shared/Components/version.cpp \
        ../../lib/ZenLib/Utils/logger.cpp \
        inject.cpp \
        openGMPFrmMain.cpp

HEADERS +=  \
            ../Shared/Components/version.hpp \
            inject.h \
            openGMPFrmMain.h

FORMS += \
    openGMPFrmMain.ui

# Compile libraries:
# Physfs:

INCLUDEPATH += ../../lib \
               ../

LIBS += -luser32 \
        -lws2_32

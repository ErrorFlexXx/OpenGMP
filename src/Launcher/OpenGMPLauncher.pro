#-------------------------------------------------
#
# Project created by QtCreator 2018-08-14T17:18:53
#
#-------------------------------------------------

QT       += core gui

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

SOURCES += main.cpp\
        openGMP.cpp

HEADERS  += openGMP.h

FORMS    += openGMP.ui

# Compile libraries:
# Physfs:

INCLUDEPATH += ../../lib/physfs/src

unix  {
}
win32 {
}

SOURCES += \
../../lib/physfs/src/physfs_archiver_7z.c \
../../lib/physfs/src/physfs_archiver_dir.c \
../../lib/physfs/src/physfs_archiver_grp.c \
../../lib/physfs/src/physfs_archiver_hog.c \
../../lib/physfs/src/physfs_archiver_iso9660.c \
../../lib/physfs/src/physfs_archiver_mvl.c \
../../lib/physfs/src/physfs_archiver_qpak.c \
../../lib/physfs/src/physfs_archiver_slb.c \
../../lib/physfs/src/physfs_archiver_unpacked.c \
../../lib/physfs/src/physfs_archiver_vdf.c \
../../lib/physfs/src/physfs_archiver_wad.c \
../../lib/physfs/src/physfs_archiver_zip.c \
../../lib/physfs/src/physfs_byteorder.c \
../../lib/physfs/src/physfs.c \
../../lib/physfs/src/physfs_platform_os2.c \
../../lib/physfs/src/physfs_platform_posix.c \
../../lib/physfs/src/physfs_platform_qnx.c \
../../lib/physfs/src/physfs_platform_unix.c \
../../lib/physfs/src/physfs_platform_windows.c \
../../lib/physfs/src/physfs_unicode.c

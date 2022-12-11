QT += core gui
QT += serialport
QT += core gui printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat
win32-msvc* {
    QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
}
TARGET      = uidemo08
TEMPLATE    = app

HEADERS     += head.h \
    ChineseEncoding.h \
    localpanel.h \
    transfer/publicFunction.h \
    transfer/transferBinary.h \
    transfer/transferbx.h \
    transfer/transferbx_10.h \
    transfer/transferbx_12.h \
    transfer/transferbx_14.h \
    transfer/transferbx_16.h \
    transfer/transferbx_24.h \
    transfer/transferbx_28.h \
    transfer/transferbx_32.h \
    transfer/transferbx_40.h \
    transfer/transferbx_48.h \
    transfer/transferbx_6.h \
    transfer/transferbx_8.h
SOURCES     += main.cpp \
    localpanel.cpp \
    transfer/transferBinary.cpp \
    transfer/transferbx_10.cpp \
    transfer/transferbx_12.cpp \
    transfer/transferbx_14.cpp \
    transfer/transferbx_16.cpp \
    transfer/transferbx_24.cpp \
    transfer/transferbx_28.cpp \
    transfer/transferbx_32.cpp \
    transfer/transferbx_40.cpp \
    transfer/transferbx_48.cpp \
    transfer/transferbx_6.cpp \
    transfer/transferbx_8.cpp
RESOURCES   += other/main.qrc \
    ../src.qrc
RESOURCES   += $$PWD/../core_qss/qss.qrc

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/form
include ($$PWD/form/form.pri)

INCLUDEPATH += $$PWD/../core_base
include ($$PWD/../core_base/core_base.pri)


FORMS += \
    localpanel.ui

QT += core gui widgets sql network
QT += printsupport charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# C++17
CONFIG += c++17
QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic

TARGET = interface
TEMPLATE = app

SOURCES += \
    activite.cpp \
    connection.cpp \
    main.cpp \
    statistics.cpp \
    qr_activite.cpp \
    qr_dialog.cpp \
    recommendations_dialog.cpp

HEADERS += \
    activite.h \
    connection.h \
    statistics.h \
    qr_activite.h \
    qr_dialog.h \
    recommendations_dialog.h

FORMS += \
    activite.ui

# Installation rules
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Afficher la console sous Windows
CONFIG += console

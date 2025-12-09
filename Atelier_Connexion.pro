QT += core gui sql charts network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Ensure Qt Charts is properly configured
QT += charts

TARGET = Atelier_Connexion
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    connection.cpp \
    fournisseur.cpp \
    statistiquesdialog.cpp \
    googlesheetsexporter.cpp

HEADERS += \
    mainwindow.h \
    connection.h \
    fournisseur.h \
    statistiquesdialog.h \
    googlesheetsexporter.h

FORMS += \
    mainwindow.ui

# Ajoute les ressources si tu as un fichier .qrc
# RESOURCES += ressources.qrc

CONFIG += c++11

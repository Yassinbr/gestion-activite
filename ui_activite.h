/********************************************************************************
** Form generated from reading UI file 'activite.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIVITE_H
#define UI_ACTIVITE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *fournisseur;
    QTabWidget *fournisseur_2;
    QWidget *tab_ajouter;
    QPushButton *ajouter_fornisseur_btn_2;
    QGroupBox *groupBox;
    QLineEdit *capacite;
    QLabel *label_telephone_ajout_4;
    QLabel *label_telephone_ajout_3;
    QLabel *label_telephone_ajout_2;
    QLabel *label_telephone_ajout;
    QLineEdit *nom_fornisseur_ajout_2;
    QLineEdit *type;
    QLabel *label_nom_ajout;
    QLineEdit *telephone_fornisseur_ajout_2;
    QLineEdit *duree;
    QPushButton *modifier;
    QTableWidget *afficher_fornisseur_2;
    QPushButton *refreche;
    QPushButton *triparname;
    QLabel *label_id_supprimer;
    QPushButton *supprimer_fornisseur_btn_2;
    QLineEdit *id_fornisseur_supprimer_2;
    QPushButton *QRCODE;
    QPushButton *Statistic;
    QPushButton *recommandationai;
    QPushButton *pdf;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        fournisseur = new QPushButton(centralwidget);
        fournisseur->setObjectName("fournisseur");
        fournisseur->setGeometry(QRect(10, 130, 161, 51));
        fournisseur->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        fournisseur_2 = new QTabWidget(centralwidget);
        fournisseur_2->setObjectName("fournisseur_2");
        fournisseur_2->setGeometry(QRect(170, 20, 1021, 500));
        tab_ajouter = new QWidget();
        tab_ajouter->setObjectName("tab_ajouter");
        ajouter_fornisseur_btn_2 = new QPushButton(tab_ajouter);
        ajouter_fornisseur_btn_2->setObjectName("ajouter_fornisseur_btn_2");
        ajouter_fornisseur_btn_2->setGeometry(QRect(30, 410, 150, 40));
        ajouter_fornisseur_btn_2->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        groupBox = new QGroupBox(tab_ajouter);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(30, 30, 441, 361));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    font-family: \"Arial\";\n"
"    font-size: 25px;\n"
"    font-weight: bold;\n"
"    color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 10px;\n"
"    margin-top: 10px;\n"
"    background-color: #B0C4DE;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 5px;\n"
"    background-color: #1E1E5A;\n"
"    color: white;\n"
"    border-radius: 5px;\n"
"}\n"
""));
        capacite = new QLineEdit(groupBox);
        capacite->setObjectName("capacite");
        capacite->setGeometry(QRect(120, 270, 300, 30));
        label_telephone_ajout_4 = new QLabel(groupBox);
        label_telephone_ajout_4->setObjectName("label_telephone_ajout_4");
        label_telephone_ajout_4->setGeometry(QRect(20, 270, 80, 30));
        label_telephone_ajout_3 = new QLabel(groupBox);
        label_telephone_ajout_3->setObjectName("label_telephone_ajout_3");
        label_telephone_ajout_3->setGeometry(QRect(20, 220, 80, 30));
        label_telephone_ajout_2 = new QLabel(groupBox);
        label_telephone_ajout_2->setObjectName("label_telephone_ajout_2");
        label_telephone_ajout_2->setGeometry(QRect(20, 170, 80, 30));
        label_telephone_ajout = new QLabel(groupBox);
        label_telephone_ajout->setObjectName("label_telephone_ajout");
        label_telephone_ajout->setGeometry(QRect(20, 130, 80, 30));
        nom_fornisseur_ajout_2 = new QLineEdit(groupBox);
        nom_fornisseur_ajout_2->setObjectName("nom_fornisseur_ajout_2");
        nom_fornisseur_ajout_2->setGeometry(QRect(120, 80, 300, 30));
        type = new QLineEdit(groupBox);
        type->setObjectName("type");
        type->setGeometry(QRect(120, 170, 300, 30));
        label_nom_ajout = new QLabel(groupBox);
        label_nom_ajout->setObjectName("label_nom_ajout");
        label_nom_ajout->setGeometry(QRect(20, 80, 80, 30));
        telephone_fornisseur_ajout_2 = new QLineEdit(groupBox);
        telephone_fornisseur_ajout_2->setObjectName("telephone_fornisseur_ajout_2");
        telephone_fornisseur_ajout_2->setGeometry(QRect(120, 130, 300, 30));
        duree = new QLineEdit(groupBox);
        duree->setObjectName("duree");
        duree->setGeometry(QRect(120, 220, 300, 30));
        modifier = new QPushButton(tab_ajouter);
        modifier->setObjectName("modifier");
        modifier->setGeometry(QRect(190, 410, 161, 41));
        modifier->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        afficher_fornisseur_2 = new QTableWidget(tab_ajouter);
        if (afficher_fornisseur_2->columnCount() < 6)
            afficher_fornisseur_2->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        afficher_fornisseur_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        afficher_fornisseur_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        afficher_fornisseur_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        afficher_fornisseur_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        afficher_fornisseur_2->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        afficher_fornisseur_2->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        afficher_fornisseur_2->setObjectName("afficher_fornisseur_2");
        afficher_fornisseur_2->setGeometry(QRect(480, 70, 361, 191));
        afficher_fornisseur_2->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: #020230;\n"
"    color: white;\n"
"    border-radius: 15px;\n"
"    padding: 10px;\n"
"    font-size: 16px;\n"
"    border: none;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #5555FF;\n"
"    color: white;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #030350;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"}"));
        refreche = new QPushButton(tab_ajouter);
        refreche->setObjectName("refreche");
        refreche->setGeometry(QRect(490, 270, 131, 41));
        refreche->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        triparname = new QPushButton(tab_ajouter);
        triparname->setObjectName("triparname");
        triparname->setGeometry(QRect(640, 270, 161, 41));
        triparname->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        label_id_supprimer = new QLabel(tab_ajouter);
        label_id_supprimer->setObjectName("label_id_supprimer");
        label_id_supprimer->setGeometry(QRect(480, 350, 80, 30));
        supprimer_fornisseur_btn_2 = new QPushButton(tab_ajouter);
        supprimer_fornisseur_btn_2->setObjectName("supprimer_fornisseur_btn_2");
        supprimer_fornisseur_btn_2->setGeometry(QRect(660, 339, 121, 41));
        supprimer_fornisseur_btn_2->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        id_fornisseur_supprimer_2 = new QLineEdit(tab_ajouter);
        id_fornisseur_supprimer_2->setObjectName("id_fornisseur_supprimer_2");
        id_fornisseur_supprimer_2->setGeometry(QRect(510, 360, 141, 20));
        QRCODE = new QPushButton(tab_ajouter);
        QRCODE->setObjectName("QRCODE");
        QRCODE->setGeometry(QRect(500, 20, 171, 31));
        QRCODE->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        Statistic = new QPushButton(tab_ajouter);
        Statistic->setObjectName("Statistic");
        Statistic->setGeometry(QRect(370, 410, 91, 41));
        Statistic->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        recommandationai = new QPushButton(tab_ajouter);
        recommandationai->setObjectName("recommandationai");
        recommandationai->setGeometry(QRect(480, 410, 181, 41));
        recommandationai->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        pdf = new QPushButton(tab_ajouter);
        pdf->setObjectName("pdf");
        pdf->setGeometry(QRect(670, 410, 111, 41));
        pdf->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        fournisseur_2->addTab(tab_ajouter, QString());
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 70, 161, 51));
        pushButton->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(10, 330, 161, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(10, 190, 171, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(10, 260, 171, 51));
        pushButton_4->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(10, 510, 261, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("QLineEdit, QDateTimeEdit {\n"
"    font-family: \"Arial\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Arial Black\";\n"
"    font-size: 14px;\n"
"    color: white;\n"
"    background-color: #0A0A2A;\n"
"    border: 2px solid #1E1E5A;\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1E1E5A;\n"
"}\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        fournisseur_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Fournisseurs", nullptr));
        fournisseur->setText(QCoreApplication::translate("MainWindow", "Gestion des activit\303\251s", nullptr));
        ajouter_fornisseur_btn_2->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Gestion des Activit\303\251s", nullptr));
        label_telephone_ajout_4->setText(QCoreApplication::translate("MainWindow", "Capacite", nullptr));
        label_telephone_ajout_3->setText(QCoreApplication::translate("MainWindow", "Duree", nullptr));
        label_telephone_ajout_2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        label_telephone_ajout->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone :", nullptr));
        label_nom_ajout->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        QTableWidgetItem *___qtablewidgetitem = afficher_fornisseur_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = afficher_fornisseur_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = afficher_fornisseur_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = afficher_fornisseur_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = afficher_fornisseur_2->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Duree", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = afficher_fornisseur_2->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Capacite", nullptr));
        refreche->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        triparname->setText(QCoreApplication::translate("MainWindow", "Tri par name", nullptr));
        label_id_supprimer->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        supprimer_fornisseur_btn_2->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        QRCODE->setText(QCoreApplication::translate("MainWindow", "QR CODE", nullptr));
        Statistic->setText(QCoreApplication::translate("MainWindow", "Statistic", nullptr));
        recommandationai->setText(QCoreApplication::translate("MainWindow", "Recommandation AI", nullptr));
        pdf->setText(QCoreApplication::translate("MainWindow", "PDF", nullptr));
        fournisseur_2->setTabText(fournisseur_2->indexOf(tab_ajouter), QCoreApplication::translate("MainWindow", "Gestion Activite", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Gestion des inscriptions", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Gestion evenement", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Gestion des emploiyes", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Gestion des plannings", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Gestion des partenaires et fournisseurs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIVITE_H

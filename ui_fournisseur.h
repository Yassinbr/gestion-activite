/********************************************************************************
** Form generated from reading UI file 'fournisseur.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOURNISSEUR_H
#define UI_FOURNISSEUR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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
    QLabel *label_nom_ajout;
    QLineEdit *nom_fornisseur_ajout_2;
    QLabel *label_telephone_ajout;
    QLineEdit *telephone_fornisseur_ajout_2;
    QPushButton *ajouter_fornisseur_btn_2;
    QPushButton *Statistic;
    QPushButton *pdf;
    QLineEdit *type;
    QLineEdit *duree;
    QLineEdit *capacite;
    QLabel *label_telephone_ajout_2;
    QLabel *label_telephone_ajout_3;
    QLabel *label_telephone_ajout_4;
    QPushButton *recommandationai;
    QWidget *tab_modifier;
    QLabel *label_id_modifier;
    QLineEdit *id_fornisseur_modifier_2;
    QLabel *label_nom_modifier;
    QLineEdit *nom_fornisseur_modifier_2;
    QLabel *label_telephone_modifier;
    QLineEdit *telephone_fornisseur_modifier_2;
    QPushButton *modifier_fornisseur_btn_2;
    QPushButton *modifsearch;
    QLineEdit *typemod;
    QLineEdit *dureemod;
    QLineEdit *capacitemod;
    QLabel *label_telephone_modifier_2;
    QLabel *label_telephone_modifier_3;
    QLabel *label_telephone_modifier_4;
    QWidget *tab_afficher;
    QTableWidget *afficher_fornisseur_2;
    QPushButton *triparname;
    QPushButton *refreche;
    QWidget *tab_supprimer;
    QLabel *label_id_supprimer;
    QLineEdit *id_fornisseur_supprimer_2;
    QPushButton *supprimer_fornisseur_btn_2;
    QWidget *tab;
    QPushButton *QRCODE;
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
        fournisseur->setGeometry(QRect(10, 10, 150, 40));
        fournisseur_2 = new QTabWidget(centralwidget);
        fournisseur_2->setObjectName("fournisseur_2");
        fournisseur_2->setGeometry(QRect(170, 60, 841, 500));
        tab_ajouter = new QWidget();
        tab_ajouter->setObjectName("tab_ajouter");
        label_nom_ajout = new QLabel(tab_ajouter);
        label_nom_ajout->setObjectName("label_nom_ajout");
        label_nom_ajout->setGeometry(QRect(40, 80, 80, 30));
        nom_fornisseur_ajout_2 = new QLineEdit(tab_ajouter);
        nom_fornisseur_ajout_2->setObjectName("nom_fornisseur_ajout_2");
        nom_fornisseur_ajout_2->setGeometry(QRect(140, 80, 300, 30));
        label_telephone_ajout = new QLabel(tab_ajouter);
        label_telephone_ajout->setObjectName("label_telephone_ajout");
        label_telephone_ajout->setGeometry(QRect(40, 130, 80, 30));
        telephone_fornisseur_ajout_2 = new QLineEdit(tab_ajouter);
        telephone_fornisseur_ajout_2->setObjectName("telephone_fornisseur_ajout_2");
        telephone_fornisseur_ajout_2->setGeometry(QRect(140, 130, 300, 30));
        ajouter_fornisseur_btn_2 = new QPushButton(tab_ajouter);
        ajouter_fornisseur_btn_2->setObjectName("ajouter_fornisseur_btn_2");
        ajouter_fornisseur_btn_2->setGeometry(QRect(110, 370, 150, 40));
        Statistic = new QPushButton(tab_ajouter);
        Statistic->setObjectName("Statistic");
        Statistic->setGeometry(QRect(620, 280, 191, 51));
        pdf = new QPushButton(tab_ajouter);
        pdf->setObjectName("pdf");
        pdf->setGeometry(QRect(620, 70, 201, 91));
        type = new QLineEdit(tab_ajouter);
        type->setObjectName("type");
        type->setGeometry(QRect(140, 170, 300, 30));
        duree = new QLineEdit(tab_ajouter);
        duree->setObjectName("duree");
        duree->setGeometry(QRect(140, 220, 300, 30));
        capacite = new QLineEdit(tab_ajouter);
        capacite->setObjectName("capacite");
        capacite->setGeometry(QRect(140, 270, 300, 30));
        label_telephone_ajout_2 = new QLabel(tab_ajouter);
        label_telephone_ajout_2->setObjectName("label_telephone_ajout_2");
        label_telephone_ajout_2->setGeometry(QRect(40, 170, 80, 30));
        label_telephone_ajout_3 = new QLabel(tab_ajouter);
        label_telephone_ajout_3->setObjectName("label_telephone_ajout_3");
        label_telephone_ajout_3->setGeometry(QRect(40, 220, 80, 30));
        label_telephone_ajout_4 = new QLabel(tab_ajouter);
        label_telephone_ajout_4->setObjectName("label_telephone_ajout_4");
        label_telephone_ajout_4->setGeometry(QRect(40, 270, 80, 30));
        recommandationai = new QPushButton(tab_ajouter);
        recommandationai->setObjectName("recommandationai");
        recommandationai->setGeometry(QRect(630, 190, 181, 61));
        fournisseur_2->addTab(tab_ajouter, QString());
        tab_modifier = new QWidget();
        tab_modifier->setObjectName("tab_modifier");
        label_id_modifier = new QLabel(tab_modifier);
        label_id_modifier->setObjectName("label_id_modifier");
        label_id_modifier->setGeometry(QRect(40, 50, 80, 30));
        id_fornisseur_modifier_2 = new QLineEdit(tab_modifier);
        id_fornisseur_modifier_2->setObjectName("id_fornisseur_modifier_2");
        id_fornisseur_modifier_2->setGeometry(QRect(140, 50, 300, 30));
        label_nom_modifier = new QLabel(tab_modifier);
        label_nom_modifier->setObjectName("label_nom_modifier");
        label_nom_modifier->setGeometry(QRect(40, 100, 80, 30));
        nom_fornisseur_modifier_2 = new QLineEdit(tab_modifier);
        nom_fornisseur_modifier_2->setObjectName("nom_fornisseur_modifier_2");
        nom_fornisseur_modifier_2->setGeometry(QRect(140, 100, 300, 30));
        label_telephone_modifier = new QLabel(tab_modifier);
        label_telephone_modifier->setObjectName("label_telephone_modifier");
        label_telephone_modifier->setGeometry(QRect(40, 150, 80, 30));
        telephone_fornisseur_modifier_2 = new QLineEdit(tab_modifier);
        telephone_fornisseur_modifier_2->setObjectName("telephone_fornisseur_modifier_2");
        telephone_fornisseur_modifier_2->setGeometry(QRect(140, 150, 300, 30));
        modifier_fornisseur_btn_2 = new QPushButton(tab_modifier);
        modifier_fornisseur_btn_2->setObjectName("modifier_fornisseur_btn_2");
        modifier_fornisseur_btn_2->setGeometry(QRect(50, 340, 150, 40));
        modifsearch = new QPushButton(tab_modifier);
        modifsearch->setObjectName("modifsearch");
        modifsearch->setGeometry(QRect(510, 50, 181, 61));
        typemod = new QLineEdit(tab_modifier);
        typemod->setObjectName("typemod");
        typemod->setGeometry(QRect(140, 190, 300, 30));
        dureemod = new QLineEdit(tab_modifier);
        dureemod->setObjectName("dureemod");
        dureemod->setGeometry(QRect(140, 240, 300, 30));
        capacitemod = new QLineEdit(tab_modifier);
        capacitemod->setObjectName("capacitemod");
        capacitemod->setGeometry(QRect(140, 280, 300, 30));
        label_telephone_modifier_2 = new QLabel(tab_modifier);
        label_telephone_modifier_2->setObjectName("label_telephone_modifier_2");
        label_telephone_modifier_2->setGeometry(QRect(40, 190, 80, 30));
        label_telephone_modifier_3 = new QLabel(tab_modifier);
        label_telephone_modifier_3->setObjectName("label_telephone_modifier_3");
        label_telephone_modifier_3->setGeometry(QRect(40, 240, 80, 30));
        label_telephone_modifier_4 = new QLabel(tab_modifier);
        label_telephone_modifier_4->setObjectName("label_telephone_modifier_4");
        label_telephone_modifier_4->setGeometry(QRect(40, 270, 80, 41));
        fournisseur_2->addTab(tab_modifier, QString());
        tab_afficher = new QWidget();
        tab_afficher->setObjectName("tab_afficher");
        afficher_fornisseur_2 = new QTableWidget(tab_afficher);
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
        afficher_fornisseur_2->setGeometry(QRect(20, 20, 800, 420));
        triparname = new QPushButton(tab_afficher);
        triparname->setObjectName("triparname");
        triparname->setGeometry(QRect(640, 310, 161, 81));
        refreche = new QPushButton(tab_afficher);
        refreche->setObjectName("refreche");
        refreche->setGeometry(QRect(670, 90, 90, 29));
        fournisseur_2->addTab(tab_afficher, QString());
        tab_supprimer = new QWidget();
        tab_supprimer->setObjectName("tab_supprimer");
        label_id_supprimer = new QLabel(tab_supprimer);
        label_id_supprimer->setObjectName("label_id_supprimer");
        label_id_supprimer->setGeometry(QRect(50, 80, 80, 30));
        id_fornisseur_supprimer_2 = new QLineEdit(tab_supprimer);
        id_fornisseur_supprimer_2->setObjectName("id_fornisseur_supprimer_2");
        id_fornisseur_supprimer_2->setGeometry(QRect(140, 80, 300, 30));
        supprimer_fornisseur_btn_2 = new QPushButton(tab_supprimer);
        supprimer_fornisseur_btn_2->setObjectName("supprimer_fornisseur_btn_2");
        supprimer_fornisseur_btn_2->setGeometry(QRect(140, 150, 150, 40));
        fournisseur_2->addTab(tab_supprimer, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        QRCODE = new QPushButton(tab);
        QRCODE->setObjectName("QRCODE");
        QRCODE->setGeometry(QRect(300, 160, 171, 101));
        fournisseur_2->addTab(tab, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        fournisseur_2->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Fournisseurs", nullptr));
        fournisseur->setText(QCoreApplication::translate("MainWindow", "Activite", nullptr));
        label_nom_ajout->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        label_telephone_ajout->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone :", nullptr));
        ajouter_fornisseur_btn_2->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        Statistic->setText(QCoreApplication::translate("MainWindow", "Statistic", nullptr));
        pdf->setText(QCoreApplication::translate("MainWindow", "PDF", nullptr));
        label_telephone_ajout_2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        label_telephone_ajout_3->setText(QCoreApplication::translate("MainWindow", "Duree", nullptr));
        label_telephone_ajout_4->setText(QCoreApplication::translate("MainWindow", "Capacite", nullptr));
        recommandationai->setText(QCoreApplication::translate("MainWindow", "Recommandation AI", nullptr));
        fournisseur_2->setTabText(fournisseur_2->indexOf(tab_ajouter), QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        label_id_modifier->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        label_nom_modifier->setText(QCoreApplication::translate("MainWindow", "Nom :", nullptr));
        label_telephone_modifier->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone :", nullptr));
        modifier_fornisseur_btn_2->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        modifsearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        label_telephone_modifier_2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        label_telephone_modifier_3->setText(QCoreApplication::translate("MainWindow", "Duree", nullptr));
        label_telephone_modifier_4->setText(QCoreApplication::translate("MainWindow", "Capacite", nullptr));
        fournisseur_2->setTabText(fournisseur_2->indexOf(tab_modifier), QCoreApplication::translate("MainWindow", "Modifier", nullptr));
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
        triparname->setText(QCoreApplication::translate("MainWindow", "Tri par name", nullptr));
        refreche->setText(QCoreApplication::translate("MainWindow", "Refreche", nullptr));
        fournisseur_2->setTabText(fournisseur_2->indexOf(tab_afficher), QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        label_id_supprimer->setText(QCoreApplication::translate("MainWindow", "ID :", nullptr));
        supprimer_fornisseur_btn_2->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        fournisseur_2->setTabText(fournisseur_2->indexOf(tab_supprimer), QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        QRCODE->setText(QCoreApplication::translate("MainWindow", "QR CODE", nullptr));
        fournisseur_2->setTabText(fournisseur_2->indexOf(tab), QCoreApplication::translate("MainWindow", "QR CODE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOURNISSEUR_H

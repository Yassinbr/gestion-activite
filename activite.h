#ifndef ACTIVITE_H
#define ACTIVITE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>
#include <QSqlRecord>
#include <QRegularExpressionValidator>
#include <QValidator>
#include "statistics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Structure Activite
struct Activite {
    int id_activite;
    QString nom, telephone, type;
    int duree, capacite;

    // Constructeur avec ID (6 paramètres)
    Activite(int i, QString n, QString t, QString ty, int d, int c)
        : id_activite(i), nom(n), telephone(t), type(ty), duree(d), capacite(c) {}

    // Constructeur sans ID (5 paramètres)
    Activite(QString n, QString t, QString ty, int d, int c)
        : id_activite(0), nom(n), telephone(t), type(ty), duree(d), capacite(c) {}

    // Constructeur avec ID et 3 paramètres (pour compatibilité chargement BD)
    Activite(int i, QString n, QString t)
        : id_activite(i), nom(n), telephone(t), type(""), duree(0), capacite(0) {}

    // Constructeur avec 2 paramètres (pour compatibilité ajout)
    Activite(QString n, QString t)
        : id_activite(0), nom(n), telephone(t), type(""), duree(0), capacite(0) {}

    // Constructeur par défaut
    Activite() : id_activite(0), nom(""), telephone(""), type(""), duree(0), capacite(0) {}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Navigation
    void onActiviteClicked();

    // Recherche & tri
    void onTriParNameClicked();

    // Statistiques
    void onStatisticClicked();

    // Activites
    void onAjouterActiviteClicked();
    void onModifierActiviteClicked();
    void onSupprimerActiviteClicked();
    void onExportPdfClicked();
    void onOpenQRDialogClicked();
    void onOpenRecommendationsClicked();
    void onRefreshActivitesClicked();

private:
    Ui::MainWindow *ui;
    QList<Activite> activites;

    // Méthodes de connexion Oracle
    bool connectToOracle();
    void initDatabase();
    bool testConnection();

    // Méthodes CRUD Activites
    void loadActivitesFromDB();
    void saveActiviteToDB(const Activite &activite);
    void updateActiviteInDB(int activiteId, const Activite &activite);
    void deleteActiviteFromDB(int activiteId);
    bool activiteExistsInDB(const QString &nom, const QString &telephone);
    QString formaterNumeroTunisien(const QString &telephone);

    // Méthodes de contrôle de saisie
    bool validerFormulaireAjout(QStringList &erreurs);

    // Méthodes d'interface
    void appliquerStyleModerne();
    QString getDateActuelle();

    // Méthodes d'affichage
    void actualiserAffichageActivite();

    // Méthodes de nettoyage des champs
    void viderChampsAjoutActivite();
};

#endif // ACTIVITE_H

#include "activite.h"
#include "ui_activite.h"
#include "connection.h"
#include "qr_dialog.h"
#include "recommendations_dialog.h"
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTabWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QRegularExpression>
#include <algorithm>
#include <QRandomGenerator>
#include <QMap>
#include <QPair>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QDir>
#include <QPageSize>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Application starting...";

    // Initialiser la liste des activites
    activites = QList<Activite>();

    // Connexions des boutons de navigation
    connect(ui->fournisseur, &QPushButton::clicked, this, &MainWindow::onActiviteClicked);

    // Connexions Activites - NOUVEAU UI SIMPLIFIÉ
    qDebug() << "🔧 Configuration des connexions...";
    
    connect(ui->ajouter_fornisseur_btn_2, &QPushButton::clicked, this, &MainWindow::onAjouterActiviteClicked);
    qDebug() << "✅ Bouton ajouter connecté";
    
    connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::onModifierActiviteClicked);
    qDebug() << "✅ Bouton modifier connecté";
    
    connect(ui->supprimer_fornisseur_btn_2, &QPushButton::clicked, this, &MainWindow::onSupprimerActiviteClicked);
    connect(ui->pdf, &QPushButton::clicked, this, &MainWindow::onExportPdfClicked);
    // Tri et statistiques
    connect(ui->triparname, &QPushButton::clicked, this, &MainWindow::onTriParNameClicked);
    connect(ui->Statistic, &QPushButton::clicked, this, &MainWindow::onStatisticClicked);
    // QR Code
    connect(ui->QRCODE, &QPushButton::clicked, this, &MainWindow::onOpenQRDialogClicked);
    // Recommandations
    connect(ui->recommandationai, &QPushButton::clicked, this, &MainWindow::onOpenRecommendationsClicked);
    // Rafraîchir
    connect(ui->refreche, &QPushButton::clicked, this, &MainWindow::onRefreshActivitesClicked);
    qDebug() << "✅ Bouton supprimer connecté";

    qDebug() << "✅ Toutes les connexions établies";

    // Configuration de l'interface
    ui->fournisseur_2->setCurrentIndex(0);
    ui->fournisseur_2->setVisible(true);
    qDebug() << "✅ Interface configurée";

    // Appliquer le style moderne
    appliquerStyleModerne();
    // Forcer le texte du tableau en noir pour écraser les styles UI précédents
    ui->afficher_fornisseur_2->setStyleSheet(
        "QTableWidget { color: black; background-color: #ffffff; }"
        "QTableWidget::item { color: black; }"
        "QTableWidget::item:selected { background-color: #3949ab; color: white; }"
        "QHeaderView::section { color: black; }"
    );

    // Initialiser la base de données
    initDatabase();

    qDebug() << "✅ Application démarrée avec succès";
}

MainWindow::~MainWindow()
{
    delete ui;
}


// ==================== VALIDATION ====================

bool MainWindow::validerFormulaireAjout(QStringList &erreurs)
{
    QString nom = ui->nom_fornisseur_ajout_2->text().trimmed();
    QString telephone = ui->telephone_fornisseur_ajout_2->text().trimmed().replace(" ", "").replace(".", "").replace("-", "");

    // Validation du nom
    if (nom.isEmpty()) {
        erreurs << "Le nom est obligatoire";
    } else if (nom.length() < 2) {
        erreurs << "Le nom doit contenir au moins 2 caractères";
    }

    // Validation téléphone - 8 chiffres minimum
    if (telephone.isEmpty()) {
        erreurs << "Le téléphone est obligatoire";
    } else if (telephone.length() < 8) {
        erreurs << "Le téléphone doit contenir au moins 8 chiffres";
    } else if (!QRegularExpression("^[0-9]+$").match(telephone).hasMatch()) {
        erreurs << "Le téléphone ne doit contenir que des chiffres";
    }

    return erreurs.isEmpty();
}
// ==================== CONNEXION ORACLE ====================

bool MainWindow::connectToOracle()
{
    if (QSqlDatabase::contains("oracle_connection")) {
        QSqlDatabase::removeDatabase("oracle_connection");
        qDebug() << "🔄 Ancienne connexion fermée";
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "oracle_connection");
    QString connectionString = "DRIVER={Oracle in XE};DBQ=XE;UID=monprojet;PWD=monprojet123;";
    db.setDatabaseName(connectionString);
    db.setConnectOptions("SQL_ATTR_USE_UNICODE=1;SQL_ATTR_TRACE=0");

    if (db.open()) {
        qDebug() << "✅ Connexion Oracle réussie avec l'utilisateur monprojet!";

        QSqlQuery testQuery(db);
        testQuery.setForwardOnly(true);
        if (testQuery.exec("SELECT 1 FROM DUAL")) {
            qDebug() << "✅ Test de requête immédiat réussi";
        } else {
            qDebug() << "⚠️ Test de requête immédiat échoué:" << testQuery.lastError().text();
        }

        return true;
    } else {
        qDebug() << "❌ Échec connexion Oracle:" << db.lastError().text();
        return false;
    }
}

void MainWindow::initDatabase()
{
    qDebug() << "=== INITIALISATION BASE DE DONNEES ===";
    qDebug() << "🔍 Tentative de connexion via classe Connection...";

    Connection conn;
    if (conn.createconnect()) {
        qDebug() << "✅ Connexion établie via classe Connection";

        QSqlDatabase db = QSqlDatabase::database();
        qDebug() << "📊 Vérification état de la connexion:";
        qDebug() << "   - isOpen():" << db.isOpen();
        qDebug() << "   - isValid():" << db.isValid();
        qDebug() << "   - driverName():" << db.driverName();
        qDebug() << "   - databaseName():" << db.databaseName();
        qDebug() << "   - connectionName():" << db.connectionName();

        if (db.isOpen()) {
            qDebug() << "🎯 Base de données ouverte, tentative de chargement des activites...";
            
            QSqlQuery testQuery(db);
            if (testQuery.exec("SELECT 1 FROM DUAL")) {
                qDebug() << "✅ Test query DUAL réussi";
            } else {
                qDebug() << "❌ Test query DUAL échoué:" << testQuery.lastError().text();
            }
            
            // Charger les données activites
            loadActivitesFromDB();
        } else {
            qDebug() << "❌ Base de données fermée après connexion!";
        }

        qDebug() << "✅ Base de données initialisée avec succès";
    } else {
        qDebug() << "❌ Échec connexion via classe Connection";
        QMessageBox::warning(this, "Mode Hors Ligne",
                             "Impossible de se connecter à Oracle. Le mode hors ligne sera utilisé.");
    }
}

bool MainWindow::testConnection()
{
    qDebug() << "🔍 Test de connexion...";
    QSqlDatabase db = QSqlDatabase::database();

    qDebug() << "   - isOpen():" << db.isOpen();
    qDebug() << "   - isValid():" << db.isValid();

    if (!db.isOpen()) {
        qDebug() << "⚠️ Connexion fermée - tentative de réouverture";
        Connection conn;
        if (!conn.createconnect()) {
            qDebug() << "❌ Réouverture impossible";
            return false;
        }
        db = QSqlDatabase::database();
        qDebug() << "✅ Reconnexion établie";
    }

    QSqlQuery query(db);
    query.setForwardOnly(true);

    if (query.exec("SELECT 1 FROM DUAL")) {
        if (query.next()) {
            qDebug() << "✅ Test connexion réussi";
            return true;
        }
    } else {
        qDebug() << "❌ Test connexion échoué:" << query.lastError().text();
        qDebug() << "   Type:" << query.lastError().type();
        qDebug() << "   Code:" << query.lastError().nativeErrorCode();
        db.close();
        Connection conn;
        if (conn.createconnect()) {
            qDebug() << "🔄 Reconnexion réussie après échec";
            return true;
        }
    }
    return false;
}

// ==================== MÉTHODES CRUD activites ====================

void MainWindow::loadActivitesFromDB()
{
    qDebug() << "=== DÉBUT CHARGEMENT activites ===";

    activites.clear();
    QSqlDatabase db = QSqlDatabase::database();

    qDebug() << "📊 État de la connexion dans loadActivitesFromDB:";
    qDebug() << "   - isOpen():" << db.isOpen();
    qDebug() << "   - isValid():" << db.isValid();
    qDebug() << "   - connectionName():" << db.connectionName();

    if (!db.isOpen()) {
        qDebug() << "❌ Base de données non ouverte";
        qDebug() << "🔄 Tentative de réouverture...";
        
        Connection conn;
        if (conn.createconnect()) {
            qDebug() << "✅ Reconnexion réussie";
            db = QSqlDatabase::database();
        } else {
            qDebug() << "❌ Reconnexion échouée";
            QMessageBox::warning(this, "Erreur", "Connexion à la base de données perdue");
            return;
        }
    }

    QStringList requetes = {
        "SELECT id_activite, NOM, TELEPHONE, TYPE, DUREE, CAPACITE FROM activites ORDER BY id_activite",
        "SELECT * FROM activites ORDER BY id_activite"
    };
    bool succes = false;
    QString derniereErreur;

    for (const QString &sql : requetes) {
        qDebug() << "🔍 Tentative requête:" << sql;
        QSqlQuery query(db);
        query.setForwardOnly(true);

        if (query.exec(sql)) {
            qDebug() << "✅ Requête réussie!";

            int count = 0;
            while (query.next()) {
                QSqlRecord record = query.record();

                int id_activite = 0;
                QString nom, telephone, type;
                int duree = 0, capacite = 0;

                if (record.count() >= 6) {
                    id_activite = query.value(0).toInt();
                    nom = query.value(1).toString();
                    telephone = query.value(2).toString();
                    type = query.value(3).toString();
                    duree = query.value(4).toInt();
                    capacite = query.value(5).toInt();
                } else if (record.count() >= 3) {
                    id_activite = query.value(0).toInt();
                    nom = query.value(1).toString();
                    telephone = query.value(2).toString();
                }

                Activite activite(id_activite, nom, telephone, type, duree, capacite);
                activites.append(activite);
                count++;
                qDebug() << "📥 Activite chargé - ID:" << activite.id_activite << "Nom:" << activite.nom;
            }

            qDebug() << "🎉" << count << "activites chargés depuis Oracle!";
            succes = true;
            break;

        } else {
            derniereErreur = query.lastError().text();
            qDebug() << "❌ Échec requête:" << derniereErreur;
            qDebug() << "   Type d'erreur:" << query.lastError().type();
            qDebug() << "   Code d'erreur:" << query.lastError().nativeErrorCode();
        }
    }

    if (!succes) {
        qDebug() << "❌ Aucune requête n'a fonctionné";
        qDebug() << "⚠️ La table activites existe-t-elle?";
        QMessageBox::critical(this, "Erreur de chargement",
                              QString("Impossible de charger les activites.\n\nDernière erreur: %1").arg(derniereErreur));
        return;
    }

    actualiserAffichageActivite();
    qDebug() << "=== FIN CHARGEMENT activites ===";
}

void MainWindow::actualiserAffichageActivite()
{
    qDebug() << "=== ACTUALISATION AFFICHAGE activites ===";
    qDebug() << "Nombre de activites à afficher:" << activites.size();

    QTableWidget *tableWidget = ui->afficher_fornisseur_2;
    tableWidget->setRowCount(activites.size());
    
    for (int i = 0; i < activites.size(); ++i) {
        const Activite &f = activites[i];
        
        tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(f.id_activite)));
        tableWidget->setItem(i, 1, new QTableWidgetItem(f.nom));
        tableWidget->setItem(i, 2, new QTableWidgetItem(f.telephone));
        tableWidget->setItem(i, 3, new QTableWidgetItem(f.type));
        tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(f.duree)));
        tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(f.capacite)));

        qDebug() << "📋 Ajouté au tableau - ID:" << f.id_activite << "Nom:" << f.nom;
    }

    tableWidget->resizeColumnsToContents();

    qDebug() << "✅ Tableau actualisé - Lignes:" << activites.size();
    qDebug() << "=====================================";
}

void MainWindow::saveActiviteToDB(const Activite &activite)
{
    qDebug() << "=== TENTATIVE SAUVEGARDE Activite DANS ORACLE ===";
    qDebug() << "📝 Données à sauvegarder:";
    qDebug() << "   - Nom:" << activite.nom;
    qDebug() << "   - Téléphone:" << activite.telephone;

    if (!testConnection()) {
        qDebug() << "❌ Connexion non disponible pour la sauvegarde";
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données perdue!");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();

    qDebug() << "🔄 Début de transaction...";
    if (!db.transaction()) {
        qDebug() << "❌ Impossible de démarrer la transaction";
        qDebug() << "   Erreur:" << db.lastError().text();
        QMessageBox::critical(this, "Erreur", "Impossible de démarrer la transaction!");
        return;
    }

    QSqlQuery query(db);
    query.setForwardOnly(true);

    QString sql = "INSERT INTO activites (NOM, TELEPHONE, TYPE, DUREE, CAPACITE) VALUES (:nom, :telephone, :type, :duree, :capacite)";
    query.prepare(sql);
    query.bindValue(":nom", activite.nom);
    query.bindValue(":telephone", activite.telephone);
    query.bindValue(":type", activite.type);
    query.bindValue(":duree", activite.duree);
    query.bindValue(":capacite", activite.capacite);

    qDebug() << "📝 Exécution de la requête INSERT...";
    qDebug() << "   SQL:" << sql;
    qDebug() << "   Nom:" << activite.nom;
    qDebug() << "   Téléphone:" << activite.telephone;

    if (query.exec()) {
        qDebug() << "✅ INSERT réussi!";
        if (db.commit()) {
            qDebug() << "✅✅✅ COMMIT RÉUSSI - Activite sauvegardé dans Oracle!";

            QSqlQuery idQuery(db);
            idQuery.setForwardOnly(true);

            qDebug() << "🔍 Récupération de l'ID généré...";
            if (idQuery.exec("SELECT seq_activites.CURRVAL FROM DUAL") && idQuery.next()) {
                int newId = idQuery.value(0).toInt();
                qDebug() << "🆕 ID généré pour le Activite:" << newId;

                for (int i = activites.size() - 1; i >= 0; --i) {
                    if (activites[i].nom == activite.nom &&
                        activites[i].telephone == activite.telephone &&
                        activites[i].id_activite == 0) {
                        activites[i].id_activite = newId;
                        qDebug() << "📋 ID mis à jour dans la liste locale:" << newId;
                        break;
                    }
                }

                QMessageBox::information(this, "Succès",
                                         QString("Activite ajouté avec succès dans Oracle!\nID: %1").arg(newId));

            } else {
                qDebug() << "⚠️ Impossible de récupérer l'ID généré";
                qDebug() << "   Erreur:" << idQuery.lastError().text();
                QMessageBox::information(this, "Succès", "Activite ajouté avec succès!");
            }

        } else {
            qDebug() << "❌ ERREUR COMMIT:" << db.lastError().text();
            qDebug() << "   Type:" << db.lastError().type();
            qDebug() << "   Code:" << db.lastError().nativeErrorCode();
            db.rollback();
            QMessageBox::critical(this, "Erreur",
                                  "Erreur lors de la sauvegarde: " + db.lastError().text());

            for (int i = 0; i < activites.size(); ++i) {
                if (activites[i].nom == activite.nom && activites[i].id_activite == 0) {
                    activites.removeAt(i);
                    qDebug() << "🗑️ Activite retiré de la liste locale (échec sauvegarde)";
                    break;
                }
            }
        }
    } else {
        qDebug() << "❌ ERREUR INSERTION:" << query.lastError().text();
        qDebug() << "   Type d'erreur:" << query.lastError().type();
        qDebug() << "   Code d'erreur:" << query.lastError().nativeErrorCode();
        qDebug() << "   Driver text:" << query.lastError().driverText();
        qDebug() << "   Database text:" << query.lastError().databaseText();
        db.rollback();
        QMessageBox::critical(this, "Erreur",
                              "Erreur d'insertion: " + query.lastError().text());

        for (int i = 0; i < activites.size(); ++i) {
            if (activites[i].nom == activite.nom && activites[i].id_activite == 0) {
                activites.removeAt(i);
                qDebug() << "🗑️ Activite retiré de la liste locale (échec insertion)";
                break;
            }
        }
    }

    actualiserAffichageActivite();
}

void MainWindow::updateActiviteInDB(int ActiviteId, const Activite &Activite)
{
    qDebug() << "=== MODIFICATION Activite ===";
    qDebug() << "   ID:" << ActiviteId;
    qDebug() << "   Nouveau nom:" << Activite.nom;
    qDebug() << "   Nouveau téléphone:" << Activite.telephone;

    if (!testConnection()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données perdue!");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.setForwardOnly(true);

    QString sql = "UPDATE activites SET NOM = :nom, TELEPHONE = :telephone, TYPE = :type, DUREE = :duree, CAPACITE = :capacite WHERE id_activite = :id";
    query.prepare(sql);
    query.bindValue(":nom", Activite.nom);
    query.bindValue(":telephone", Activite.telephone);
    query.bindValue(":type", Activite.type);
    query.bindValue(":duree", Activite.duree);
    query.bindValue(":capacite", Activite.capacite);
    query.bindValue(":id", ActiviteId);

    qDebug() << "📝 Exécution UPDATE...";
    if (query.exec()) {
        int rowsAffected = query.numRowsAffected();
        qDebug() << "✅ Activite ID" << ActiviteId << "modifié avec succès";
        qDebug() << "   Lignes affectées:" << rowsAffected;
        QMessageBox::information(this, "Succès", "Activite modifié avec succès!");
    } else {
        qDebug() << "❌ Erreur modification Activite ID" << ActiviteId;
        qDebug() << "   Erreur:" << query.lastError().text();
        qDebug() << "   Type:" << query.lastError().type();
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification: " + query.lastError().text());
    }
}

void MainWindow::deleteActiviteFromDB(int ActiviteId)
{
    qDebug() << "=== SUPPRESSION Activite ===";
    qDebug() << "   ID à supprimer:" << ActiviteId;

    if (!testConnection()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données perdue!");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.setForwardOnly(true);

    QString sql = "DELETE FROM activites WHERE id_activite = :id";
    query.prepare(sql);
    query.bindValue(":id", ActiviteId);

    qDebug() << "📝 Exécution DELETE...";
    if (query.exec()) {
        int rowsAffected = query.numRowsAffected();
        qDebug() << "✅ Activite ID" << ActiviteId << "supprimé avec succès";
        qDebug() << "   Lignes affectées:" << rowsAffected;
        QMessageBox::information(this, "Succès", "Activite supprimé avec succès!");
    } else {
        qDebug() << "❌ Erreur suppression Activite ID" << ActiviteId;
        qDebug() << "   Erreur:" << query.lastError().text();
        qDebug() << "   Type:" << query.lastError().type();
        QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression: " + query.lastError().text());
    }
}

bool MainWindow::activiteExistsInDB(const QString &nom, const QString &telephone)
{
    if (!testConnection()) return false;

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.setForwardOnly(true);

    QString sql = "SELECT COUNT(*) FROM activites WHERE NOM = :nom OR TELEPHONE = :telephone";
    query.prepare(sql);
    query.bindValue(":nom", nom);
    query.bindValue(":telephone", telephone);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

// ==================== NAVIGATION ====================

void MainWindow::onActiviteClicked()
{
    qDebug() << "";
    qDebug() << "====================================";
    qDebug() << "🔘 BOUTON Activite (MENU) CLIQUÉ";
    qDebug() << "====================================";
    qDebug() << "📊 État actuel du widget fournisseur_2:";
    qDebug() << "   - Existe:" << (ui->fournisseur_2 != nullptr);
    qDebug() << "   - Visible:" << ui->fournisseur_2->isVisible();
    qDebug() << "   - Enabled:" << ui->fournisseur_2->isEnabled();
    
    ui->fournisseur_2->setVisible(true);
    ui->fournisseur_2->setCurrentIndex(0); // Forcer l'onglet "ajouter" (index 0)
    qDebug() << "✅ fournisseur_2 rendu visible";
    qDebug() << "✅ Onglet 'ajouter' (index 0) sélectionné";
    qDebug() << "📍 Index actuel du tab:" << ui->fournisseur_2->currentIndex();
    
    actualiserAffichageActivite();
    qDebug() << "";
}

// ==================== activites ====================

void MainWindow::onAjouterActiviteClicked()
{
    qDebug() << "";
    qDebug() << "====================================";
    qDebug() << "🔵 BOUTON AJOUTER CLIQUÉ";
    qDebug() << "====================================";
    
    QString nom = ui->nom_fornisseur_ajout_2->text().trimmed();
    QString telephone = ui->telephone_fornisseur_ajout_2->text().trimmed().replace(" ", "").replace(".", "").replace("-", "");
    QString type = ui->type->text().trimmed();
    int duree = ui->duree->text().trimmed().toInt();
    int capacite = ui->capacite->text().trimmed().toInt();

    qDebug() << "=== TENTATIVE AJOUT Activite ===";
    qDebug() << "📝 Champs saisis:";
    qDebug() << "   - Nom:" << nom;
    qDebug() << "   - Téléphone:" << telephone;
    qDebug() << "   - Type:" << type;
    qDebug() << "   - Durée:" << duree;
    qDebug() << "   - Capacité:" << capacite;

    QStringList erreurs;
    if (!validerFormulaireAjout(erreurs)) {
        qDebug() << "❌ Validation échouée:";
        for (const QString &err : erreurs) {
            qDebug() << "   -" << err;
        }
        
        QString messageErreur = "Veuillez corriger les erreurs suivantes:\n\n• " + erreurs.join("\n• ");
        QMessageBox::warning(this, "Erreur de validation", messageErreur);

        if (!erreurs.isEmpty()) {
            if (erreurs[0].contains("nom", Qt::CaseInsensitive)) {
                ui->nom_fornisseur_ajout_2->setFocus();
            } else if (erreurs[0].contains("téléphone", Qt::CaseInsensitive)) {
                ui->telephone_fornisseur_ajout_2->setFocus();
            }
        }

        return;
    }

    qDebug() << "✅ Validation réussie";
    qDebug() << "🔍 Vérification existence dans BD...";

    if (activiteExistsInDB(nom, telephone)) {
        qDebug() << "⚠️ Activite existe déjà";
        QMessageBox::warning(this, "Erreur", "Un Activite avec ce nom ou téléphone existe déjà dans la base!");
        return;
    }

    qDebug() << "✅ Activite n'existe pas encore";
    Activite newActivite(nom, telephone, type, duree, capacite);

    qDebug() << "💾 Début sauvegarde Oracle...";
    saveActiviteToDB(newActivite);
    // Refresh the table and jump to 'Afficher' to show the new Activite
    actualiserAffichageActivite();
    // Il n'y a qu'un seul onglet maintenant
    ui->fournisseur_2->setCurrentIndex(0);

    // Try to select and scroll to the newly added Activite (match by name + telephone)
    QTableWidget *table = ui->afficher_fornisseur_2;
    int foundRow = -1;
    for (int r = 0; r < table->rowCount(); ++r) {
        QString tNom = table->item(r, 1) ? table->item(r, 1)->text() : QString();
        QString tTel = table->item(r, 2) ? table->item(r, 2)->text() : QString();
        if (tNom == nom && tTel == telephone) { foundRow = r; break; }
    }
    if (foundRow >= 0) {
        table->selectRow(foundRow);
        table->scrollToItem(table->item(foundRow, 0));
    }

    viderChampsAjoutActivite();

    qDebug() << "=== FIN AJOUT Activite ===";
    qDebug() << "";
}


void MainWindow::onModifierActiviteClicked()
{
    qDebug() << "";
    qDebug() << "====================================";
    qDebug() << "🔵 BOUTON MODIFIER CLIQUÉ";
    qDebug() << "====================================";
    
    // Récupérer la ligne sélectionnée dans le tableau
    QTableWidget *tableWidget = ui->afficher_fornisseur_2;
    int currentRow = tableWidget->currentRow();
    
    if (currentRow < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une activité dans le tableau!");
        return;
    }
    
    // Récupérer les données de la ligne sélectionnée
    int activiteId = tableWidget->item(currentRow, 0)->text().toInt();
    QString currentNom = tableWidget->item(currentRow, 1)->text();
    QString currentTelephone = tableWidget->item(currentRow, 2)->text();
    QString currentType = tableWidget->item(currentRow, 3)->text();
    int currentDuree = tableWidget->item(currentRow, 4)->text().toInt();
    int currentCapacite = tableWidget->item(currentRow, 5)->text().toInt();
    
    qDebug() << "📝 Activité sélectionnée - ID:" << activiteId << "Nom:" << currentNom;
    
    // Créer un QDialog pour la modification
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Modifier Activité");
    dialog->setMinimumSize(400, 350);
    dialog->setStyleSheet("QDialog { background-color: #f5f5f5; }");
    
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    
    // Champs de saisie
    QLabel *labelId = new QLabel(QString("ID: %1").arg(activiteId));
    labelId->setStyleSheet("font-weight: bold; font-size: 14px; color: #1a237e;");
    layout->addWidget(labelId);
    
    QLabel *labelNom = new QLabel("Nom:");
    QLineEdit *editNom = new QLineEdit(currentNom);
    layout->addWidget(labelNom);
    layout->addWidget(editNom);
    
    QLabel *labelTelephone = new QLabel("Téléphone:");
    QLineEdit *editTelephone = new QLineEdit(currentTelephone);
    layout->addWidget(labelTelephone);
    layout->addWidget(editTelephone);
    
    QLabel *labelType = new QLabel("Type:");
    QLineEdit *editType = new QLineEdit(currentType);
    layout->addWidget(labelType);
    layout->addWidget(editType);
    
    QLabel *labelDuree = new QLabel("Durée:");
    QLineEdit *editDuree = new QLineEdit(QString::number(currentDuree));
    layout->addWidget(labelDuree);
    layout->addWidget(editDuree);
    
    QLabel *labelCapacite = new QLabel("Capacité:");
    QLineEdit *editCapacite = new QLineEdit(QString::number(currentCapacite));
    layout->addWidget(labelCapacite);
    layout->addWidget(editCapacite);
    
    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *btnConfirmer = new QPushButton("Confirmer");
    QPushButton *btnAnnuler = new QPushButton("Annuler");
    btnConfirmer->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 10px; border-radius: 5px; }");
    btnAnnuler->setStyleSheet("QPushButton { background-color: #f44336; color: white; padding: 10px; border-radius: 5px; }");
    buttonLayout->addWidget(btnConfirmer);
    buttonLayout->addWidget(btnAnnuler);
    layout->addLayout(buttonLayout);
    
    connect(btnAnnuler, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(btnConfirmer, &QPushButton::clicked, dialog, &QDialog::accept);
    
    if (dialog->exec() == QDialog::Accepted) {
        QString newNom = editNom->text().trimmed();
        QString newTelephone = editTelephone->text().trimmed().replace(" ", "").replace(".", "").replace("-", "");
        QString newType = editType->text().trimmed();
        int newDuree = editDuree->text().toInt();
        int newCapacite = editCapacite->text().toInt();
        
        // Validation
        QStringList erreurs;
        if (newNom.isEmpty() || newNom.length() < 2) {
            erreurs << "Le nom doit contenir au moins 2 caractères";
        }
        if (newTelephone.isEmpty() || newTelephone.length() < 8) {
            erreurs << "Le téléphone doit contenir au moins 8 chiffres";
        }
        
        if (!erreurs.isEmpty()) {
            QMessageBox::warning(this, "Erreur de validation", "• " + erreurs.join("\n• "));
            delete dialog;
            return;
        }
        
        // Mettre à jour dans la base de données
        Activite updatedActivite(activiteId, newNom, newTelephone, newType, newDuree, newCapacite);
        updateActiviteInDB(activiteId, updatedActivite);
        
        // Mettre à jour la liste locale
        for (int i = 0; i < activites.size(); ++i) {
            if (activites[i].id_activite == activiteId) {
                activites[i] = updatedActivite;
                break;
            }
        }
        
        actualiserAffichageActivite();
        qDebug() << "✅ Activité modifiée avec succès";
    }
    
    delete dialog;
    qDebug() << "";
}

void MainWindow::onSupprimerActiviteClicked()
{
    qDebug() << "";
    qDebug() << "====================================";
    qDebug() << "🔵 BOUTON SUPPRIMER CLIQUÉ";
    qDebug() << "====================================";
    
    QString deleteText = ui->id_fornisseur_supprimer_2->text().trimmed();
    bool isNumeric;
    int deleteId = deleteText.toInt(&isNumeric);

    qDebug() << "🗑️ Demande de suppression ID:" << deleteText;

    if (deleteText.isEmpty()) {
        qDebug() << "❌ Champ vide";
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID!");
        return;
    }

    if (!isNumeric) {
        qDebug() << "❌ ID non numérique";
        QMessageBox::warning(this, "Erreur", "Veuillez saisir un ID valide (chiffres uniquement)!");
        ui->id_fornisseur_supprimer_2->setFocus();
        return;
    }

    qDebug() << "🔎 Recherche du Activite ID" << deleteId << "...";

    int index = -1;
    QString ActiviteNom;
    int ActiviteId = 0;

    for (int i = 0; i < activites.size(); ++i) {
        if (activites[i].id_activite == deleteId) {
            index = i;
            ActiviteNom = activites[i].nom;
            ActiviteId = activites[i].id_activite;
            qDebug() << "✅ Activite trouvé:";
            qDebug() << "   - Nom:" << ActiviteNom;
            qDebug() << "   - Téléphone:" << activites[i].telephone;
            break;
        }
    }

    if (index == -1) {
        qDebug() << "❌ Activite non trouvé";
        QMessageBox::warning(this, "Erreur", QString("Aucun Activite trouvé avec l'ID: %1").arg(deleteId));
        return;
    }

    qDebug() << "⚠️ Demande de confirmation...";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation de suppression",
                                  QString("Êtes-vous sûr de vouloir supprimer le Activite:\n\n"
                                          "• ID: %1\n"
                                          "• Nom: %2\n"
                                          "• Téléphone: %3\n\n"
                                          "Cette action est irréversible!")
                                      .arg(ActiviteId)
                                      .arg(ActiviteNom)
                                      .arg(activites[index].telephone),
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        qDebug() << "✅ Confirmation reçue, suppression...";
        deleteActiviteFromDB(ActiviteId);
        activites.removeAt(index);
        ui->id_fornisseur_supprimer_2->clear();
        actualiserAffichageActivite();
        qDebug() << "✅ Suppression terminée";
    } else {
        qDebug() << "❌ Suppression annulée par l'utilisateur";
    }
    qDebug() << "";
}

void MainWindow::viderChampsAjoutActivite()
{
    ui->nom_fornisseur_ajout_2->clear();
    ui->telephone_fornisseur_ajout_2->clear();
    ui->type->clear();
    ui->duree->clear();
    ui->capacite->clear();
}

// ==================== EXPORT PDF ====================

void MainWindow::onExportPdfClicked()
{
    qDebug() << "🖨️ Bouton PDF cliqué - Export en cours...";

    if (activites.isEmpty()) {
        QMessageBox::information(this, "Export PDF", "Il n'y a pas de activites à exporter.");
        return;
    }

    // Build HTML (prefer table view to reflect what's shown)
    QTableWidget *tableWidget = ui->afficher_fornisseur_2;
    QString html = "<html><head><meta charset=\"utf-8\"><style>";
    html += "table{border-collapse:collapse;width:100%;font-family:Arial, Helvetica, sans-serif; font-size:12pt;}";
    html += "th,td{border:1px solid #ddd;padding:12px;text-align:left; vertical-align:top;}";
    html += "th{background:#4CAF50;color:white; font-size:13pt;}";
    html += "tr:nth-child(even){background-color:#f2f2f2;}";
    html += "</style></head><body>";
    html += QString("<h2>Liste des activites (%1)</h2>").arg(getDateActuelle());
    html += "<table>";
    html += "<tr><th>ID</th><th>Nom</th><th>Téléphone</th></tr>";

    // Try to export only visible rows from the table if possible
    if (tableWidget && tableWidget->rowCount() > 0) {
        for (int r = 0; r < tableWidget->rowCount(); ++r) {
            if (tableWidget->isRowHidden(r)) continue;
            QString id = tableWidget->item(r, 0) ? tableWidget->item(r, 0)->text() : "";
            QString nom = tableWidget->item(r, 1) ? tableWidget->item(r, 1)->text() : "";
            QString tel = tableWidget->item(r, 2) ? tableWidget->item(r, 2)->text() : "";
            html += QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>")
                    .arg(id)
                    .arg(nom.toHtmlEscaped())
                    .arg(formaterNumeroTunisien(tel).toHtmlEscaped());
        }
    } else {
        for (const Activite &f : activites) {
            html += QString("<tr><td>%1</td><td>%2</td><td>%3</td></tr>")
                    .arg(f.id_activite)
                    .arg(f.nom.toHtmlEscaped())
                    .arg(formaterNumeroTunisien(f.telephone).toHtmlEscaped());
        }
    }

    html += "</table></body></html>";

    // Ask user for file path
    QString defaultName = QDir::homePath() + "/activites_export_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".pdf";
    QString fileName = QFileDialog::getSaveFileName(this, "Exporter en PDF", defaultName, "PDF Files (*.pdf)");
    if (fileName.isEmpty()) {
        qDebug() << "❌ Export annulé par l'utilisateur";
        return;
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    // set default font to be larger for print
    doc.setDefaultFont(QFont("Arial", 11));
    doc.setHtml(html);

    // Set page size in POINTS for correct layout and ensure the content width matches the page
    QSizeF pageSizePoints = printer.pageRect(QPrinter::Point).size();
    doc.setPageSize(pageSizePoints);
    doc.setTextWidth(pageSizePoints.width());

    // Print
    doc.print(&printer);

    QMessageBox::information(this, "Export PDF", QString("Export terminé: %1").arg(fileName));
    qDebug() << "✅ Export PDF terminé:" << fileName;
}

// ==================== RECHERCHE / TRIS / STATISTIQUES / COMMANDE ====================

void MainWindow::onTriParNameClicked()
{
    qDebug() << "🔽 Tri des activites par nom";

    std::sort(activites.begin(), activites.end(), [](const Activite &a, const Activite &b){
        return a.nom.toLower() < b.nom.toLower();
    });

    actualiserAffichageActivite();
    QMessageBox::information(this, "Tri effectué", "La liste des activites a été triée par nom.");
}

void MainWindow::onStatisticClicked()
{
    qDebug() << "📊 Bouton Statistic cliqué";

    if (!testConnection()) {
        QMessageBox::warning(this, "Erreur BD", "Connexion perdue: impossible d'obtenir les statistiques.");
        return;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    query.setForwardOnly(true);

    // Charger tous les activites pour le graphique
    QList<FournisseurStat> stats;
    if (query.exec("SELECT id_activite, NOM, TELEPHONE FROM activites ORDER BY NOM")) {
        while (query.next()) {
            FournisseurStat stat;
            stat.id = query.value(0).toInt();
            stat.nom = query.value(1).toString();
            stat.telephone = query.value(2).toString();
            stats.append(stat);
        }
    }

    if (stats.isEmpty()) {
        QMessageBox::information(this, "Statistiques", "Aucun Activite dans la base de données.");
        return;
    }

    // Afficher le dialog graphique
    StatisticsDialog *statsDialog = new StatisticsDialog(this);
    statsDialog->setFournisseursData(stats);
    statsDialog->exec();
    delete statsDialog;
}

QString MainWindow::getDateActuelle()
{
    return QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
}

void MainWindow::appliquerStyleModerne()
{
    // Style moderne avec fond blanc et accents bleu foncé
    this->setStyleSheet(
        "QMainWindow {"
        "    background: #ffffff;"
        "    color: #1a237e;"
        "}"
        "QWidget {"
        "    background: #ffffff;"
        "    color: #1a237e;"
        "}"
        "QTabWidget::pane {"
        "    border: 2px solid #1a237e;"
        "    border-radius: 10px;"
        "    background: #f5f5f5;"
        "    margin: 5px;"
        "}"
        "QTabBar::tab {"
        "    background: #e8eaf6;"
        "    color: #1a237e;"
        "    border: 2px solid #3949ab;"
        "    border-bottom: none;"
        "    border-top-left-radius: 8px;"
        "    border-top-right-radius: 8px;"
        "    min-width: 120px;"
        "    padding: 8px;"
        "    margin-right: 2px;"
        "    font-weight: bold;"
        "    font-size: 11px;"
        "}"
        "QTabBar::tab:selected {"
        "    background: #3949ab;"
        "    color: #ffffff;"
        "    border: 2px solid #1a237e;"
        "}"
        "QTabBar::tab:hover {"
        "    background: #5e35b1;"
        "    color: #ffffff;"
        "}"
        "QLabel {"
        "    color: #1a237e;"
        "    background: transparent;"
        "    font-size: 11px;"
        "}"
        "QLineEdit {"
        "    background: #ffffff;"
        "    border: 2px solid #3949ab;"
        "    border-radius: 6px;"
        "    padding: 8px;"
        "    color: #1a237e;"
        "    font-weight: 500;"
        "    selection-background-color: #3949ab;"
        "}"
        "QLineEdit:focus {"
        "    border: 2px solid #1a237e;"
        "    background: #f0f4ff;"
        "}"
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #5e35b1, stop:1 #3949ab);"
        "    border: 2px solid #1a237e;"
        "    border-radius: 6px;"
        "    color: #ffffff;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "    font-size: 11px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #7e57c2, stop:1 #5e35b1);"
        "    border: 2px solid #3949ab;"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #3949ab, stop:1 #1a237e);"
        "}"
        "QTableWidget {"
        "    background: #ffffff;"
        "    border: 2px solid #3949ab;"
        "    border-radius: 8px;"
        "    color: #000000;"
        "    gridline-color: #c5cae9;"
        "    font-weight: 500;"
        "    font-size: 10px;"
        "}"
        "QTableWidget::item {"
        "    padding: 6px;"
        "    border-bottom: 1px solid #e8eaf6;"
        "    background: #fafafa;"
        "}"
        "QTableWidget::item:alternate {"
        "    background: #f5f5f5;"
        "}"
        "QTableWidget::item:selected {"
        "    background: #3949ab;"
        "    color: #ffffff;"
        "}"
        "QTableWidget::item:hover {"
        "    background: #e8eaf6;"
        "}"
        "QHeaderView::section {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #5e35b1, stop:1 #3949ab);"
        "    color: #ffffff;"
        "    font-weight: bold;"
        "    padding: 8px;"
        "    border: 1px solid #1a237e;"
        "    font-size: 10px;"
        "}"
        "QHeaderView::section:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #7e57c2, stop:1 #5e35b1);"
        "}"
        "QMenuBar {"
        "    background: #f5f5f5;"
        "    color: #1a237e;"
        "    font-weight: bold;"
        "    border-bottom: 2px solid #3949ab;"
        "}"
        "QMenuBar::item:selected {"
        "    background: #3949ab;"
        "    color: #ffffff;"
        "    border-radius: 3px;"
        "}"
        "QMenu {"
        "    background: #ffffff;"
        "    color: #1a237e;"
        "    border: 1px solid #3949ab;"
        "}"
        "QMenu::item:selected {"
        "    background: #e8eaf6;"
        "    color: #1a237e;"
        "}"
        "QTextEdit {"
        "    background: #ffffff;"
        "    border: 2px solid #3949ab;"
        "    border-radius: 6px;"
        "    color: #1a237e;"
        "    padding: 8px;"
        "}"
        "QComboBox {"
        "    background: #ffffff;"
        "    border: 2px solid #3949ab;"
        "    border-radius: 6px;"
        "    color: #1a237e;"
        "    padding: 6px;"
        "}"
        "QComboBox:focus {"
        "    border: 2px solid #1a237e;"
        "}"
        "QGroupBox {"
        "    color: #1a237e;"
        "    border: 2px solid #3949ab;"
        "    border-radius: 6px;"
        "    margin-top: 10px;"
        "    padding-top: 10px;"
        "    font-weight: bold;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 3px 0 3px;"
        "    color: #3949ab;"
        "}"
        );

    // Style spécial pour le bouton supprimer (rouge moderne)
    QString styleSuppression =
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #ef5350, stop:1 #c62828);"
        "    border: 2px solid #b71c1c;"
        "    color: #ffffff;"
        "    border-radius: 6px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #f44336, stop:1 #d32f2f);"
        "    border: 2px solid #c62828;"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #c62828, stop:1 #b71c1c);"
        "}";

    // Appliquer le style rouge au bouton supprimer
    ui->supprimer_fornisseur_btn_2->setStyleSheet(styleSuppression);

    qDebug() << "✅ Style moderne blanc et bleu appliqué";
}

QString MainWindow::formaterNumeroTunisien(const QString &phone)
{
    QString numero = phone.trimmed().replace(" ", "").replace(".", "").replace("-", "");

    // Nettoyer les préfixes
    numero = numero.replace("+216", "").replace("00216", "");

    // Retirer le 0 initial s'il existe
    if (numero.startsWith("0")) {
        numero = numero.mid(1);
    }

    // Formater selon la longueur
    if (numero.length() == 8) {
        return "+216 " + numero;
    }

    return numero;
}

void MainWindow::onOpenQRDialogClicked()
{
    qDebug() << "Opening QR Dialog with " << activites.size() << " activites";
    
    if (activites.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Aucune activité trouvée. Veuillez d'abord charger les activités");
        return;
    }
    
    QRDialog qrDialog(activites, this);
    qrDialog.exec();
}

void MainWindow::onOpenRecommendationsClicked()
{
    qDebug() << "Opening Recommendations Dialog";
    
    RecommendationsDialog recDialog(this);
    recDialog.exec();
}

void MainWindow::onRefreshActivitesClicked()
{
    qDebug() << "Refreshing activities from database...";
    
    loadActivitesFromDB();
    actualiserAffichageActivite();
    
    QMessageBox::information(this, "Rafraîchissement", 
                             QString("Table rafraîchie avec succès!\n%1 activités chargées").arg(activites.size()));
}


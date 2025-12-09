#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statistiquesdialog.h"
#include "googlesheetsexporter.h"
#include "fournisseur.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QPdfWriter>
#include <QPageSize>
#include <QPainter>
#include <QFileDialog>
#include <QDate>
#include <QFont>
#include <QInputDialog>
#include <QClipboard>
#include <QApplication>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , googleSheetsExporter(new GoogleSheetsExporter(this))
{
    ui->setupUi(this);
    // Activer le tri sur la table
    ui->tableWidget->setSortingEnabled(true);
    actualiserTable();
    
    // Connecter les signaux de l'exporteur Google Sheets
    connect(googleSheetsExporter, &GoogleSheetsExporter::exportReussi, 
            this, [this](const QString &message) {
        QMessageBox::information(this, "Export réussi", message);
    });
    
    connect(googleSheetsExporter, &GoogleSheetsExporter::exportEchoue, 
            this, [this](const QString &erreur) {
        QMessageBox::critical(this, "Erreur d'export", erreur);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ------------------------- 🔄 ACTUALISER TABLE ------------------------- */
void MainWindow::actualiserTable()
{
    // Désactiver temporairement le tri pendant le remplissage pour éviter les problèmes
    ui->tableWidget->setSortingEnabled(false);
    
    QSqlQueryModel *model = fournisseur::lister();

    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Domaine", "Adresse", "Téléphone", "Email"});

    for (int i = 0; i < model->rowCount(); i++) {
        for (int j = 0; j < 6; j++) {
            QTableWidgetItem *item;
            
            // Définir le type de données pour un tri correct
            // Colonne 0 = ID (numérique), Colonne 4 = Téléphone (numérique)
            if (j == 0 || j == 4) {
                // Créer un item avec une valeur numérique pour un tri correct
                int numValue = model->data(model->index(i, j)).toInt();
                item = new QTableWidgetItem();
                item->setData(Qt::DisplayRole, QString::number(numValue));
                item->setData(Qt::EditRole, numValue);
            } else {
                item = new QTableWidgetItem(model->data(model->index(i, j)).toString());
            }
            
            ui->tableWidget->setItem(i, j, item);
        }
    }
    
    // Réactiver le tri après le remplissage
    ui->tableWidget->setSortingEnabled(true);

    delete model;
}

/* ------------------------- ➕ AJOUTER FOURNISSEUR ------------------------- */
void MainWindow::on_btn_ajouter_clicked()
{
    QString nom = ui->lineEdit_nom->text();
    QString domaine = ui->lineEdit_domaine->text();
    QString adresse = ui->lineEdit_adresse->text();
    QString telStr = ui->lineEdit_tel->text();
    QString email = ui->lineEdit_email->text();

    if (nom.isEmpty() || domaine.isEmpty() || adresse.isEmpty() || telStr.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs !");
        return;
    }

    bool okTel;
    int telephone = telStr.toInt(&okTel);
    if (!okTel) {
        QMessageBox::warning(this, "Erreur", "Le numéro de téléphone doit être numérique !");
        return;
    }

    if (fournisseur::ajouter(nom, domaine, adresse, telephone, email)) {
        QMessageBox::information(this, "Succès", "Fournisseur ajouté avec succès !");
        actualiserTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du fournisseur.");
    }
}

/* ------------------------- ✏️ MODIFIER FOURNISSEUR ------------------------- */
void MainWindow::on_btn_modifier_clicked()
{
    QString idStr = ui->lineEdit_recherche->text();
    if (idStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à modifier !");
        return;
    }

    bool ok;
    int id = idStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "ID invalide !");
        return;
    }

    QString nom = ui->lineEdit_nom->text();
    QString domaine = ui->lineEdit_domaine->text();
    QString adresse = ui->lineEdit_adresse->text();
    QString telStr = ui->lineEdit_tel->text();
    QString email = ui->lineEdit_email->text();

    if (fournisseur::modifier(id, nom, domaine, adresse, telStr.toInt(), email)) {
        QMessageBox::information(this, "Succès", "Fournisseur modifié !");
        actualiserTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du fournisseur.");
    }
}

/* ------------------------- ❌ SUPPRIMER FOURNISSEUR ------------------------- */
void MainWindow::on_btn_supprimer_clicked()
{
    QString idStr = ui->lineEdit_recherche->text();
    if (idStr.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer l'ID du fournisseur à supprimer !");
        return;
    }

    int id = idStr.toInt();
    if (fournisseur::supprimer(id)) {
        QMessageBox::information(this, "Succès", "Fournisseur supprimé !");
        actualiserTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression du fournisseur.");
    }
}

/* ------------------------- 🔍 RECHERCHER (ID ou DOMAINE) ------------------------- */
void MainWindow::on_btn_rechercher_clicked()
{
    QString texteRecherche = ui->lineEdit_recherche->text().trimmed();

    if (texteRecherche.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID ou un domaine à rechercher !");
        return;
    }

    QSqlQueryModel *model = fournisseur::rechercher(texteRecherche);

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Résultat vide", "Aucun fournisseur trouvé pour cette recherche !");
        actualiserTable();
        delete model;
        return;
    }

    // Désactiver temporairement le tri pendant le remplissage
    ui->tableWidget->setSortingEnabled(false);
    
    // Remplir la table
    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels({"ID", "Nom", "Domaine", "Adresse", "Téléphone", "Email"});

    for (int i = 0; i < model->rowCount(); i++) {
        for (int j = 0; j < 6; j++) {
            QTableWidgetItem *item;
            
            // Définir le type de données pour un tri correct
            // Colonne 0 = ID (numérique), Colonne 4 = Téléphone (numérique)
            if (j == 0 || j == 4) {
                // Créer un item avec une valeur numérique pour un tri correct
                int numValue = model->data(model->index(i, j)).toInt();
                item = new QTableWidgetItem();
                item->setData(Qt::DisplayRole, QString::number(numValue));
                item->setData(Qt::EditRole, numValue);
            } else {
                item = new QTableWidgetItem(model->data(model->index(i, j)).toString());
            }
            
            ui->tableWidget->setItem(i, j, item);
        }
    }
    
    // Réactiver le tri après le remplissage
    ui->tableWidget->setSortingEnabled(true);

    delete model;
}

/* ------------------------- 🔁 ACTUALISER MANUELLEMENT ------------------------- */
void MainWindow::on_btn_actualiser_clicked()
{
    actualiserTable();
}

/* ------------------------- 🧾 EXPORTER EN PDF PAR DOMAINE ------------------------- */
void MainWindow::on_btn_exporter_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichier PDF (*.pdf)");
    if (filePath.isEmpty())
        return;

    QPdfWriter pdf(filePath);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setTitle("Liste des Fournisseurs par Domaine");

    QPainter painter(&pdf);
    int y = 300;

    painter.setFont(QFont("Helvetica", 16, QFont::Bold));
    painter.drawText(200, 100, "Liste des Fournisseurs par Domaine");
    painter.setFont(QFont("Helvetica", 10));
    painter.drawText(4000, 100, "Date : " + QDate::currentDate().toString("dd/MM/yyyy"));

    // 🔹 Récupérer les domaines distincts
    QSqlQuery domainQuery("SELECT DISTINCT DOMAINE FROM FOURNISSEUR ORDER BY DOMAINE ASC");

    painter.setFont(QFont("Helvetica", 12, QFont::Bold));

    while (domainQuery.next()) {
        QString domaine = domainQuery.value(0).toString();

        y += 400;
        painter.setFont(QFont("Helvetica", 13, QFont::Bold));
        painter.drawText(100, y, "Domaine : " + domaine);
        y += 200;

        // En-têtes du tableau
        painter.setFont(QFont("Helvetica", 11, QFont::Bold));
        painter.drawText(100, y, "ID");
        painter.drawText(600, y, "Nom");
        painter.drawText(1600, y, "Adresse");
        painter.drawText(3000, y, "Téléphone");
        painter.drawText(4600, y, "Email");
        y += 250;

        // 🔹 Requête pour les fournisseurs de ce domaine
        QSqlQuery query;
        query.prepare("SELECT ID_FOURNISSEUR, NOM, ADRESSE, TELEPHONE, EMAIL FROM FOURNISSEUR WHERE DOMAINE = :domaine ORDER BY ID_FOURNISSEUR");
        query.bindValue(":domaine", domaine);
        query.exec();

        painter.setFont(QFont("Helvetica", 10));

        bool hasData = false;
        while (query.next()) {
            hasData = true;
            painter.drawText(100, y, query.value(0).toString());
            painter.drawText(600, y, query.value(1).toString());
            painter.drawText(1600, y, query.value(2).toString());
            painter.drawText(3000, y, query.value(3).toString());
            painter.drawText(4600, y, query.value(4).toString());
            y += 250;

            if (y > 10500) {
                pdf.newPage();
                y = 300;
            }
        }

        if (!hasData) {
            painter.drawText(100, y, "Aucun fournisseur enregistré dans ce domaine.");
            y += 300;
        }

        y += 200;
    }

    painter.end();
    QMessageBox::information(this, "Exportation terminée", "Le fichier PDF a été généré avec succès par domaine !");
}

/* ------------------------- 📊 AFFICHER STATISTIQUES ------------------------- */
void MainWindow::on_btn_statistiques_clicked()
{
    StatistiquesDialog *dialog = new StatistiquesDialog(this);
    dialog->exec();
    delete dialog;
}

/* ------------------------- 📊 EXPORTER VERS GOOGLE SHEETS ------------------------- */
void MainWindow::on_btn_export_google_clicked()
{
    if (ui->tableWidget->rowCount() == 0) {
        QMessageBox::warning(this, "Table vide", "Aucune donnée à exporter. La table est vide.");
        return;
    }
    
    // Demander le nom de la feuille (optionnel)
    bool ok;
    QString sheetName = QInputDialog::getText(
        this,
        "Nom de la feuille",
        "Entrez le nom de la feuille Google Sheets:",
        QLineEdit::Normal,
        "Fournisseurs",
        &ok
    );
    
    if (!ok) {
        return; // Utilisateur a annulé
    }
    
    if (sheetName.isEmpty()) {
        sheetName = "Fournisseurs";
    }
    
    // Exporter vers Google Sheets
    googleSheetsExporter->exporterVersGoogleSheets(ui->tableWidget, "", sheetName);
}

void MainWindow::on_btn_generer_badge_clicked()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Sélection requise", "Veuillez sélectionner un fournisseur dans la table.");
        return;
    }

    QString id = ui->tableWidget->item(row, 0)->text();
    QString nom = ui->tableWidget->item(row, 1)->text();
    QString domaine = ui->tableWidget->item(row, 2)->text();
    QString adresse = ui->tableWidget->item(row, 3)->text();
    QString telephone = ui->tableWidget->item(row, 4)->text();
    QString email = ui->tableWidget->item(row, 5)->text();

    QString photoPath = QFileDialog::getOpenFileName(this, "Sélectionner la photo", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (photoPath.isEmpty()) {
        QMessageBox::warning(this, "Photo requise", "Veuillez sélectionner une photo avant de générer le badge.");
        return;
    }
    QImage photo(photoPath);
    if (photo.isNull()) {
        QMessageBox::warning(this, "Photo invalide", "Impossible de charger la photo sélectionnée.");
        return;
    }

    QString defaultName = QString("badge_%1_%2.pdf").arg(nom).arg(id);
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le badge", defaultName, "Fichier PDF (*.pdf)");
    if (filePath.isEmpty())
        return;

    QPdfWriter pdf(filePath);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setTitle("Badge Fournisseur");

    QPainter painter(&pdf);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRect badgeRect(1000, 2000, 5000, 2800);
    painter.setPen(QPen(Qt::black, 8));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(badgeRect, 100, 100);

    painter.setFont(QFont("Helvetica", 18, QFont::Bold));
    painter.drawText(badgeRect.adjusted(200, 200, -200, -2200), Qt::AlignTop | Qt::AlignHCenter, "Badge Fournisseur");

    painter.setFont(QFont("Helvetica", 16, QFont::Bold));
    painter.drawText(badgeRect.left() + 300, badgeRect.top() + 800, nom);

    painter.setFont(QFont("Helvetica", 11));
    painter.drawText(badgeRect.left() + 300, badgeRect.top() + 1200, QString("ID: %1").arg(id));
    painter.drawText(badgeRect.left() + 300, badgeRect.top() + 1500, QString("Domaine: %1").arg(domaine));
    painter.drawText(badgeRect.left() + 300, badgeRect.top() + 1800, QString("Téléphone: %1").arg(telephone));
    painter.drawText(badgeRect.left() + 300, badgeRect.top() + 2100, QString("Email: %1").arg(email));
    painter.drawText(badgeRect.left() + 300, badgeRect.top() + 2400, QString("Adresse: %1").arg(adresse));

    QRect photoRect(badgeRect.right() - 1900, badgeRect.top() + 600, 1600, 1800);
    painter.setPen(QPen(Qt::black, 5));
    painter.drawRoundedRect(photoRect, 60, 60);
    QImage scaledPhoto = photo.scaled(photoRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    int px = photoRect.left() + (photoRect.width() - scaledPhoto.width()) / 2;
    int py = photoRect.top() + (photoRect.height() - scaledPhoto.height()) / 2;
    painter.drawImage(QPoint(px, py), scaledPhoto);

    painter.end();
    QMessageBox::information(this, "Badge généré", "Le badge PDF a été généré avec succès.");
}

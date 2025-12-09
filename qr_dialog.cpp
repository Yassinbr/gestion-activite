#include "qr_dialog.h"
#include "qr_activite.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QDebug>

QRDialog::QRDialog(const QList<Activite> &activites, QWidget *parent)
    : QDialog(parent), allActivites(activites), selectedActivite(nullptr)
{
    setWindowTitle("Générateur de Code QR - Activités");
    setGeometry(100, 100, 900, 650);
    setModal(true);
    
    setupUI();
    loadActivites(activites);
}

QRDialog::~QRDialog()
{
    if (selectedActivite) {
        delete selectedActivite;
    }
}

void QRDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Left side: Activites list
    QGroupBox *activitesGroup = new QGroupBox("Sélectionner une Activité", this);
    QVBoxLayout *activitesLayout = new QVBoxLayout(activitesGroup);
    
    activiteListWidget = new QListWidget();
    activiteListWidget->setMaximumWidth(300);
    connect(activiteListWidget, &QListWidget::itemSelectionChanged,
            this, [this]() { onActiviteSelected(activiteListWidget->currentRow()); });
    activitesLayout->addWidget(activiteListWidget);
    
    // Right side: QR code display
    QVBoxLayout *rightLayout = new QVBoxLayout();
    
    QGroupBox *qrGroup = new QGroupBox("Aperçu du Code QR", this);
    QVBoxLayout *qrLayout = new QVBoxLayout(qrGroup);
    
    qrLabel = new QLabel();
    qrLabel->setAlignment(Qt::AlignCenter);
    qrLabel->setStyleSheet("border: 1px solid #ccc; background-color: white;");
    qrLabel->setMinimumSize(400, 400);
    qrLayout->addWidget(qrLabel);
    
    rightLayout->addWidget(qrGroup);
    
    // Buttons
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    
    generateButton = new QPushButton("Générer QR Code");
    generateButton->setEnabled(false);
    connect(generateButton, &QPushButton::clicked, this, &QRDialog::onGenerateQRClicked);
    
    saveButton = new QPushButton("Sauvegarder QR Code");
    saveButton->setEnabled(false);
    connect(saveButton, &QPushButton::clicked, this, &QRDialog::onSaveQRClicked);
    
    closeButton = new QPushButton("Fermer");
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
    
    buttonsLayout->addWidget(generateButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(closeButton);
    
    rightLayout->addLayout(buttonsLayout);
    
    // Main layout: list on left, QR on right
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->addWidget(activitesGroup);
    contentLayout->addLayout(rightLayout);
    
    mainLayout->addLayout(contentLayout);
    
    setLayout(mainLayout);
}

void QRDialog::loadActivites(const QList<Activite> &activites)
{
    for (const Activite &activite : activites) {
        QString itemText = QString("%1 - %2").arg(activite.nom).arg(activite.type);
        activiteListWidget->addItem(itemText);
    }
}

void QRDialog::onActiviteSelected(int row)
{
    if (row >= 0 && row < activiteListWidget->count()) {
        generateButton->setEnabled(true);
        qDebug() << "[QR Dialog] Selected activite at row:" << row;
    }
}

void QRDialog::onGenerateQRClicked()
{
    int row = activiteListWidget->row(activiteListWidget->currentItem());
    if (row < 0 || row >= allActivites.size()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une activité valide");
        return;
    }
    
    if (selectedActivite) {
        delete selectedActivite;
    }
    selectedActivite = new Activite(allActivites[row]);
    
    generateButton->setEnabled(false);
    generateButton->setText("Génération en cours...");
    
    qDebug() << "[QR Dialog] Generating QR code for activite:" << selectedActivite->nom;
    
    // Generate QR code
    currentQRImage = QRCodeGenerator::generateQRCode(*selectedActivite);
    
    if (currentQRImage.isNull()) {
        QMessageBox::critical(this, "Erreur", "Impossible de générer le code QR");
        generateButton->setEnabled(true);
        generateButton->setText("Générer QR Code");
        return;
    }
    
    // Display in label
    QPixmap pixmap = QPixmap::fromImage(currentQRImage);
    qrLabel->setPixmap(pixmap.scaledToWidth(400, Qt::SmoothTransformation));
    
    // Enable save button
    saveButton->setEnabled(true);
    
    generateButton->setEnabled(true);
    generateButton->setText("Générer QR Code");
    
    QMessageBox::information(this, "Succès", 
                             QString("Code QR généré pour:\n%1").arg(selectedActivite->nom));
}

void QRDialog::onSaveQRClicked()
{
    if (currentQRImage.isNull()) {
        QMessageBox::warning(this, "Erreur", "Veuillez d'abord générer un code QR");
        return;
    }
    
    // Try to save with the generator first
    qrFilePath = QRCodeGenerator::generateAndSaveQRCode(*selectedActivite);
    
    if (!qrFilePath.isEmpty()) {
        QMessageBox::information(this, "Succès", 
                                 QString("Code QR sauvegardé avec succès:\n%1").arg(qrFilePath));
        return;
    }
    
    // Fallback: manual save dialog
    QString filePath = QFileDialog::getSaveFileName(this,
                                                    "Sauvegarder le code QR",
                                                    QString("QR_Activite_%1.png").arg(selectedActivite->nom),
                                                    "PNG Images (*.png);;JPEG Images (*.jpg)");
    
    if (!filePath.isEmpty()) {
        if (currentQRImage.save(filePath)) {
            QMessageBox::information(this, "Succès", 
                                     QString("Code QR sauvegardé:\n%1").arg(filePath));
            qrFilePath = filePath;
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de sauvegarder le code QR");
        }
    }
}

#include "commandedialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>
#include <QGroupBox>
#include <QSlider>
#include <QDebug>

CommandeDialog::CommandeDialog(QWidget *parent)
    : QDialog(parent), saved(false)
{
    setWindowTitle("Suggestions de Commandes Intelligentes");
    setGeometry(100, 100, 900, 650);
    setStyleSheet(
        "QDialog { background: #1a1a2e; }"
        "QLabel { color: #ffffff; }"
        "QGroupBox { color: #00ffff; border: 2px solid #00ffff; border-radius: 5px; margin-top: 10px; padding-top: 10px; }"
        "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; padding: 0 5px; color: #00ffff; }"
        "QSpinBox { background: #0a0a1a; color: #ffffff; border: 1px solid #00ffff; border-radius: 4px; padding: 5px; }"
        "QSlider::groove:horizontal { background: #2d2d2d; border: 1px solid #00ffff; border-radius: 4px; height: 8px; }"
        "QSlider::handle:horizontal { background: #00ffff; border: 1px solid #0080ff; border-radius: 4px; width: 18px; margin: -5px 0; }"
        "QSlider::handle:horizontal:hover { background: #0080ff; }"
        "QPushButton { background: #00ffff; color: black; border: 2px solid #00ffff; border-radius: 6px; padding: 8px; font-weight: bold; }"
        "QPushButton:hover { background: #0080ff; color: white; border: 2px solid #0080ff; }"
    );
    buildUI();
}

void CommandeDialog::setSuggestions(const QList<CommandeSuggestion> &suggestions)
{
    this->suggestions = suggestions;
    buildUI();
}

QList<CommandeSuggestion> CommandeDialog::getModifiedSuggestions() const
{
    return modifiedSuggestions;
}

void CommandeDialog::buildUI()
{
    // Nettoyer le layout existant
    if (layout()) {
        QLayoutItem *item;
        while ((item = layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete layout();
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Titre
    QLabel *titleLabel = new QLabel("📋 Ajustez les quantités des commandes suggérées", this);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 13px; color: #00ffff;");
    mainLayout->addWidget(titleLabel);

    // Sous-titre avec instructions
    QLabel *instrLabel = new QLabel("💡 Utilisez le slider, les boutons +/-, ou entrez directement la valeur", this);
    instrLabel->setStyleSheet("font-size: 10px; color: #0080ff; margin-bottom: 10px;");
    mainLayout->addWidget(instrLabel);

    // Zone scrollable pour les suggestions
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);

    // Créer un widget pour chaque suggestion
    for (int i = 0; i < suggestions.size(); ++i) {
        CommandeSuggestion &sugg = const_cast<CommandeSuggestion &>(suggestions[i]);

        QGroupBox *groupBox = new QGroupBox(this);
        QVBoxLayout *groupLayout = new QVBoxLayout(groupBox);

        // Informations fournisseur
        QLabel *fournisseurLabel = new QLabel(QString("Fournisseur: <b>%1</b> (ID %2)")
                                                .arg(sugg.nom_fournisseur).arg(sugg.id_fournisseur), this);
        groupLayout->addWidget(fournisseurLabel);

        // Produit suggéré
        QLabel *produitLabel = new QLabel(QString("Produit: <b>%1</b>").arg(sugg.produit), this);
        groupLayout->addWidget(produitLabel);

    // Ajustement de quantité avec slider, spinbox et boutons +/-
        QHBoxLayout *quantiteLayout = new QHBoxLayout();

        QLabel *quantiteLabel = new QLabel("Quantité: ", this);
        quantiteLayout->addWidget(quantiteLabel);

        // Bouton -
        QPushButton *btnMinus = new QPushButton("-", this);
        btnMinus->setMaximumWidth(40);
        quantiteLayout->addWidget(btnMinus);

        // SpinBox
        QSpinBox *spinBox = new QSpinBox(this);
        spinBox->setMinimum(1);
        spinBox->setMaximum(1000);
        spinBox->setValue(sugg.quantite);
        spinBox->setMinimumWidth(60);
        quantiteLayout->addWidget(spinBox);

        // Slider horizontal pour ajuster avec la souris
        QSlider *slider = new QSlider(Qt::Horizontal, this);
        slider->setMinimum(1);
        slider->setMaximum(1000);
        slider->setValue(sugg.quantite);
        slider->setTickPosition(QSlider::TicksBelow);
        slider->setTickInterval(50);
        quantiteLayout->addWidget(slider);

        // Bouton +
        QPushButton *btnPlus = new QPushButton("+", this);
        btnPlus->setMaximumWidth(40);
        quantiteLayout->addWidget(btnPlus);

        // Label affichant la valeur actuelle
        QLabel *valueLabel = new QLabel(QString::number(sugg.quantite), this);
        valueLabel->setMinimumWidth(40);
        valueLabel->setAlignment(Qt::AlignCenter);
        valueLabel->setStyleSheet("font-weight: bold; color: #00ffff;");
        quantiteLayout->addWidget(valueLabel);

        quantiteLayout->addStretch();

        groupLayout->addLayout(quantiteLayout);

        // Synchroniser slider et spinbox
        connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);
        connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), valueLabel, [valueLabel](int val) {
            valueLabel->setText(QString::number(val));
        });
        connect(slider, &QSlider::valueChanged, valueLabel, [valueLabel](int val) {
            valueLabel->setText(QString::number(val));
        });

        // Connecter les boutons +/- au spinbox
        connect(btnPlus, &QPushButton::clicked, [spinBox]() {
            if (spinBox->value() < spinBox->maximum()) {
                spinBox->setValue(spinBox->value() + 1);
            }
        });

        connect(btnMinus, &QPushButton::clicked, [spinBox]() {
            if (spinBox->value() > spinBox->minimum()) {
                spinBox->setValue(spinBox->value() - 1);
            }
        });

        // Stocker le spinbox dans la structure
        sugg.spinBox = spinBox;

        scrollLayout->addWidget(groupBox);
    }

    scrollLayout->addStretch();
    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    // Boutons d'action
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *saveBtn = new QPushButton("✅ Enregistrer les Commandes", this);
    saveBtn->setMinimumHeight(40);
    connect(saveBtn, &QPushButton::clicked, this, &CommandeDialog::onSaveClicked);

    QPushButton *cancelBtn = new QPushButton("❌ Annuler", this);
    cancelBtn->setMinimumHeight(40);
    cancelBtn->setStyleSheet(
        "QPushButton { background: #ff4444; color: white; border: 2px solid #ff0000; border-radius: 6px; padding: 8px; font-weight: bold; }"
        "QPushButton:hover { background: #ff0000; color: white; border: 2px solid #ff4444; }"
    );
    connect(cancelBtn, &QPushButton::clicked, this, &CommandeDialog::onCancelClicked);

    buttonLayout->addWidget(saveBtn);
    buttonLayout->addWidget(cancelBtn);

    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void CommandeDialog::onSaveClicked()
{
    // Récupérer les quantités modifiées
    modifiedSuggestions.clear();

    for (CommandeSuggestion &sugg : suggestions) {
        if (sugg.spinBox) {
            sugg.quantite = sugg.spinBox->value();
        }
        modifiedSuggestions.append(sugg);
    }

    saved = true;
    accept();
}

void CommandeDialog::onCancelClicked()
{
    saved = false;
    reject();
}

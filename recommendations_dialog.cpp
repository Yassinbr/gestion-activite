#include "recommendations_dialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QDebug>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>

RecommendationsDialog::RecommendationsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Recommandations Détaillées");
    setGeometry(100, 100, 700, 600);
    setModal(true);

    setupUI();
    loadRecommendations();

    if (!recommendations.isEmpty()) {
        currentRecommendation = getRandomRecommendation();
        displayRecommendation(currentRecommendation);
    }
}

RecommendationsDialog::~RecommendationsDialog()
{
}

void RecommendationsDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Title section
    QGroupBox *titleGroup = new QGroupBox("Recommandation", this);
    QVBoxLayout *titleLayout = new QVBoxLayout(titleGroup);
    titleLabel = new QLabel();
    titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2c3e50;");
    titleLabel->setWordWrap(true);
    titleLayout->addWidget(titleLabel);
    mainLayout->addWidget(titleGroup);

    // Category section
    QGroupBox *categoryGroup = new QGroupBox("Catégorie", this);
    QVBoxLayout *categoryLayout = new QVBoxLayout(categoryGroup);
    categoryLabel = new QLabel();
    categoryLabel->setStyleSheet("font-size: 12px; color: #16a085;");
    categoryLayout->addWidget(categoryLabel);
    mainLayout->addWidget(categoryGroup);

    // Description section
    QGroupBox *descGroup = new QGroupBox("Description Détaillée", this);
    QVBoxLayout *descLayout = new QVBoxLayout(descGroup);
    descriptionLabel = new QLabel();
    descriptionLabel->setStyleSheet("font-size: 11px; color: #34495e;");
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    descLayout->addWidget(descriptionLabel);
    mainLayout->addWidget(descGroup, 1);  // This grows

    // Benefit section
    QGroupBox *benefitGroup = new QGroupBox("Avantages", this);
    QVBoxLayout *benefitLayout = new QVBoxLayout(benefitGroup);
    benefitLabel = new QLabel();
    benefitLabel->setStyleSheet("font-size: 11px; color: #27ae60;");
    benefitLabel->setWordWrap(true);
    benefitLayout->addWidget(benefitLabel);
    mainLayout->addWidget(benefitGroup);

    // Buttons section
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    nextButton = new QPushButton("Recommandation Suivante");
    nextButton->setStyleSheet("background-color: #3498db; color: white; padding: 8px; border-radius: 4px;");
    connect(nextButton, &QPushButton::clicked, this, &RecommendationsDialog::onNewRecommendation);

    saveButton = new QPushButton("Enregistrer");
    saveButton->setStyleSheet("background-color: #27ae60; color: white; padding: 8px; border-radius: 4px;");
    connect(saveButton, &QPushButton::clicked, this, &RecommendationsDialog::onSaveRecommendation);

    closeButton = new QPushButton("Fermer");
    closeButton->setStyleSheet("background-color: #e74c3c; color: white; padding: 8px; border-radius: 4px;");
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    buttonsLayout->addWidget(nextButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(closeButton);

    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
}

void RecommendationsDialog::loadRecommendations()
{
    // Recommandations pour activités de loisir et bien-être
    recommendations.append({
        "Activités Aquatiques",
        "Les activités aquatiques comme la natation, le water-polo ou le kayak offrent un excellent exercice cardio-vasculaire tout en étant ludiques et conviviales. Elles sont adaptées à tous les âges et niveaux de forme physique.",
        "Loisir Aquatique",
        "✓ Améliore l'endurance cardio-vasculaire\n✓ Renforce les muscles\n✓ Réduit le stress et l'anxiété\n✓ Convivialité et socialisation"
    });

    recommendations.append({
        "Yoga et Méditation",
        "Le yoga combine exercices physiques et techniques de respiration pour améliorer la flexibilité, l'équilibre et la concentration. C'est une pratique millénaire reconnue pour ses effets relaxants.",
        "Bien-être Spirituel",
        "✓ Améliore la flexibilité et la posture\n✓ Réduit le stress et l'anxiété\n✓ Augmente la conscience corporelle\n✓ Améliore la qualité du sommeil"
    });

    recommendations.append({
        "Sports d'Équipe",
        "Le football, basketball ou volleyball développent l'esprit d'équipe, la communication et l'agilité. Ces sports sont parfaits pour développer des liens sociaux forts.",
        "Sports Collectifs",
        "✓ Développe l'esprit d'équipe\n✓ Améliore la condition physique générale\n✓ Renforce les liens sociaux\n✓ Augmente la confiance en soi"
    });

    recommendations.append({
        "Arts Martiaux",
        "Karaté, judo, taekwondo ou muay thaï enseignent la discipline, l'auto-défense et le respect. Ces disciplines renforcent à la fois le corps et l'esprit.",
        "Combat et Discipline",
        "✓ Améliore la discipline personnelle\n✓ Enseigne l'auto-défense\n✓ Augmente la confiance en soi\n✓ Développe la concentration mentale"
    });

    recommendations.append({
        "Randonnée et Nature",
        "Explorer les sentiers naturels renforce les jambes et les poumons, tout en réduisant le stress. C'est l'occasion parfaite de se reconnecter avec la nature.",
        "Activités Extérieures",
        "✓ Améliore l'endurance et la force\n✓ Réduit le stress et la dépression\n✓ Connexion avec la nature\n✓ Améliore la santé mentale générale"
    });

    recommendations.append({
        "Danse",
        "La danse est une forme d'expression artistique qui améliore la coordination, brûle des calories et libère des endorphines. C'est aussi une activité sociale amusante.",
        "Arts Créatifs",
        "✓ Améliore la coordination et la grâce\n✓ Brûle des calories efficacement\n✓ Expression créative\n✓ Améliore l'humeur et la confiance"
    });

    recommendations.append({
        "Cyclisme",
        "Le cyclisme est une activité à faible impact parfaite pour renforcer les jambes et améliorer la santé cardiovasculaire. Vous pouvez la pratiquer seul ou en groupe.",
        "Activités Outdoor",
        "✓ Excellent exercice cardio-vasculaire\n✓ Faible impact sur les articulations\n✓ Flexibilité de pratique\n✓ Explore de nouveaux lieux"
    });

    recommendations.append({
        "Musculation",
        "L'entraînement avec poids ou machines renforce les muscles et augmente le métabolisme. C'est idéal pour atteindre une silhouette tonifiée et équilibrée.",
        "Fitness",
        "✓ Augmente la masse musculaire\n✓ Élève le métabolisme de base\n✓ Améliore la posture\n✓ Augmente la force et l'endurance"
    });

    recommendations.append({
        "Pilates",
        "Le Pilates se concentre sur le renforcement du core et l'amélioration de la flexibilité. C'est parfait pour les personnes cherchant une activité douce mais efficace.",
        "Bien-être Physique",
        "✓ Renforce les muscles du core\n✓ Améliore la posture et l'équilibre\n✓ Augmente la flexibilité\n✓ Réduit les douleurs dorsales"
    });

    recommendations.append({
        "Tennis",
        "Le tennis est un sport intense qui développe l'agilité, la coordination œil-main et les réflexes. C'est aussi une excellente activité sociale.",
        "Raquette",
        "✓ Améliore l'agilité et les réflexes\n✓ Renforce les jambes et les bras\n✓ Développe la concentration\n✓ Activité sociale et compétitive"
    });

    qDebug() << "[Recommendations] Loaded" << recommendations.size() << "recommendations";
}

Recommendation RecommendationsDialog::getRandomRecommendation()
{
    if (recommendations.isEmpty()) {
        return {"Aucune", "Aucune recommandation disponible", "N/A", "N/A"};
    }

    int randomIndex = QRandomGenerator::global()->bounded(recommendations.size());
    return recommendations[randomIndex];
}

void RecommendationsDialog::displayRecommendation(const Recommendation &rec)
{
    titleLabel->setText(rec.title);
    categoryLabel->setText(QString("📂 %1").arg(rec.category));
    descriptionLabel->setText(rec.description);
    benefitLabel->setText(rec.benefit);

    currentRecommendation = rec;
    qDebug() << "[Recommendations] Displaying:" << rec.title;
}

void RecommendationsDialog::onNewRecommendation()
{
    if (recommendations.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Aucune recommandation disponible");
        return;
    }

    Recommendation nextRec = getRandomRecommendation();
    displayRecommendation(nextRec);
}

void RecommendationsDialog::onSaveRecommendation()
{
    if (saveRecommendationToDB(currentRecommendation)) {
        QString message = QString("Recommandation sauvegardée avec succès:\n\n%1\n\n%2")
                              .arg(currentRecommendation.title)
                              .arg(currentRecommendation.description);
        QMessageBox::information(this, "Recommandation Enregistrée", message);
        qDebug() << "[Recommendations] Saved to DB:" << currentRecommendation.title;
    } else {
        QMessageBox::warning(this, "Erreur", "Impossible de sauvegarder la recommandation en base de données");
    }
}

bool RecommendationsDialog::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isValid() || !db.isOpen()) {
        qDebug() << "[Recommendations] Database not connected";
        return false;
    }
    return true;
}

bool RecommendationsDialog::saveRecommendationToDB(const Recommendation &rec)
{
    if (!connectToDatabase()) {
        qDebug() << "[Recommendations] Failed to connect to database";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    // Insérer dans la table ACTIVITES
    // Les champs telephone, duree, capacite peuvent être NULL
    query.prepare("INSERT INTO ACTIVITES (NOM, TELEPHONE, TYPE, DUREE, CAPACITE) "
                  "VALUES (:nom, NULL, :type, NULL, NULL)");

    query.addBindValue(rec.title);           // NOM = titre de la recommandation
    query.addBindValue(rec.category);        // TYPE = catégorie de la recommandation
    // TELEPHONE, DUREE, CAPACITE seront NULL

    if (!query.exec()) {
        qDebug() << "[Recommendations] SQL Error:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur BD", 
                             QString("Erreur lors de l'enregistrement:\n%1").arg(query.lastError().text()));
        return false;
    }

    qDebug() << "[Recommendations] Successfully saved to ACTIVITES table:" << rec.title;
    return true;
}


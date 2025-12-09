#include "statistiquesdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QColor>

StatistiquesDialog::StatistiquesDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Statistiques des Fournisseurs par Domaine");
    setMinimumSize(800, 600);
    resize(900, 650);

    // Layout principal
    layoutPrincipal = new QVBoxLayout(this);

    // Layout pour les boutons
    layoutBoutons = new QHBoxLayout();
    btnBarres = new QPushButton("📊 Graphique en Barres", this);
    btnCamembert = new QPushButton("🥧 Graphique en Camembert", this);

    btnBarres->setStyleSheet(
        "QPushButton {"
        "    font-family: 'Arial Black';"
        "    font-size: 14px;"
        "    color: white;"
        "    background-color: #0A0A2A;"
        "    border: 2px solid #1E1E5A;"
        "    border-radius: 5px;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1E1E5A;"
        "}"
    );

    btnCamembert->setStyleSheet(
        "QPushButton {"
        "    font-family: 'Arial Black';"
        "    font-size: 14px;"
        "    color: white;"
        "    background-color: #0A0A2A;"
        "    border: 2px solid #1E1E5A;"
        "    border-radius: 5px;"
        "    padding: 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1E1E5A;"
        "}"
    );

    layoutBoutons->addWidget(btnBarres);
    layoutBoutons->addWidget(btnCamembert);
    layoutBoutons->addStretch();

    layoutPrincipal->addLayout(layoutBoutons);

    // Vue du graphique
    chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    layoutPrincipal->addWidget(chartView);

    // Charger les données
    chargerDonnees();

    // Afficher le graphique en barres par défaut
    afficherGraphiqueBarres();

    // Connexions
    connect(btnBarres, &QPushButton::clicked, this, &StatistiquesDialog::afficherGraphiqueBarres);
    connect(btnCamembert, &QPushButton::clicked, this, &StatistiquesDialog::afficherGraphiqueCamembert);
}

StatistiquesDialog::~StatistiquesDialog()
{
}

void StatistiquesDialog::chargerDonnees()
{
    donneesStatistiques.clear();

    QSqlQuery query;
    query.prepare("SELECT DOMAINE, COUNT(*) as nombre FROM FOURNISSEUR GROUP BY DOMAINE ORDER BY nombre DESC, DOMAINE ASC");

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible de charger les statistiques : " + query.lastError().text());
        return;
    }

    while (query.next()) {
        QString domaine = query.value(0).toString();
        int nombre = query.value(1).toInt();
        donneesStatistiques[domaine] = nombre;
    }
}

void StatistiquesDialog::afficherGraphiqueBarres()
{
    if (donneesStatistiques.isEmpty()) {
        QMessageBox::information(this, "Information", "Aucune donnée disponible pour afficher les statistiques.");
        return;
    }

    QBarSeries *series = new QBarSeries();

    QStringList categories;
    QBarSet *set = new QBarSet("Nombre de fournisseurs");

    for (auto it = donneesStatistiques.begin(); it != donneesStatistiques.end(); ++it) {
        categories << it.key();
        *set << it.value();
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Fournisseurs par Domaine");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Nombre de fournisseurs");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->setChart(chart);
}

void StatistiquesDialog::afficherGraphiqueCamembert()
{
    if (donneesStatistiques.isEmpty()) {
        QMessageBox::information(this, "Information", "Aucune donnée disponible pour afficher les statistiques.");
        return;
    }

    QPieSeries *series = new QPieSeries();

    int total = 0;
    for (auto it = donneesStatistiques.begin(); it != donneesStatistiques.end(); ++it) {
        total += it.value();
    }

    // Couleurs pour le camembert
    QStringList couleurs = {
        "#FF6384", "#36A2EB", "#FFCE56", "#4BC0C0", "#9966FF",
        "#FF9F40", "#FF6384", "#C9CBCF", "#4BC0C0", "#FF6384"
    };
    int couleurIndex = 0;

    for (auto it = donneesStatistiques.begin(); it != donneesStatistiques.end(); ++it) {
        QString domaine = it.key();
        int nombre = it.value();
        double pourcentage = (nombre * 100.0) / total;

        QPieSlice *slice = series->append(
            QString("%1\n(%2 - %3%)").arg(domaine).arg(nombre).arg(QString::number(pourcentage, 'f', 1)),
            nombre
        );

        slice->setLabelVisible(true);
        slice->setColor(QColor(couleurs[couleurIndex % couleurs.size()]));
        couleurIndex++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Fournisseurs par Domaine");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    chartView->setChart(chart);
}


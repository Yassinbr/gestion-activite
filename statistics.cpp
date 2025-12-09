#include "statistics.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QFont>
#include <QPainter>


StatisticsDialog::StatisticsDialog(QWidget *parent)
    : QDialog(parent), chartView(nullptr), chart(nullptr)
{
    setWindowTitle("Statistiques des Fournisseurs");
    setGeometry(100, 100, 1000, 700);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Onglets pour différents types de stats
    QTabWidget *tabWidget = new QTabWidget(this);

    // Onglet 1 : Graphique Circulaire (Pie Chart) avec noms
    chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    tabWidget->addTab(chartView, "Répartition par Fournisseur (Pie)");

    // Onglet 2 : Statistiques textuelles détaillées
    QWidget *statsWidget = new QWidget(this);
    QVBoxLayout *statsLayout = new QVBoxLayout(statsWidget);

    QLabel *totalLabel = new QLabel("Statistiques Globales des Fournisseurs", this);
    totalLabel->setStyleSheet("font-weight: bold; font-size: 14px; color: #00ffff;");
    statsLayout->addWidget(totalLabel);

    QLabel *countLabel = new QLabel(this);
    countLabel->setStyleSheet("font-size: 12px;");
    statsLayout->addWidget(countLabel);

    QLabel *idLabel = new QLabel("Liste Complète des Fournisseurs :", this);
    idLabel->setStyleSheet("font-weight: bold; margin-top: 20px; color: #00ffff;");
    statsLayout->addWidget(idLabel);

    // Zone texte pour lister les fournisseurs avec détails
    QLabel *fournisseurList = new QLabel(this);
    fournisseurList->setWordWrap(true);
    fournisseurList->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    fournisseurList->setStyleSheet("background: #1a1a2e; color: #ffffff; padding: 10px; border: 1px solid #00ffff; border-radius: 5px;");
    statsLayout->addWidget(fournisseurList);
    statsLayout->addStretch();

    tabWidget->addTab(statsWidget, "Détails & Informations");

    mainLayout->addWidget(tabWidget);

    // Bouton fermer
    QPushButton *closeBtn = new QPushButton("Fermer", this);
    closeBtn->setStyleSheet(
        "QPushButton {"
        "    background: #0080ff;"
        "    color: white;"
        "    border: 2px solid #00ffff;"
        "    border-radius: 8px;"
        "    padding: 8px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover { background: #00ffff; color: black; }"
    );
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(closeBtn);

    setLayout(mainLayout);
}

void StatisticsDialog::setFournisseursData(const QList<FournisseurStat> &data)
{
    fournisseurs = data;
    displayStatistics();
}

void StatisticsDialog::displayStatistics()
{
    if (fournisseurs.isEmpty()) {
        return;
    }

    createPieChart();
}

void StatisticsDialog::createPieChart()
{
    if (chart) {
        delete chart;
    }

    chart = new QChart();
    chart->setTitle("Répartition des Fournisseurs");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor(26, 26, 46)));
    chart->setTitleBrush(QBrush(QColor(0, 255, 255)));

    QPieSeries *series = new QPieSeries();

    // Palette de couleurs vibrantes pour les slices
    QList<QColor> colors = {
        QColor(0, 255, 255),   // Cyan
        QColor(0, 128, 255),   // Bleu
        QColor(255, 0, 255),   // Magenta
        QColor(0, 255, 128),   // Vert cyan
        QColor(255, 128, 0),   // Orange
        QColor(255, 0, 128),   // Rose
        QColor(128, 0, 255),   // Violet
        QColor(0, 255, 64),    // Vert
    };

    // Chaque fournisseur = une tranche égale
    for (int i = 0; i < fournisseurs.size(); ++i) {
        const FournisseurStat &f = fournisseurs[i];
        QPieSlice *slice = new QPieSlice(f.nom, 1);
        
        // Label avec nom et ID
        QString label = QString("%1\n(ID: %2, Tel: %3)").arg(f.nom).arg(f.id).arg(f.telephone);
        slice->setLabel(label);
        slice->setLabelVisible(true);
        
        // Couleur avec alternance
        QColor sliceColor = colors[i % colors.size()];
        slice->setColor(sliceColor);
        slice->setLabelColor(QColor(255, 255, 255));
        
        series->append(slice);
    }

    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->legend()->setLabelColor(QColor(0, 255, 255));

    chartView->setChart(chart);
}

void StatisticsDialog::createBarChart()
{
    if (chart) {
        delete chart;
    }

    chart = new QChart();
    chart->setTitle("Distribution des Fournisseurs par Initiale");

    // Compter les fournisseurs par première lettre du nom
    QMap<QString, int> initialCounts;
    for (const FournisseurStat &f : fournisseurs) {
        if (!f.nom.isEmpty()) {
            QString initial = f.nom.left(1).toUpper();
            initialCounts[initial]++;
        }
    }

    QBarSet *set0 = new QBarSet("Nombre");
    QStringList categories;

    for (auto it = initialCounts.constBegin(); it != initialCounts.constEnd(); ++it) {
        *set0 << it.value();
        categories << it.key();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);

    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView->setChart(chart);
}

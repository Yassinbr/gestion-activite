#ifndef STATISTIQUESDIALOG_H
#define STATISTIQUESDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QMap>
#include <QPainter>
#include <QtCharts/QChartView>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
QT_END_NAMESPACE

class StatistiquesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatistiquesDialog(QWidget *parent = nullptr);
    ~StatistiquesDialog();

private slots:
    void afficherGraphiqueBarres();
    void afficherGraphiqueCamembert();

private:
    void chargerDonnees();
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutBoutons;
    QChartView *chartView;
    QPushButton *btnBarres;
    QPushButton *btnCamembert;
    QMap<QString, int> donneesStatistiques;
};

#endif // STATISTIQUESDIALOG_H


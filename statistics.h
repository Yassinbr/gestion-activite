#ifndef STATISTICS_H
#define STATISTICS_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QList>
#include <QString>
#include <QPushButton>
#include <QLabel>

struct FournisseurStat {
    int id;
    QString nom;
    QString telephone;
};

// QtCharts types are provided by <QtCharts/...> includes and are available
// in the current global namespace for this project; use the unqualified
// names here for compatibility with how Qt's headers are configured.

class StatisticsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsDialog(QWidget *parent = nullptr);
    void setFournisseursData(const QList<FournisseurStat> &data);
    void displayStatistics();

private:
    QChartView *chartView;
    QChart *chart;
    QList<FournisseurStat> fournisseurs;

    void createPieChart();
    void createBarChart();
};

#endif // STATISTICS_H

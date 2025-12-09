#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
class StatistiquesDialog;
class GoogleSheetsExporter;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_ajouter_clicked();
    void on_btn_modifier_clicked();
    void on_btn_supprimer_clicked();
    void on_btn_rechercher_clicked();
    void on_btn_actualiser_clicked();
    void on_btn_exporter_clicked();  // ✅ Ajout du slot Export PDF
    void on_btn_statistiques_clicked();  // ✅ Slot pour afficher les statistiques
    void on_btn_export_google_clicked();  // ✅ Slot pour exporter vers Google Sheets
    void on_btn_generer_badge_clicked();

private:
    Ui::MainWindow *ui;
    void actualiserTable();
    GoogleSheetsExporter *googleSheetsExporter;
};

#endif // MAINWINDOW_H

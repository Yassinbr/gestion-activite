#ifndef QR_DIALOG_H
#define QR_DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QImage>
#include <QList>

// Forward declaration
struct Activite;

class QRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QRDialog(const QList<Activite> &activites, QWidget *parent = nullptr);
    ~QRDialog();

private slots:
    void onActiviteSelected(int row);
    void onGenerateQRClicked();
    void onSaveQRClicked();

private:
    void setupUI();
    void loadActivites(const QList<Activite> &activites);
    
    QListWidget *activiteListWidget;
    QLabel *qrLabel;
    QPushButton *generateButton;
    QPushButton *saveButton;
    QPushButton *closeButton;
    
    QImage currentQRImage;
    Activite *selectedActivite;
    QString qrFilePath;
    QList<Activite> allActivites;
};

#endif // QR_DIALOG_H

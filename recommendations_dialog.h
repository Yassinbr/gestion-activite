#ifndef RECOMMENDATIONS_DIALOG_H
#define RECOMMENDATIONS_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include <QList>

struct Recommendation {
    QString title;
    QString description;
    QString category;
    QString benefit;
};

class RecommendationsDialog : public QDialog {
    Q_OBJECT

public:
    explicit RecommendationsDialog(QWidget *parent = nullptr);
    ~RecommendationsDialog();

private slots:
    void onNewRecommendation();
    void onSaveRecommendation();

private:
    void setupUI();
    void loadRecommendations();
    Recommendation getRandomRecommendation();
    void displayRecommendation(const Recommendation &rec);
    bool saveRecommendationToDB(const Recommendation &rec);
    bool connectToDatabase();

    QLabel *titleLabel;
    QLabel *descriptionLabel;
    QLabel *categoryLabel;
    QLabel *benefitLabel;
    QPushButton *nextButton;
    QPushButton *saveButton;
    QPushButton *closeButton;

    QList<Recommendation> recommendations;
    Recommendation currentRecommendation;
};

#endif // RECOMMENDATIONS_DIALOG_H


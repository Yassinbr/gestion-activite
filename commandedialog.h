#ifndef COMMANDEDIALOG_H
#define COMMANDEDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <QString>

struct CommandeSuggestion {
    int id_fournisseur;
    QString nom_fournisseur;
    QString produit;
    int quantite;
    QSpinBox *spinBox; // Pour ajuster la quantité
};

class CommandeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommandeDialog(QWidget *parent = nullptr);
    void setSuggestions(const QList<CommandeSuggestion> &suggestions);
    QList<CommandeSuggestion> getModifiedSuggestions() const;

private slots:
    void onSaveClicked();
    void onCancelClicked();

private:
    QList<CommandeSuggestion> suggestions;
    QList<CommandeSuggestion> modifiedSuggestions;
    bool saved;

    void buildUI();
};

#endif // COMMANDEDIALOG_H

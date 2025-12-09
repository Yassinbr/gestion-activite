#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class fournisseur
{
public:
    static bool ajouter(const QString &nom,
                        const QString &domaine,
                        const QString &adresse,
                        int telephone,
                        const QString &email);

    static bool modifier(int id,
                         const QString &nom,
                         const QString &domaine,
                         const QString &adresse,
                         int telephone,
                         const QString &email);

    static bool supprimer(int id);

    static QSqlQueryModel *lister();
    static QSqlQueryModel *rechercher(const QString &texteRecherche);
};

#endif // FOURNISSEUR_H

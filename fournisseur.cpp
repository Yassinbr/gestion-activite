#include "fournisseur.h"

bool fournisseur::ajouter(const QString &nom,
                          const QString &domaine,
                          const QString &adresse,
                          int telephone,
                          const QString &email)
{
    QSqlQuery query;
    query.prepare("INSERT INTO FOURNISSEUR (NOM, DOMAINE, ADRESSE, TELEPHONE, EMAIL) "
                  "VALUES (:nom, :domaine, :adresse, :telephone, :email)");
    query.bindValue(":nom", nom);
    query.bindValue(":domaine", domaine);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    return query.exec();
}

bool fournisseur::modifier(int id,
                           const QString &nom,
                           const QString &domaine,
                           const QString &adresse,
                           int telephone,
                           const QString &email)
{
    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEUR SET NOM=:nom, DOMAINE=:domaine, ADRESSE=:adresse, TELEPHONE=:telephone, EMAIL=:email "
                  "WHERE ID_FOURNISSEUR=:id");
    query.bindValue(":nom", nom);
    query.bindValue(":domaine", domaine);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":id", id);
    return query.exec();
}

bool fournisseur::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FOURNISSEUR WHERE ID_FOURNISSEUR=:id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel *fournisseur::lister()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT ID_FOURNISSEUR, NOM, DOMAINE, ADRESSE, TELEPHONE, EMAIL FROM FOURNISSEUR ORDER BY ID_FOURNISSEUR ASC");
    return model;
}

QSqlQueryModel *fournisseur::rechercher(const QString &texteRecherche)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    bool ok;
    int id = texteRecherche.toInt(&ok);
    if (ok) {
        model->setQuery(QString("SELECT ID_FOURNISSEUR, NOM, DOMAINE, ADRESSE, TELEPHONE, EMAIL FROM FOURNISSEUR WHERE ID_FOURNISSEUR = %1")
                        .arg(id));
    } else {
        QString pattern = "%" + texteRecherche + "%";
        model->setQuery(QString("SELECT ID_FOURNISSEUR, NOM, DOMAINE, ADRESSE, TELEPHONE, EMAIL FROM FOURNISSEUR WHERE LOWER(DOMAINE) LIKE LOWER('%1')")
                        .arg(pattern));
    }
    return model;
}

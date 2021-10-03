#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H


#include <iostream>
#include <QString>
#include <QSqlQueryModel>


class Fournisseur
{
public:
    Fournisseur();
    Fournisseur(int,QString,int,QString,QString);

    int getIdFournisseur();
    QString getNom();
    int getTel();
    QString getRegion();
    QString getCategorie();

    void setIdFournisseur(int);
    void setNom(QString);
    void setTel(int);
    void setRegion(QString);
    void setCategorie(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherBrievement();
    bool supprimer();
    bool modifier();
    QSqlQueryModel* trier(QString);
    QSqlQueryModel* find(Fournisseur);
    QSqlQuery Select(int,QString);
private:
    int IdFournisseur,Tel;
    QString Nom,Region,Categorie;
};


#endif // FOURNISSEUR_H

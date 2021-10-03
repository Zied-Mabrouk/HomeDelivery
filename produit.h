#ifndef PRODUIT_H
#define PRODUIT_H

#include <QString>
#include <QSqlQueryModel>

class Produit
{
public:
    Produit();
    Produit(int,int,int,int,int,int);
    int get_idp();
    int get_idf();
    int get_ids();
    int get_eval();
    int get_prix();
    int get_poids();

    bool ajouter();
    QSqlQueryModel* afficher1();
    QSqlQueryModel* afficher1_1();
    QSqlQueryModel* afficher2();
    QSqlQueryModel* afficher2_1();
    QSqlQueryModel* afficher3();
    QSqlQueryModel* afficher3_1();
    QSqlQueryModel* afficher4();
    QSqlQueryModel* afficher4_1();
    QSqlQueryModel* afficher5();
    QSqlQueryModel* afficher5_1();
    QSqlQueryModel* afficher6();
    QSqlQueryModel* afficher6_1();

    bool supprimer(int);
    bool modifier(int);


private:
    int IdProduit , IdFournisseur, IdStock, Evaluation, Prix, Poids;
};


#endif // PRODUIT_H

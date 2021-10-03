#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class Commande
{public:
    Commande();
    Commande(int,QString,QString,int,int);
    QString get_date_livraison();
    QString get_destination();
    int get_id_produit();
    int get_id_commande();
    int get_id_client();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * affichertri1();
    QSqlQueryModel * affichertri2();
    QSqlQueryModel * affichertri3();


    bool supprimer(int);
    bool modifier(int);
private:
    QString  destination, date_livraison;
    int id_commande,id_produit,id_client;
};

#endif // COMMANDE_H

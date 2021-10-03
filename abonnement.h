#ifndef ABONNEMENT_H
#define ABONNEMENT_H

#include <QString>
#include <QSqlQueryModel>

class abonnement
{
public:
    abonnement();
    abonnement(int,int,int);
        int get_ida();
        int get_nbr();
        int get_idc();


        bool ajouter();
        QSqlQueryModel* afficher1();
        QSqlQueryModel* afficher1_1();
        QSqlQueryModel* afficher2();
        QSqlQueryModel* afficher2_1();
        QSqlQueryModel* afficher3();
        QSqlQueryModel* afficher3_1();


        bool supprimer(int);
        bool modifier(int);
    private:
        int id_abonnement,nbr_commande,id_client;
};

#endif // ABONNEMENT_H

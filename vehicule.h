#ifndef VEHICULE_H
#define VEHICULE_H
#include <QString>
#include <QSqlQueryModel>

class vehicule
{
public:
    vehicule();
    vehicule(int, QString ,int,int);
    int get_idv();
    QString get_date();
    int get_emp();
    int get_cmd();

    bool ajouter();
    QSqlQueryModel* afficher1();
    QSqlQueryModel* afficher1_1();
    QSqlQueryModel* afficher2();
    QSqlQueryModel* afficher2_1();
    QSqlQueryModel* afficher3();
    QSqlQueryModel* afficher3_1();
    QSqlQueryModel* afficher4();
    QSqlQueryModel* afficher4_1();

    bool supprimer(int);
    bool modifier(int);

private:
    int IdVehicule, IdEmploye, IdCommande;
    QString DateLivraison;
};

#endif // VEHICULE_H

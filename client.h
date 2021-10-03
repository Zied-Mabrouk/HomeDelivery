#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQueryModel>
class client
{
public:
    client();
    client(int,QString,QString ,QString ,int,int,int );
    int get_id();
    QString get_nom();
    QString get_prenom();
    QString get_adresse();
    int get_telephone();
    int get_nbr_cmd();
    int get_id_ab();
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
    void ResetClient();
    bool supprimer(int);
    bool modifier(int);
private:
    int id_client ,telephone, nbr_cmd,id_ab;
    QString nom, prenom, adresse;


};


#endif // CLIENT_H

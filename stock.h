#ifndef STOCK_H
#define STOCK_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class stock
{
public:
    stock();
    stock(int id_stock , QString date_ajout  ,QString date_reservation );

    int getid_stock();
    QString  getdate_ajout();
    QString getdate_reservation();

     bool ajouter();
     QSqlQueryModel* afficher();
     QSqlQueryModel* afficher1();
     QSqlQueryModel* afficher11();
     QSqlQueryModel* afficher2();
     QSqlQueryModel* afficher22();
     QSqlQueryModel* afficher3();
     QSqlQueryModel* afficher33();
     QSqlQueryModel *recherche(int);
     bool supprimer(int);
     bool modifier(int);
 private :
     int id_stock;
     QString date_ajout, date_reservation;

};

#endif // STOCK_H

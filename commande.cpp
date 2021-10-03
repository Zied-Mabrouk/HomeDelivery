#include "commande.h"
#include <QDebug>
Commande::Commande()
{
 int id_commande ;
 QString date_livraison;
 QString destination;
 int id_produit;
 int id_client;
}
Commande::Commande(int id_commande,QString date_livraison,QString destination, int id_produit,int id_client)
{
  this->id_commande=id_commande;
  this->date_livraison=date_livraison;
  this->destination=destination;
  this->id_produit=id_produit;
    this->id_client=id_client;
}
int Commande::get_id_produit(){return id_produit;}
QString Commande::get_date_livraison(){return  date_livraison;}
QString Commande::get_destination(){return  destination;}
int Commande::get_id_commande(){return  id_commande;}
int Commande::get_id_client(){return  id_client;}

bool Commande::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO commande (ID_COMMANDE, DATE_LIVRAISON, DESTINATION, ID_PRODUIT,ID_CLIENT) "
                    "VALUES (:id_commande, :date_livraison, :destination , :id_produit,:id_client  )");
query.bindValue(":id_commande", id_commande);
query.bindValue(":date_livraison", date_livraison);
query.bindValue(":destination", destination);
query.bindValue(":id_produit", id_produit);
query.bindValue(":id_client", id_client);

return    query.exec();
}

QSqlQueryModel * Commande::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from COMMANDE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_COMMANDE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_LIVRAISON "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("DESTINATION"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID_PRODUIT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    return model;
}

bool Commande::supprimer(int id_commande)
{
QSqlQuery query;

query.prepare("Delete from commande where id_commande = :id_commande ");
query.bindValue(":id_commande", id_commande);
return    query.exec();
}
bool Commande::modifier(int id_commande)
{
QSqlQuery query;


query.prepare("UPDATE commande SET id_commande=:id_commande, date_livraison=:date_livraison, destination=:destination , id_produit=:id_produit, id_client=:id_client WHERE id_commande=:id_commande ");
query.bindValue(":id_commande", id_commande);
query.bindValue(":date_livraison",date_livraison);
query.bindValue(":destination", destination);
query.bindValue(":id_produit", id_produit);
query.bindValue(":id_client", id_client);
return    query.exec();
}
QSqlQueryModel * Commande::affichertri1()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from commande order by ID_COMMANDE  DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Livraison "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Destination"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID Client"));

    return model;
}
QSqlQueryModel * Commande::affichertri2()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from commande order by Date_livraison");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Livraison "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Destination"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID Produit"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID Client"));
    return model;
}

QSqlQueryModel * Commande::affichertri3()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from commande order by Destination");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Commande"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Livraison "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Destination"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("ID Produit"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID Client"));

    return model;
}



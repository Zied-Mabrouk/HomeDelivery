#include "abonnement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
abonnement::abonnement()
{
 id_abonnement=0 ;
 nbr_commande=0;
 id_client=0;
}
abonnement::abonnement(int id_abonnement,int nbr_commande,int id_client)
{

    this->id_abonnement = id_abonnement;
    this->nbr_commande = nbr_commande;
    this->id_client = id_client;
}
int abonnement::get_ida() {return id_abonnement;}
int abonnement::get_nbr(){return nbr_commande;}
int abonnement::get_idc(){return id_client ;}

bool abonnement::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO abonnement (id_abonnement, nbr_commande, id_client) "
                  "VALUES (:id_abonnement, :nbr_commande, :id_client)");
    query.bindValue(":id_abonnement", id_abonnement);
    query.bindValue(":nbr_commande", nbr_commande);
    query.bindValue(":id_client", id_client);

    return query.exec();
}
bool abonnement::supprimer(int id_abonnement)
{
    QSqlQuery query;
    query.prepare(" Delete from abonnement where id_abonnement=:id_abonnement");
    query.bindValue(":id_abonnement", id_abonnement);
    return query.exec();
}
bool abonnement::modifier(int id_abonnement )
{
    QSqlQuery query;

    query.prepare("UPDATE abonnement SET id_abonnement=:id_abonnement ,nbr_commande=:nbr_commande ,id_client=:id_client  where id_abonnement=:id_abonnement ");
    query.bindValue(":id_abonnement", id_abonnement);
    query.bindValue(":nbr_commande", nbr_commande);
    query.bindValue(":id_client", id_client);

    return query.exec();
}

QSqlQueryModel *abonnement::afficher1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM abonnement order by id_abonnement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_abonnement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbr_commande"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id_client"));
    return  model;
}
QSqlQueryModel *abonnement::afficher1_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM abonnement order by id_abonnement desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_abonnement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbr_commande"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id_client"));
    return  model;
}

QSqlQueryModel *abonnement::afficher2()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM abonnement order by nbr_commande");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_abonnement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbr_commande"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id_client"));
    return  model;
}
QSqlQueryModel *abonnement::afficher2_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM abonnement order by nbr_commande desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_abonnement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbr_commande"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id_client"));
    return  model;
}
QSqlQueryModel *abonnement::afficher3()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM abonnement order by id_client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_abonnement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbr_commande"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id_client"));
    return  model;
}
QSqlQueryModel *abonnement::afficher3_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM abonnement order by id_client desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_abonnement"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nbr_commande"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("id_client"));
    return  model;
}

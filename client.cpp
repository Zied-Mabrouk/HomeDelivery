#include "client.h"
#include <QSqlQuery>

#include <QtDebug>
#include <QObject>
#include<vector>

client::client()
{
    id_client =0;
    nom = "";
    prenom= "";
    adresse ="";
    telephone=0;
    nbr_cmd = 0;
    id_ab = 0;
}

client::client(int id_client, QString nom, QString prenom,QString adresse, int telephone, int nbr_cmd, int id_ab)
{
    this->id_client = id_client;
    this->nom = nom;
    this->prenom = prenom;
    this->adresse = adresse;
    this->telephone = telephone;
    this->nbr_cmd = nbr_cmd;
    this->id_ab = id_ab;
}
int client::get_id(){return id_client;}
QString client:: get_nom(){return nom ;}
QString client:: get_prenom(){return prenom;}
QString client:: get_adresse(){return adresse;}
int client:: get_telephone(){return telephone;}
int client:: get_nbr_cmd(){return nbr_cmd;}
int client:: get_id_ab(){return id_ab;}
bool client::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO client (id_client, nom, prenom,adresse,telephone,nbr_cmd,id_ab ) "
                  "VALUES (:id_client, :nom, :prenom, :adresse, :telephone, :nbr_cmd,:id_ab)");
    query.bindValue(":id_client", id_client);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":nbr_cmd", nbr_cmd);
    query.bindValue(":id_ab", id_ab);
    return query.exec();

}
bool client::supprimer(int id_client)
{
    QSqlQuery query;
    query.prepare(" Delete from client where id_client=:id_client");
    query.bindValue(":id_client", id_client);
    return query.exec();
}

bool client::modifier(int id_client )
{
    QSqlQuery query;

    query.prepare("UPDATE client SET id_client=:id_client ,nom=:nom ,prenom=:prenom ,adresse=:adresse ,telephone=:telephone ,nbr_cmd=:nbr_cmd  where id_client=:id_client ");
    query.bindValue(":id_client", id_client);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":nbr_cmd", nbr_cmd);
    query.bindValue(":id_ab", id_ab);
    return query.exec();
}

QSqlQueryModel *client::afficher1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by id_client  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab"));

    return  model;
}
QSqlQueryModel *client::afficher1_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by id_client desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}

QSqlQueryModel *client::afficher2()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by nom desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}
QSqlQueryModel *client::afficher2_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by nom desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}
QSqlQueryModel *client::afficher3()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by prenom desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}
QSqlQueryModel *client::afficher3_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by prenom desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}
QSqlQueryModel *client::afficher4()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by adresse desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}
QSqlQueryModel *client::afficher4_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by adresse desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}
QSqlQueryModel *client::afficher5()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by telephone desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}
QSqlQueryModel *client::afficher5_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by telephone desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}
QSqlQueryModel *client::afficher6()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by nbr_cmd desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}
QSqlQueryModel *client::afficher6_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM client order by nbr_cmd desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_client  "));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom  "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom  "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("telephone  "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("nbr_cmd  "));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("id_ab   "));

    return  model;
}

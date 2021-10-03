#include "vehicule.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>

vehicule::vehicule()
{
    IdVehicule = 0;
    DateLivraison="";
    IdEmploye = 0;
    IdCommande=0;

}

vehicule::vehicule(int IdVehicule, QString DateLivraison, int IdEmploye, int IdCommande)
{
    this->IdVehicule = IdVehicule;
    this->DateLivraison = DateLivraison;
    this->IdEmploye = IdEmploye;
    this->IdCommande = IdCommande;
}
int vehicule::get_idv(){return IdVehicule;}
QString vehicule:: get_date(){return DateLivraison ;}
int vehicule:: get_emp(){return IdEmploye;}
int vehicule:: get_cmd(){return IdCommande;}
bool vehicule::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO vehicule (IdVehicule, DateLivraison,IdEmploye,IdCommande) "
                  "VALUES (:IdVehicule, :DateLivraison, :IdEmploye, :IdCommande)");
    query.bindValue(":IdVehicule", IdVehicule);
    query.bindValue(":DateLivraison", DateLivraison);
    query.bindValue(":IdEmploye", IdEmploye);
    query.bindValue(":IdCommande", IdCommande);
    return query.exec();

}
bool vehicule::supprimer(int IdVehicule)
{
    QSqlQuery query;
    query.prepare(" Delete from vehicule where IdVehicule=:IdVehicule");
    query.bindValue(":IdVehicule", IdVehicule);
    return query.exec();
}

bool vehicule::modifier(int IdVehicule )
{
    QSqlQuery query;

    query.prepare("UPDATE vehicule SET IdVehicule=:IdVehicule ,DateLivraison=:DateLivraison ,IdEmploye=:IdEmploye ,IdCommande=:IdCommande  where IdVehicule=:IdVehicule ");
    query.bindValue(":IdVehicule", IdVehicule);
    query.bindValue(":DateLivraison", DateLivraison);
    query.bindValue(":IdEmploye", IdEmploye);
    query.bindValue(":IdCommande", IdCommande);
    return query.exec();
}

QSqlQueryModel *vehicule::afficher1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM vehicule order by IdVehicule");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdVehicule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DateLivraison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdEmploye"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IdCommande"));


    return  model;
}
QSqlQueryModel *vehicule::afficher1_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM vehicule ORDER BY IdVehicule desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdVehicule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DateLivraison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdEmploye"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IdCommande"));

    return  model;
}

QSqlQueryModel *vehicule::afficher2()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM vehicule ORDER BY DateLivraison ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdVehicule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DateLivraison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdEmploye"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IdCommande"));

    return  model;
}
QSqlQueryModel *vehicule::afficher2_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM vehicule ORDER BY DateLivraison desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdVehicule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DateLivraison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdEmploye"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IdCommande"));

    return  model;
}
QSqlQueryModel *vehicule::afficher3()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM vehicule ORDER BY IdEmploye ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdVehicule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DateLivraison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdEmploye"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IdCommande"));
    return  model;
}
QSqlQueryModel *vehicule::afficher3_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM vehicule ORDER BY IdEmploye desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdVehicule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DateLivraison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdEmploye"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IdCommande"));

    return  model;
}
QSqlQueryModel *vehicule::afficher4()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM vehicule ORDER BY IdCommande  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdVehicule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DateLivraison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdEmploye"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IdCommande"));

    return  model;
}
QSqlQueryModel *vehicule::afficher4_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM vehicule ORDER BY IdCommande  desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdVehicule"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DateLivraison"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdEmploye"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("IdCommande"));

    return  model;
}


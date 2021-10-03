#include "dialog.h"
#include "ui_dialog.h"
#include "fournisseur.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
Fournisseur::Fournisseur()
{
    IdFournisseur = 0;
    Nom = "", Region = "", Categorie = "", Tel = 0;
}

Fournisseur::Fournisseur(int IdFournisseur, QString Nom, int Tel, QString Region, QString Categorie)
{
    this->IdFournisseur = IdFournisseur;
    this->Nom = Nom;
    this->Tel = Tel;
    this->Region = Region;
    this->Categorie = Categorie;
}

int Fournisseur::getIdFournisseur()
{
    return  IdFournisseur;
}
void Fournisseur::setIdFournisseur(int IdFournisseur)
{
    this->IdFournisseur = IdFournisseur;
}

bool Fournisseur::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO FOURNISSEURS (ID_FOURNISSEUR, NAME, TEL,REGION, CATEGORIE) "
                  "VALUES (:id, :name, :tel, :region, :categorie)");
    query.bindValue(":id", IdFournisseur);
    query.bindValue(":name", Nom);
    query.bindValue(":tel", Tel);
    query.bindValue(":region", Region);
    query.bindValue(":categorie", Categorie);
    return query.exec();
}

bool Fournisseur::supprimer()
{
    QSqlQuery query;
    query.prepare(" Delete from FOURNISSEURS where ID_FOURNISSEUR=:id");
    query.bindValue(0, IdFournisseur);
    return query.exec();
}

bool Fournisseur::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE FOURNISSEURS set ID_FOURNISSEUR=:id,NAME=:nom,TEL=:tel,REGION=:region,CATEGORIE=:categorie where ID_FOURNISSEUR=:id");
    query.bindValue(":id", IdFournisseur);
    query.bindValue(":nom", Nom);
    query.bindValue(":tel", Tel);
    query.bindValue(":region", Region);
    query.bindValue(":categorie", Categorie);
    return query.exec();
}

QSqlQueryModel *Fournisseur::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT* FROM FOURNISSEURS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REGION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CATEGORIE"));

    return  model;
}


QSqlQueryModel *Fournisseur::find(Fournisseur F)
{
    QString Id = QString::number(F.IdFournisseur);
    QSqlQueryModel *model = new QSqlQueryModel();
    QString request = "";
    if(F.IdFournisseur != 0)
        request += "Where ID_FOURNISSEUR LIKE '" + Id + "%'";
    if(!F.Nom.isEmpty())
    {
        if(F.IdFournisseur!=0)
            request += " AND";
        else
            request += "Where";
        request += " NAME LIKE '" + Nom + "%'";
    }
    if(!F.Region.isEmpty())
    {
        if(F.IdFournisseur!=0 || !F.Nom.isEmpty())
            request += " AND";
        else
            request += "Where";
        request += " REGION LIKE '" + Region + "%'";
    }
    model->setQuery("SELECT * FROM FOURNISSEURS " + request);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REGION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CATEGORIE"));

    return  model;
}

QSqlQueryModel *Fournisseur::trier(QString val)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM FOURNISSEURS ORDER BY " + val);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REGION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CATEGORIE"));

    return  model;
}

QSqlQuery Fournisseur::Select(int choice, QString val)
{
    QSqlQuery query;
    QString choix = "";
    switch (choice)
    {
    case 0:
        choix += "ID_FOURNISSEUR";
        break;
    case 1:
        choix += "NAME";
        break;
    case 3:
        choix += "REGION";
        break;
    }
    query.prepare("SELECT * FROM FOURNISSEURS WHERE " + choix + " LIKE '" + val + "%'");

    return query;
}


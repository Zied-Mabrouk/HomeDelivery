#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reclamation.h"
#include "dialog.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <arduino.h>

Reclamation::Reclamation()
{
    IdReclamation = 0;
    IdFournisseur = 0;
    IdClient = 0;
    Desc = "";
    Statut = "En cours";
}

Reclamation::Reclamation(int IdReclamation, int IdFournisseur, int IdClient, QString Desc, QString Statut, QString DateReclamation)
{
    this->IdReclamation = IdReclamation;
    this->IdFournisseur = IdFournisseur;
    this->IdClient = IdClient;
    this->Desc = Desc;
    this->Statut = Statut;
    this->DateReclamation = DateReclamation;
}
int Reclamation::getIdReclamation()
{
    return IdReclamation;
}
int Reclamation::getIdFournisseur()
{
    return  IdFournisseur;
}
int Reclamation::getIdClient()
{
    return IdClient;
}
void Reclamation::setIdReclamation(int IdReclamation)
{
    this->IdReclamation = IdReclamation;
}
void Reclamation::setIdFournisseur(int IdFournisseur)
{
    this->IdFournisseur = IdFournisseur;
}
void Reclamation::setIdClient(int IdClient)
{
    this->IdClient = IdClient;
}
bool Reclamation::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO RECLAMATIONS (ID_RECLAMATION, ID_FOURNISSEUR, ID_CLIENT,DESCRIPTION,STATUT,DATE_RECLAMATION) "
                  "VALUES (:id, :forename, :surname, :desc, :statut, :date)");
    query.bindValue(":id", IdReclamation);
    query.bindValue(":forename", IdFournisseur);
    query.bindValue(":surname", IdClient);
    query.bindValue(":desc", Desc);
    query.bindValue(":statut", Statut);
    query.bindValue(":date", DateReclamation);
    return query.exec();

}
bool Reclamation::supprimer()
{
    QSqlQuery query;
    query.prepare(" Delete from RECLAMATIONS where ID_RECLAMATION=:id");
    query.bindValue(0, IdReclamation);
    return query.exec();
}

bool Reclamation::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE RECLAMATIONS set ID_RECLAMATION=:idr,ID_FOURNISSEUR=:idf,ID_CLIENT=:idc,DESCRIPTION=:desc,STATUT=:statut,DATE_RECLAMATION=:date where ID_RECLAMATION=:idr");
    query.bindValue(":idr", IdReclamation);
    query.bindValue(":idf", IdFournisseur);
    query.bindValue(":idc", IdClient);
    query.bindValue(":desc", Desc);
    query.bindValue(":statut", Statut);
    query.bindValue(":date", DateReclamation);
    return query.exec();
}
boolean checkReclamationState()
{
    boolean check = false;
     QSqlQuery query;
     query.prepare("Select STATUT From RECLAMATIONS");
     while(query.next())
     {
         if(query.value(4)== "En cours")
             check = true;
     }
     return check;
}
QSqlQueryModel *Reclamation::afficher(Arduino *A)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    if(checkReclamationState())
         A->write_to_arduino("1");
    model->setQuery("SELECT * FROM RECLAMATIONS");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RECLAMATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date De Reclamation"));

    return  model;
}

QSqlQueryModel *Reclamation::trier(QString val)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM RECLAMATIONS ORDER BY " + val);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RECLAMATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date De Reclamation"));
    return  model;
}

QSqlQueryModel *Reclamation::find(Reclamation R)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString request = "", idr = QString::number(IdReclamation), idf = QString::number(IdFournisseur), idc = QString::number(IdClient);
    if(R.IdReclamation != 0)
        request += "Where ID_RECLAMATION LIKE '" + idr + "%'";
    if(R.IdFournisseur != 0)
    {
        if(R.IdReclamation != 0)
            request += " AND";
        else
            request += "Where";
        request += " ID_FOURNISSEUR LIKE '" + idf + "%'";
    }
    if(R.IdClient != 0)
    {
        if(R.IdReclamation != 0 || R.IdFournisseur != 0)
            request += " AND";
        else
            request += "Where";
        request += " ID_CLIENT LIKE '" + idc + "%'";
    }

    model->setQuery("SELECT * FROM RECLAMATIONS " + request);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_RECLAMATION"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID_FOURNISSEUR"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ID_CLIENT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date De Reclamation"));
    return  model;
}

QSqlQuery Reclamation::Select(int choice, QString val)
{
    QSqlQuery query;
    QString choix = "";
    switch (choice)
    {
    case 0:
        choix += "ID_RECLAMATION";
        break;
    case 1:
        choix += "ID_FOURNISSEUR";
        break;
    case 2:
        choix += "ID_CLIENT";
        break;
    }
    query.prepare("SELECT * FROM RECLAMATIONS WHERE " + choix + " LIKE '" + val + "%'");
    return query;
}

QSqlQuery Reclamation::getTableFournisseur()
{
    QSqlQuery query;
    if((QString::number(IdFournisseur) != "0"))
        query.prepare("SELECT ID_FOURNISSEUR FROM FOURNISSEURS WHERE ID_FOURNISSEUR LIKE '" + QString::number(IdFournisseur) + "%'");
    else
        query.prepare("SELECT ID_FOURNISSEUR FROM FOURNISSEURS");
    return query;
}
QSqlQuery Reclamation::getTableClient()
{
    QSqlQuery query;
    if((QString::number(IdClient) != "0"))
    query.prepare("SELECT ID_CLIENT FROM CLIENT WHERE ID_CLIENT LIKE '" + QString::number(IdClient) + "%'");
    else
        query.prepare("SELECT ID_CLIENT FROM CLIENT");
    return query;
}


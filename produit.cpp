#include "produit.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>

Produit::Produit()
{
    IdProduit = 0;
    IdFournisseur = 0;
    IdStock = 0;
    Evaluation=0;
    Prix = 0;
    Poids = 0;
}

Produit::Produit(int IdProduit, int IdFournisseur, int IdStock, int Evaluation, int Prix, int Poids)
{
    this->IdProduit = IdProduit;
    this->IdFournisseur = IdFournisseur;
    this->IdStock = IdStock;
    this->Evaluation = Evaluation;
    this->Prix = Prix;
    this->Poids = Poids;
}
int Produit::get_idp(){return IdProduit;}
int Produit:: get_idf(){return IdFournisseur ;}
int Produit:: get_ids(){return IdStock;}
int Produit:: get_eval(){return Evaluation;}
int Produit:: get_prix(){return Prix;}
int Produit:: get_poids(){return Poids;}
bool Produit::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO PRODUIT (IdProduit, IdFournisseur, IdStock,Evaluation,PRIX,POIDS) "
                  "VALUES (:IdProduit, :IdFournisseur, :IdStock, :Evaluation, :PRIX, :POIDS)");
    query.bindValue(":IdProduit", IdProduit);
    query.bindValue(":IdFournisseur", IdFournisseur);
    query.bindValue(":IdStock", IdStock);
    query.bindValue(":Evaluation", Evaluation);
    query.bindValue(":PRIX", Prix);
    query.bindValue(":POIDS", Poids);
    return query.exec();

}
bool Produit::supprimer(int IdProduit)
{
    QSqlQuery query;
    query.prepare(" Delete from PRODUIT where IdProduit=:IdProduit");
    query.bindValue(":IdProduit", IdProduit);
    return query.exec();
}

bool Produit::modifier(int IdProduit )
{
    QSqlQuery query;

    query.prepare("UPDATE PRODUIT SET IdProduit=:IdProduit ,IdFournisseur=:IdFournisseur ,IdStock=:IdStock ,Evaluation=:Evaluation ,Prix=:Prix ,POIDS=:Poids  where IdProduit=:IdProduit ");
    query.bindValue(":IdProduit", IdProduit);
    query.bindValue(":IdFournisseur", IdFournisseur);
    query.bindValue(":IdStock", IdStock);
    query.bindValue(":Evaluation", Evaluation);
    query.bindValue(":Prix", Prix);
    query.bindValue(":Poids", Poids);
    return query.exec();
}

QSqlQueryModel *Produit::afficher1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT order by IdProduit");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));

    return  model;
}
QSqlQueryModel *Produit::afficher1_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY IdProduit desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}

QSqlQueryModel *Produit::afficher2()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY IdFournisseur ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}
QSqlQueryModel *Produit::afficher2_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY IdFournisseur desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}
QSqlQueryModel *Produit::afficher3()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY IdStock ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}
QSqlQueryModel *Produit::afficher3_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY IdStock desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}
QSqlQueryModel *Produit::afficher4()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY Evaluation  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}
QSqlQueryModel *Produit::afficher4_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY Evaluation  desc ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}
QSqlQueryModel *Produit::afficher5()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY PRIX   ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}
QSqlQueryModel *Produit::afficher5_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY PRIX  desc  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}
QSqlQueryModel *Produit::afficher6()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY POIDS    ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}
QSqlQueryModel *Produit::afficher6_1()
{
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRODUIT ORDER BY POIDS  desc  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdProduit"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IdFournisseur"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IdStock"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Evaluation"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("POIDS"));
    return  model;
}



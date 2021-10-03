#include "stock.h"
#include <QDebug>
stock::stock()
{
id_stock=0;
date_ajout="";
date_reservation="";
}

stock::stock(int id_stock, QString date_ajout, QString date_reservation)
{
    this->id_stock=id_stock;
    this->date_ajout=date_ajout;
    this->date_reservation=date_reservation;
}
int stock::getid_stock(){return id_stock;}
QString stock::getdate_ajout(){return date_ajout;}
QString stock::getdate_reservation(){return date_reservation;}

bool stock::ajouter() {

    QSqlQuery query;
    query.prepare("INSERT INTO STOCK (id_stock, date_ajout,date_reservation)"
                  "VALUES (:id_stock, :date_ajout,:date_reservation )");
    query.bindValue(":id_stock", id_stock);
    query.bindValue(":date_ajout", date_ajout);
    query.bindValue(":date_reservation", date_reservation);

    return query.exec();
}

QSqlQueryModel * stock::afficher()
{   QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock order by id_stock");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Ajout"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Reservation"));
    return model;
}
QSqlQueryModel * stock::afficher1()
{   QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock order by id_stock ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Ajout"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Reservation"));
    return model;
}
QSqlQueryModel * stock::afficher11()
{   QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock order by id_stock DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Ajout"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Reservation"));
    return model;
}
QSqlQueryModel * stock::afficher2()
{   QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock order by date_ajout");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Ajout"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Reservation"));
    return model;
}
QSqlQueryModel * stock::afficher22()
{   QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock order by date_ajout DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Ajout"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Reservation"));
    return model;
}
QSqlQueryModel * stock::afficher3()
{   QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock order by date_reservation");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Ajout"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Reservation"));
    return model;
}
QSqlQueryModel * stock::afficher33()
{   QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from stock order by date_reservation desc");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID stock"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Ajout"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Reservation"));
    return model;
}

bool stock::supprimer(int id_stock)
{
    QSqlQuery query;
    query.prepare("Delete from stock where id_stock = :id_stock");
    query.bindValue(":id_stock", id_stock);
    return query.exec();
}

bool stock::modifier(int id_stock)
{
    QSqlQuery query;
    query.prepare("UPDATE STOCK SET id_stock=:id_stock, date_ajout=:date_ajout, date_reservation=:date_reservation where id_stock=:id_stock");
    query.bindValue(":id_stock", id_stock);
    query.bindValue(":date_ajout", date_ajout);
    query.bindValue(":date_reservation", date_reservation);
    return query.exec();

}

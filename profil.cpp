#include "profil.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QDebug>
#include <QObject>
#include <QDateTime>

profil::profil()
{
id=0; user=""; pass="";datec=QDateTime::currentDateTime();mail="";role="";}
profil::profil(int id,QString user,QString pass,QString mail,QString role,QDateTime datec)
{

    this->id=id; this->pass=pass; this->user=user;this->mail=mail;this->datec=datec;this->role=role;

}
    int profil::getid(){return id;}
    QString profil::getuser(){return  user;}
    QString profil::getpass(){return pass;}
    QString profil::getmail(){return mail;}
    QString profil::getrole(){return role;}
    QDateTime profil::getdateC(){return datec;}

    void profil::setid(int id){this->id=id;}
    void profil::setuser(QString user){this->user=user;}
    void profil::setpass(QString pass){this->pass=pass;}
     void profil::setmail(QString mail){this->mail=mail;}
        void profil::setrole(QString role){this->role=role;}
    void profil::setdateC(QDateTime datec){this->datec=datec;}

    bool profil::ajouterP()
    {

        QSqlQuery query;
      QString id_string= QString::number(id);


             query.prepare("INSERT INTO profil (id, username, password, email,role, date_creation) "
                           "VALUES (:id, :username, :password,:email,:role, :date_creation )");
             query.bindValue(":id",id_string);
             query.bindValue(":username", user);
             query.bindValue(":password", pass);
             query.bindValue(":email",mail);

             query.bindValue(":role",role);
             query.bindValue(":date_creation",datec);
            return query.exec();

    }
    bool profil::supprimerP(int id)
    {
        QSqlQuery query;
             query.prepare(" Delete from profil where id=:id");
             query.bindValue(0, id);

            return query.exec();


    }
    QSqlQueryModel* profil::afficherP()
    {
      QSqlQueryModel* model=new QSqlQueryModel();


       model->setQuery("SELECT* FROM profil");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom D'utlisateur"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mot de Passe"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("e-mail"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("role"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("date de creation"));




      return  model;




}
    bool profil::modifier()
    {

        QSqlQuery query;
      QString id_string= QString::number(id);


             query.prepare("UPDATE profil SET  username=:username, password=:password, email=:email,role=:role WHERE id=:id ");

             query.bindValue(":id",id_string);
             query.bindValue(":username", user);
             query.bindValue(":password", pass);
             query.bindValue(":email",mail);

             query.bindValue(":role",role);
             query.bindValue(":date_creation",datec);
            return query.exec();

    }
    QSqlQueryModel*  profil::recherche(QString id ,QString nomu,QString role){




        QSqlQueryModel* model=new QSqlQueryModel();

        QString request =" SELECT * FROM profil where  " ;
       if(!id.isEmpty() )
       { request += " id='";
        request += id;
           request += "'";
           if(!nomu.isEmpty() ||!role.isEmpty() )
                request += " and ";
        }

       if(!nomu.isEmpty() )
       { request += " username='";
        request += nomu;
           request += "'";
           if(!role.isEmpty() )
                request += " and ";}
       if(!role.isEmpty() ){
           request += " role='";
               request += role;
                  request += "'";

}





        model->setQuery(request);

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom D'utlisateur"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mot de Passe"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("e-mail"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("role"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("date de creation"));



return model;

}
    QSqlQueryModel* profil::tri(QString val)
    {
      QSqlQueryModel* model=new QSqlQueryModel();


       model->setQuery("SELECT* FROM profil ORDER BY "+val+" ");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom D'utlisateur"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Mot de Passe"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("e-mail"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("role"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("date de creation"));




      return  model;




}

    bool profil::login(QString user, QString pass){

        QSqlQuery query;

            QString select ="SELECT  id from profil where username=? and password=?";

            query.prepare(select);
            query.addBindValue(user);
             query.addBindValue(pass);
               query.exec();

             if (query.next()){
                 return  true;
             }
             return  false;

    }

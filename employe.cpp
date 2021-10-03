#include "employe.h"
#include <QSqlQuery>

#include <QtDebug>
#include <QObject>
#include<vector>
employe::employe()
{
}
employe::employe(int id,QString nom,QString prenom,int cin,QDate date,int tele,float salaire)
{

    this->id=id; this->nom=nom; this->prenom=prenom;this->cin=cin;this->date=date;this->tele=tele;
    this->salaire=salaire;
}
    int employe::getid(){return id;}
    QString employe::getnom(){return  nom;}
    QString employe::getprenom(){return prenom;}
    int employe::getcin(){return cin;}
    QDate employe::getdate(){return date;}
    int employe::gettele(){return tele;}
    float employe::getsalaire(){return salaire;}
    void employe::setid(int id){this->id=id;}
    void employe::setnom(QString nom){this->nom=nom;}
    void employe::setprenom(QString prenom){this->prenom=prenom;}
    void employe::setcin(int cin){this->cin=cin;}
    void employe::setdate(QDate date){this->date=date;}
    void employe::settele(int tele){this->tele=tele;}
    void employe::setsalaire(float salaire){this->salaire=salaire;}
    bool employe::ajouter()
    {

        QSqlQuery query;
      QString id_string= QString::number(id);
      QString cin_string= QString::number(cin);
      QString tele_string= QString::number(tele);

      QString dateS =date.toString("dd/MM/yyyy");

QString sal_string= QString::number(salaire);
             query.prepare("INSERT INTO employe (id, nom, prenom, cin, date_naissance,telephone,salaire) "
                           "VALUES (:id, :nom, :prenom,:cin, :date_naissance,:telephone,:salaire)");
             query.bindValue(":id",id_string);
             query.bindValue(":nom", nom);
             query.bindValue(":prenom", prenom);
             query.bindValue(":cin",cin_string);
             query.bindValue(":date_naissance",dateS);
             query.bindValue(":telephone",tele_string);
             query.bindValue(":salaire",sal_string);
            return query.exec();








    }
    bool employe::supprimer(int id)
    {
        QSqlQuery query;
             query.prepare(" Delete from employe where id=:id");
             query.bindValue(0, id);

            return query.exec();


    }
    QSqlQueryModel* employe::afficher()
    {
      QSqlQueryModel* model=new QSqlQueryModel();

       model->setQuery("SELECT id, nom, prenom, cin, date_naissance  ,telephone,salaire FROM employe");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


      return  model;




}

    bool employe::modifier()
    {

      QSqlQuery query;
      QString id_string= QString::number(id);
      QString cin_string= QString::number(cin);
      QString tele_string= QString::number(tele);
      QString sal_string= QString::number(salaire);

             query.prepare(" UPDATE employe SET  nom=:nom, prenom=:prenom, cin=:cin, date_naissance=:date_naissance,telephone=:telephone,salaire=:salaire  WHERE id=:id ");
              query.bindValue(":id", id_string);


             query.bindValue(":nom", nom);
             query.bindValue(":prenom", prenom);
             query.bindValue(":cin",cin_string);
             query.bindValue(":date_naissance",date);
             query.bindValue(":telephone",tele_string);
             query.bindValue(":salaire",sal_string);
            return query.exec();

    }

    QSqlQueryModel* employe::recherche_id(QString id)
    {
      QSqlQueryModel* model=new QSqlQueryModel();
QSqlQuery query;



       model->setQuery("SELECT * FROM employe WHERE  (id like '"+id+"')  ");


       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));

query.exec();
      return  model;




}
    QSqlQueryModel* employe::recherche_cin(QString cin)
    {
      QSqlQueryModel* model=new QSqlQueryModel();
QSqlQuery query;



       model->setQuery("SELECT * FROM employe WHERE  ( cin like'"+cin+"')");


       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));

query.exec();
      return  model;




}
    QSqlQueryModel* employe::recherche_tele(QString tele)
    {
      QSqlQueryModel* model=new QSqlQueryModel();
QSqlQuery query;



       model->setQuery("SELECT * FROM employe WHERE  ( telephone like'"+tele+"')");


       model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
       model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));

query.exec();
      return  model;




}
 QSqlQueryModel* employe::trier_n()
 {


     QSqlQueryModel* model=new QSqlQueryModel();


      model->setQuery("SELECT * FROM employe ORDER BY nom ");


      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


     return  model;



 }
 QSqlQueryModel* employe::trier_i()
 {


     QSqlQueryModel* model=new QSqlQueryModel();


      model->setQuery("SELECT * FROM employe ORDER BY id ");


      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


     return  model;



 }
 QSqlQueryModel* employe::trier_p()
 {


     QSqlQueryModel* model=new QSqlQueryModel();


      model->setQuery("SELECT * FROM employe ORDER BY prenom ");


      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


     return  model;



 }
QVector<float> employe::stat()
{
    QSqlQuery q1,q2,q3,q4,q5;
double rows,s1,s2,s3,s4;
rows=0;s2=0;s3=0;s4=0;s1=0;

   q1.prepare("SELECT count (*)  from employe  " );

                   q1.exec();
                    if (q1.next()) {
                    rows= q1.value(0).toInt();}
      q2.prepare("SELECT count (*)  from employe where salaire  between 0 and 500 " );

                                    q2.exec();
                                     if (q2.next()) {
                                    s1= q2.value(0).toInt();}
  q3.prepare("SELECT count (*)  from employe where salaire between 500 and 1000 " );

                                          q3.exec();
                                             if (q3.next()) {
                                            s2= q3.value(0).toInt();}
   q4.prepare("SELECT count (*)  from employe where salaire between 1000 and 2000 " );

                                                                                     q4.exec();
                                                                                        if (q4.next()) {
                                                                                       s3= q4.value(0).toInt();}
   q5.prepare("SELECT count (*)  from employe where salaire > 2000  " );

                                       q5.exec();
                             if (q5.next()) {
                           s4= q5.value(0).toInt();}

QVector<float>stats;
float a1 = (s1/rows)*100;
float a2 = (s2/rows)*100;
float a3 = (s3/rows)*100;
float a4 =  (s4/rows)*100;

stats.push_back(a1);
stats.push_back(a2);
stats.push_back(a3);
stats.push_back(a4);

return stats;
}
QSqlQueryModel* employe::recherche(QString id ,QString cin ,QString tele){

    QSqlQueryModel* model=new QSqlQueryModel();

    QString request =" SELECT * FROM employe where  " ;
   if(!id.isEmpty() )
   { request += " id='";
    request += id;
       request += "'";
       if(!cin.isEmpty() ||!tele.isEmpty() )
            request += " and ";
    }

   if(!cin.isEmpty() )
   { request += " cin='";
    request += cin;
       request += "'";
       if(!tele.isEmpty() )
            request += " and ";}
   if(!tele.isEmpty() ){
       request += " telephone='";
           request += tele;
              request += "'";
    }





    model->setQuery(request);


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("date_naissance"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("salaire"));


   return  model;







}

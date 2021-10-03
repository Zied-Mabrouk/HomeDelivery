#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include<vector>


class employe
{
public:
    employe();
    employe(int,QString,QString,int,QDate,int,float);
    int getid();
    QString getnom();
    QString getprenom();
    int getcin();
    QDate getdate();
    int gettele();
    float getsalaire();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setcin(int);
    void setdate(QDate);
    void settele(int);
    void setsalaire(float);
    bool ajouter();
    bool modifier();
    QSqlQueryModel* trier_n();
     QSqlQueryModel* trier_i();
       QSqlQueryModel* trier_p();
   QSqlQueryModel* recherche_id(QString);
   QSqlQueryModel* recherche_cin(QString);
   QSqlQueryModel* recherche_tele(QString);
   QSqlQueryModel* recherche(QString,QString,QString);


    QSqlQueryModel* afficher();
    bool supprimer(int);
  QVector<float> stat();

private:
int id,cin,tele;
QString nom,prenom;
QDate date;
float salaire;}
;
#endif // EMPLOYE_H

#ifndef PROFIL_H
#define PROFIL_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include <QDateTimeEdit>
class profil
{public:
    profil();
   profil(int,QString,QString,QString,QString,QDateTime);
    int getid();
    QString getuser();
    QString getpass();
     QString getmail();
    QDateTime getdateC();
    QString getrole();

    void setid(int);
    void setuser(QString);
    void setpass(QString);
    void setmail(QString);
    void setrole(QString);
    void setdateC(QDateTime);
    bool ajouterP();
    bool modifier();
    bool login(QString,QString);
    QSqlQueryModel* afficherP();
    bool supprimerP(int);
    QSqlQueryModel* recherche(QString,QString,QString);
  QSqlQueryModel* tri(QString );

private:
int id;
QString user,pass,role,mail;
QDateTime datec;

};

#endif // PROFIL_H

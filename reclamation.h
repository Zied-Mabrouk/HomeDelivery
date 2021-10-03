#ifndef RECLAMATION_H
#define RECLAMATION_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include "arduino.h"

class Reclamation
{
public:
    Reclamation();
    Reclamation(int,int,int,QString,QString,QString);

    int getIdReclamation();
    int getIdFournisseur();
    int getIdClient();
    QString getDesc();
    QString getStatut();
    QDate getDateReclamation();

    void setIdReclamation(int);
    void setIdFournisseur(int);
    void setIdClient(int);
    void setDesc(QString);
    void setStatut(QString);
    void setDateReclamation(QDate);

    bool ajouter();
    QSqlQueryModel* afficher(Arduino*);
    bool supprimer();
    bool modifier();
    QSqlQueryModel* trier(QString);
    QSqlQueryModel* find(Reclamation);
    QSqlQuery Select(int,QString);
    QSqlQuery getTableFournisseur();
    QSqlQuery getTableClient();
private:
    int IdFournisseur,IdClient,IdReclamation;
    QString Desc,Statut,DateReclamation;
};


#endif // RECLAMATION_H

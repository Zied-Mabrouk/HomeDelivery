#ifndef DIALOG_H
#define DIALOG_H
#include "client.h"
#include <QDialog>
#include "reclamation.h"
#include <QMediaPlayer>
#include <QListWidgetItem>
#include "profil.h"
#include "employe.h"
#include<QtCharts>
#include<QChartView>
#include<QLineSeries>
#include <QDate>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <arduino.h>
#include "produit.h"
#include "commande.h"
#include "abonnement.h"
#include "stock.h"
#include "vehicule.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void myfunction();

private slots:
    void on_RemoveR_button_clicked();

    void on_TabR1_activated(const QModelIndex &index);

    void on_AddR_button_clicked();

    void on_EditR_button_clicked();

    void on_ResetR_button_clicked();

    void ResetFournisseur();

    void ResetReclamation();

    void ResetProduit();

    void on_RemoveF_button_clicked();

    void on_AddF_button_clicked();

    void on_EditF_button_clicked();

    void on_ResetF_button_clicked();

    void on_TriR_Idr_clicked();

    void on_TriR_Idf_clicked();

    void on_TriR_Idc_clicked();


    void on_TriF_Id_clicked();

    void on_TriF_Nom_clicked();

    void on_TriF_Prenom_clicked();

    void on_Idf_find_textEdited();

    void on_Nom_find_textEdited();

    void on_Region_find_textEdited();

    void on_Idr_find_textEdited();

    void on_Idf2_find_textEdited();

    void on_Idc_find_textEdited();

    void on_TabF1_activated(const QModelIndex &index);

    void on_PrintR_clicked();

    void on_Idf_input_2_textEdited();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_Idc_input_textEdited();

    void on_Idf_input_2_editingFinished();

    void on_Idc_input_editingFinished();

    void on_listWidget_2_itemClicked(QListWidgetItem *item);

    void on_PrintR_2_clicked();

    void on_Desc_input_textEdited();

    void on_Idr_input_textEdited();

    void on_TabP_activated(const QModelIndex &index);

    void on_AddP_button_clicked();

    void on_ResetP_button_clicked();


    void on_RemoveP_button_clicked();

    void on_TriP_Idp_clicked();

    void on_TriP_Idf_clicked();

    void on_TriP_Ids_clicked();

    void on_pb_ajouterE_clicked();

    void on_pb_updateE_clicked();

    void on_deleteE_clicked();

    void on_tab_employe_activated(const QModelIndex &index);

    void on_Tri_IdE_clicked();

    void on_Tri_nomE_clicked();

    void on_Tri_prenomE_clicked();

    void on_pb_ajouterPr_clicked();

    void on_pb_updatePr_clicked();

    void on_bt_deletePr_clicked();

    void on_Tri_idPr_clicked();

    void on_Tri_userPr_clicked();

    void on_Tri_datePr_clicked();

    void on_find_Employe_clicked();

    void on_find_profil_clicked();

    void on_tab_profil_activated(const QModelIndex &index);

    void on_pb_resetE_clicked();

    void on_pb_reset2_clicked();

    void on_pb_envoyer_clicked();

    void on_PrintE_clicked();

    void on_reload_stat_clicked();

    void on_PrintR_4_clicked();

    Arduino getArduino();

    void update_label();

    void on_SaveP_clicked();

    void on_Psearch_textChanged(const QString &arg1);

    void on_EditP_button_clicked();

    void on_TabC_activated(const QModelIndex &index);

    void on_AddC_button_clicked();

    void on_EditP_button_2_clicked();

    void on_Csearch_textChanged(const QString &arg1);

    void on_RemoveP_button_2_clicked();

    void on_ResetP_button_2_clicked();

    void on_AddP_button_2_clicked();

    void on_TabP_2_activated(const QModelIndex &index);

    void on_EditP_button_3_clicked();

    void on_Psearch_2_textChanged(const QString &arg1);

    void on_RemoveP_button_3_clicked();

    void on_AddP_button_3_clicked();

    void on_EditP_button_4_clicked();

    void on_TabP_3_activated(const QModelIndex &index);

    void on_Psearch_3_textChanged(const QString &arg1);

    void on_RemoveP_button_4_clicked();

    void on_AddP_button_4_clicked();

    void on_TabP_4_activated(const QModelIndex &index);

    void on_EditP_button_5_clicked();



    void on_Psearch_4_textChanged(const QString &arg1);

    void on_ResetP_button_5_clicked();

    void on_RemoveP_button_5_clicked();

    void on_TriP_Idp_5_clicked();

    void on_TriP_Idp_7_clicked();

    void on_TriP_Idf_5_clicked();

    void on_TriP_Idf_7_clicked();

    void on_TriP_Ids_5_clicked();

    void on_TriP_Ids_7_clicked();

    void on_TriP_Idp_4_clicked();

    void on_TriP_Idp_8_clicked();

    void on_TriP_Idf_4_clicked();

    void on_TriP_Idf_8_clicked();

    void on_TriP_Ids_4_clicked();

    void on_TriP_Ids_8_clicked();

    void on_SaveP_4_clicked();

    void on_SaveP_5_clicked();

    void on_SaveP_3_clicked();

    void on_SaveP_2_clicked();


    void on_TriP_Idp_6_clicked();

    void on_TriP_Idp_21_clicked();

    void on_AddP_button_5_clicked();

    void on_RemoveP_button_6_clicked();

    void on_Psearch_5_textChanged(const QString &arg1);

    void on_TabP_5_activated(const QModelIndex &index);

    void on_EditP_button_6_clicked();

    void on_TriP_Ids_6_clicked();

    void on_TriP_Idf_6_clicked();

    void on_TriP_Idp_3_clicked();

    void on_TriP_Idf_3_clicked();

    void on_TriP_Ids_3_clicked();

    void on_TriP_Idf_2_clicked();

    void on_TriP_Idp_2_clicked();

    void on_TriP_Ids_2_clicked();

    void on_SaveP_6_clicked();

private:
    QTimer *timer;
    employe E;
    profil PR;
    Ui::Dialog *ui;
    QBarSeries *series = new QBarSeries();
    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);
    QBarSet *set0 = new QBarSet("100-500");
   QBarSet *set1 = new QBarSet("500-1000");
   QBarSet *set2 = new QBarSet("1000-2000");
   QBarSet *set3 = new QBarSet("+2000");
    QMediaPlayer * sound;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QByteArray data; // variable contenant les données reçues
    Arduino A;
    Produit P;
    client C;
    Commande CM;
    abonnement ab;
    stock e;
    vehicule h;

};

#endif // DIALOG_H

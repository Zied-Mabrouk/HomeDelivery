#include "ui_dialog.h"
#include "reclamation.h"
#include "fournisseur.h"
#include "produit.h"
#include "profil.h"
#include "employe.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "dialog.h"
#include <iostream>
#include <QDebug>
#include <QRadioButton>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include <QVector2D>
#include <QVector>
#include <QSqlQuery>
#include<QDesktopServices>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QDateTime>
#include <QPrinter>
#include <QPrintDialog>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
    ui->TabP_5->setModel(h.afficher1());
     ui->TabP_4->setModel(e.afficher());
    ui->date_ajout->hide();
    ui->TabP_3->setModel(ab.afficher1());
     ui->TabP_2->setModel(CM.afficher());
    ui->TabC->setModel(C.afficher1());
    ui->TelF_input->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idr_input->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idf_input->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idc_input->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idr_remove->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idr_find->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idc_find->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idf_input_2->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idf2_find->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idf_find->setValidator(new QIntValidator(100, 99999999, this));
    ui->Idf_remove->setValidator(new QIntValidator(100, 99999999, this));
    ui->le_id->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_tele->setValidator(new QIntValidator(10000000, 99999999, this));
    ui->le_cin->setValidator(new QIntValidator(10000000, 99999999, this));
    ui->le_sal->setValidator(new QIntValidator(0, 99999999, this));

    Reclamation R;
    Fournisseur F;
    Produit P;
    employe E;
    profil PR;
    sound = new QMediaPlayer();
    sound->setMedia(QUrl("qrc:/sounds/click.mp3"));
    ui->TabR1->setModel(R.afficher(&A));
    ui->TabF1->setModel(F.afficher());
    ui->TabP->setModel(P.afficher1());
    ui->tab_employe->setModel(E.afficher());
    ui->tab_profil->setModel(PR.afficherP());
    ui->listWidget->setVisible(false);
    ui->listWidget_2->setVisible(false);
    ui->comboBox->addItem("En cours");
    ui->comboBox->addItem("Finie");
    QString date = "01/01/2020";
    ui->Date_input->setDate(QDate::fromString(date, "dd/MM/yyyy"));
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

    QVector<float> x;
        employe E3;
         x=E3.stat();
        // QBarSeries *series = new QBarSeries()
                  QBarSet *set0 = new QBarSet("100-500");
                 QBarSet *set1 = new QBarSet("500-1000");
                 QBarSet *set2 = new QBarSet("1000-2000");
                 QBarSet *set3 = new QBarSet("+2000");

                 *set0 << x[0];
                 *set1 << x[1] ;
                 *set2 << x[2] ;
                 *set3 << x[3] ;
         series->append(set0);
         series->append(set1);
         series->append(set2);
         series->append(set3);


       //  QChart *chart = new QChart();

         //chart->legend()->hide();
         chart->addSeries(series);
         chart->createDefaultAxes();
         chart->setTitle("Statistique des salaires");


         chart->legend()->setVisible(true);
         chart->legend()->setAlignment(Qt::AlignBottom);



       //  QChartView *chartView = new QChartView(chart);
           chartView->resize(631,220);
         chartView->setRenderHint(QPainter::Antialiasing);
         chartView->setParent(ui->horizontalFrame);

         manager = new QNetworkAccessManager();
            QObject::connect(manager, &QNetworkAccessManager::finished,
                this, [=](QNetworkReply *reply) {
                    if (reply->error()) {
                        qDebug() << reply->errorString();
                        return;
                    }

                    QString answer = reply->readAll();

                    qDebug() << answer;
                }
            );
}
void Dialog::myfunction()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString time_text = dateTime.toString("dd.MM.yyyy");
    ui->date_ajout->setText(time_text);



}

Dialog::~Dialog()
{
    delete ui;
}
Arduino Dialog::getArduino(){return A;}

void Dialog::on_TabR1_activated(const QModelIndex &index)
{
    Reclamation R;
    QString val;
    int rowx = index.row();
    int columnx = index.column();
    QSqlQuery query;
    if(ui->WidgetR->currentWidget()->objectName() == "RechercheR" && columnx < 3)
    {
        val = ui->TabR1->model()->data(ui->TabR1->model()->index(rowx, columnx)).toString();
        query = R.Select(columnx, val);
    }
    else
    {
        val = ui->TabR1->model()->data(ui->TabR1->model()->index(rowx, 0)).toString();
        query = R.Select(0, val);
    }
    if(query.exec())
    {
        while(query.next())
        {
            if(ui->WidgetR->currentWidget()->objectName() == "SuppressionR")
                ui->Idr_remove->setText(query.value(0).toString());
            else
            {
                if(ui->WidgetR->currentWidget()->objectName() == "AjoutR")
                {
                    ui->Idr_input->setText(query.value(0).toString());
                    ui->Idf_input_2->setText(query.value(1).toString());
                    ui->Idc_input->setText(query.value(2).toString());
                    ui->Desc_input->setText(query.value(3).toString());
                    ui->comboBox->setCurrentText(query.value(4).toString());
                    QDate date = QDate::fromString(query.value(5).toString(), "d/M/yyyy");
                    ui->Date_input->setDate(date);
                    ui->EditR_button->setEnabled(true);
                    ui->Idr_input->setDisabled(true);
                    ui->Idf_input_2->setDisabled(true);
                    ui->Idc_input->setDisabled(true);
                }
                else
                {
                    switch(columnx)
                    {
                    case 0:
                        ui->Idr_find->setText(query.value(0).toString());
                        break;
                    case 1:
                        ui->Idf2_find->setText(query.value(1).toString());
                        break;
                    case 2:
                        ui->Idc_find->setText(query.value(2).toString());
                        break;
                    }
                    on_Idc_find_textEdited();
                }
            }
        }
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }
}

void Dialog::on_TriR_Idr_clicked()
{
    sound->play();
    Reclamation R;
    ui->TabR1->setModel(R.trier("ID_RECLAMATION"));
}

void Dialog::on_TriR_Idf_clicked()
{
    sound->play();
    Reclamation R;
    ui->TabR1->setModel(R.trier("ID_FOURNISSEUR"));
}


void Dialog::on_TriR_Idc_clicked()
{
    sound->play();
    Reclamation R;
    ui->TabR1->setModel(R.trier("ID_CLIENT"));
}


void Dialog::on_AddR_button_clicked()
{
    sound->play();
    int idr = ui->Idr_input->text().toInt();
    int idf = ui->Idf_input_2->text().toInt();
    int idc = ui->Idc_input->text().toInt();
    QString desc = ui->Desc_input->text();
    QString date = ui->Date_input->text();
    QString statut = ui->comboBox->currentText();
    Reclamation R(idr, idf, idc, desc, statut, date);
    bool test = R.ajouter();
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Ajout avec succes.");
        ResetReclamation();
        ui->TabR1->setModel(R.afficher(&A));
    }
    else
    {
        msgBox.setText("Echec d'ajout");
    }
    msgBox.exec();
}


void Dialog::on_EditR_button_clicked()
{
    sound->play();
    int idr = ui->Idr_input->text().toInt();
    int idf = ui->Idf_input_2->text().toInt();
    int idc = ui->Idc_input->text().toInt();
    QString desc = ui->Desc_input->text();
    QString statut = ui->comboBox->currentText();
    QString date = ui->Date_input->text();
    Reclamation R(idr, idf, idc, desc, statut, date);
    bool test = R.modifier();
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Modification avec succes.");
        ui->EditR_button->setEnabled(false);
        ResetReclamation();
        ui->TabR1->setModel(R.afficher(&A));
    }
    else
    {
        msgBox.setText("Echec de modification");
    }
    msgBox.exec();
}

void Dialog::ResetReclamation()
{
    ui->Idr_input->setText("");
    ui->Idf_input_2->setText("");
    ui->Idc_input->setText("");
    ui->Desc_input->setText("");
    ui->comboBox->setCurrentText("En cours");
    QString date = "01/01/2020";
    ui->Date_input->setDate(QDate::fromString(date, "dd/MM/yyyy"));
    ui->Idr_input->setDisabled(false);
    ui->Idf_input_2->setDisabled(false);
    ui->Idc_input->setDisabled(false);
}

void Dialog::on_ResetR_button_clicked()
{
    Reclamation R;
    sound->play();
    ResetReclamation();
    ui->EditR_button->setEnabled(false);
    ui->TabR1->setModel(R.afficher(&A));
    ui->Idr_remove->setText("");
    ui->Idr_find->setText("");
    ui->Idf2_find->setText("");
    ui->Idc_find->setText("");
}
void Dialog::on_RemoveR_button_clicked()
{
    Reclamation R;
    sound->play();
    R.setIdReclamation(ui->Idr_remove->text().toInt());
    bool test = R.supprimer();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("Suppression avec succes.");
        ui->TabR1->setModel(R.afficher(&A));
        ui->EditR_button->setEnabled(false);
        ui->Idr_remove->setText("");
        ui->Idr_find->setText("");
        ui->Idf2_find->setText("");
        ui->Idc_find->setText("");
        ResetReclamation();
    }
    else
    {
        msgBox.setText("Echec de suppression");
    }
    msgBox.exec();
}
void Dialog::on_RemoveF_button_clicked()
{
    sound->play();
    Fournisseur F1;
    F1.setIdFournisseur(ui->Idf_remove->text().toInt());
    bool test = F1.supprimer();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("Suppression avec succes.");
        ui->Idf_remove->setText("");
        ui->TabF1->setModel(F1.afficher());
    }
    else
    {
        msgBox.setText("Echec de suppression");
    }
    msgBox.exec();
}


void Dialog::on_AddF_button_clicked()
{
    sound->play();
    int id = ui->Idf_input->text().toInt();
    QString nom = ui->NameF_input->text();
    int tel = ui->TelF_input->text().toInt();
    QString region = ui->RegionF_input->text();
    QString categorie = ui->CategorieF_input->text();
    Fournisseur F(id, nom, tel, region, categorie);
    bool test = F.ajouter();
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Ajout avec succes.");
        ResetFournisseur();
        ui->TabF1->setModel(F.afficher());
    }
    else
    {
        msgBox.setText("Echec d'ajout");
    }
    msgBox.exec();
}

void Dialog::on_EditF_button_clicked()
{
    sound->play();
    int idf = ui->Idf_input->text().toInt();
    QString nom = ui->NameF_input->text();
    int tel = ui->TelF_input->text().toInt();
    QString region = ui->RegionF_input->text();
    QString categorie = ui->CategorieF_input->text();
    Fournisseur F(idf, nom, tel, region, categorie);
    bool test = F.modifier();
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Modification avec succes.");
        ResetFournisseur();
        ui->EditF_button->setEnabled(false);
        ui->TabF1->setModel(F.afficher());
    }
    else
    {
        msgBox.setText("Echec de modification");
    }
    msgBox.exec();
}

void Dialog::ResetFournisseur()
{
    ui->Idf_input->setText("");
    ui->NameF_input->setText("");
    ui->TelF_input->setText("");
    ui->RegionF_input->setText("");
    ui->CategorieF_input->setText("");
    ui->Idf_input->setDisabled(false);
}
void Dialog::on_ResetF_button_clicked()
{
    Fournisseur F;
    sound->play();
    ResetFournisseur();
    ui->EditF_button->setEnabled(false);
    ui->TabF1->setModel(F.afficher());
    ui->Idf_find->setText("");
    ui->Nom_find->setText("");
    ui->Region_find->setText("");
    ui->Idf_remove->setText("");
}

void Dialog::on_TriF_Id_clicked()
{
    sound->play();
    Fournisseur F;
    ui->TabF1->setModel(F.trier("ID_FOURNISSEUR"));
}

void Dialog::on_TriF_Nom_clicked()
{
    sound->play();
    Fournisseur F;
    ui->TabF1->setModel(F.trier("NAME"));
}

void Dialog::on_TriF_Prenom_clicked()
{
    sound->play();
    Fournisseur F;
    ui->TabF1->setModel(F.trier("REGION"));
}

void Dialog::on_Idf_find_textEdited()
{

    int id = ui->Idf_find->text().toInt();
    QString nom = ui->Nom_find->text();
    QString region = ui->Region_find->text();
    Fournisseur F(id, nom, 0, region, "");
    ui->TabF1->setModel(F.find(F));
}

void Dialog::on_Nom_find_textEdited()
{
    int id = ui->Idf_find->text().toInt();
    QString nom = ui->Nom_find->text();
    QString region = ui->Region_find->text();
    Fournisseur F(id, nom, 0, region, "");
    ui->TabF1->setModel(F.find(F));
}

void Dialog::on_Region_find_textEdited()
{
    int id = ui->Idf_find->text().toInt();
    QString nom = ui->Nom_find->text();
    QString region = ui->Region_find->text();
    Fournisseur F(id, nom, 0, region, "");
    ui->TabF1->setModel(F.find(F));
}

void Dialog::on_Idr_find_textEdited()
{
    sound->play();
    int idr = ui->Idr_find->text().toInt();
    int idf = ui->Idf2_find->text().toInt();
    int idc = ui->Idc_find->text().toInt();
    QString date = ui->Date_input->text();
    Reclamation R(idr, idf, idc, "", "", date);
    ui->TabR1->setModel(R.find(R));
}

void Dialog::on_Idf2_find_textEdited()
{
    sound->play();
    int idr = ui->Idr_find->text().toInt();
    int idf = ui->Idf2_find->text().toInt();
    int idc = ui->Idc_find->text().toInt();
    QString date = ui->Date_input->text();
    Reclamation R(idr, idf, idc, "", "", date);
    ui->TabR1->setModel(R.find(R));
}

void Dialog::on_Idc_find_textEdited()
{
    sound->play();
    int idr = ui->Idr_find->text().toInt();
    int idf = ui->Idf2_find->text().toInt();
    int idc = ui->Idc_find->text().toInt();
    QString date = ui->Date_input->text();
    Reclamation R(idr, idf, idc, "", "", date);
    ui->TabR1->setModel(R.find(R));
}

void Dialog::on_TabF1_activated(const QModelIndex &index)
{
    Fournisseur F;
    QString val;
    bool stop= false;
    int rowx = index.row();
    int columnx = index.column();
    QSqlQuery query;
    if(ui->WidgetF->currentWidget()->objectName() == "RechercheF")
    {
        if(columnx != 2 && columnx < 4){
        val = ui->TabF1->model()->data(ui->TabF1->model()->index(rowx, columnx)).toString();
        query = F.Select(columnx, val); }
        else
            stop=true;
    }
    else
    {
        val = ui->TabF1->model()->data(ui->TabF1->model()->index(rowx, 0)).toString();
        query = F.Select(0, val);
    }
    if(!stop){
    if(query.exec() )
    {
        while(query.next())
        {
            if(ui->WidgetF->currentWidget()->objectName() == "SuppressionF")
                ui->Idf_remove->setText(query.value(0).toString());
            else
            {
                if(ui->WidgetF->currentWidget()->objectName() == "AjoutF")
                {
                    ui->Idf_input->setText(query.value(0).toString());
                    ui->NameF_input->setText(query.value(1).toString());
                    ui->TelF_input->setText(query.value(2).toString());
                    ui->RegionF_input->setText(query.value(3).toString());
                    ui->CategorieF_input->setText(query.value(4).toString());
                    ui->Idf_input->setDisabled(true);
                    ui->EditF_button->setDisabled(false);
                }
                else
                {
                    switch(columnx)
                    {
                    case 0:
                        ui->Idf_find->setText(query.value(0).toString());
                        break;
                    case 1:
                        ui->Nom_find->setText(query.value(1).toString());
                        break;
                    case 3:
                        ui->Region_find->setText(query.value(3).toString());
                        break;
                    }
                    on_Nom_find_textEdited();
                }
            }
        }
    }
    else
    {
        QMessageBox::critical(this, tr("error::"), query.lastError().text());
    }}
}


void Dialog::on_PrintR_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = ui->TabF1->model()->rowCount();
    const int columnCount = ui->TabF1->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        //     "<align='right'> " << datefich << "</align>"
        "<center> <H1>Liste Des Fournisseurs </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->TabF1->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->TabF1->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->TabF1->isColumnHidden(column))
            {
                QString data = ui->TabF1->model()->data(ui->TabF1->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}

void Dialog::on_Idf_input_2_textEdited()
{
    QString idf = ui->Idf_input_2->text();
    Reclamation R;
    QSqlQuery query;
    R.setIdFournisseur(idf.toInt());
    query = R.getTableFournisseur();
    ui->listWidget->setVisible(true);
    ui->listWidget_2->setVisible(false);
    ui->listWidget->clear();
    if(query.exec())
    {
        while(query.next())
            ui->listWidget->addItem(query.value(0).toString());
    }
}

void Dialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->Idf_input_2->setText(item->text());
    ui->listWidget->setVisible(false);
}

void Dialog::on_Idc_input_textEdited()
{
    QString idc = ui->Idc_input->text();
    Reclamation R;
    QSqlQuery query;
    R.setIdClient(idc.toInt());
    query = R.getTableClient();
    ui->listWidget_2->setVisible(true);
    ui->listWidget->setVisible(false);
    ui->listWidget_2->clear();
    if(query.exec())
    {
        while(query.next())
            ui->listWidget_2->addItem(query.value(0).toString());
    }
}

void Dialog::on_Idf_input_2_editingFinished()
{
    ui->listWidget->setVisible(false);
}

void Dialog::on_Idc_input_editingFinished()
{
    ui->listWidget_2->setVisible(false);
}

void Dialog::on_listWidget_2_itemClicked(QListWidgetItem *item)
{
    ui->Idc_input->setText(item->text());
    ui->listWidget_2->setVisible(false);
}

void Dialog::on_PrintR_2_clicked()
{
    QPrinter printer;

    printer.setPrinterName("Reclamation");

    QPrintDialog dialog(&printer, this);

    if(dialog.exec() == QDialog::Rejected)

        return;
}

void Dialog::on_Desc_input_textEdited()
{
    ui->listWidget_2->setVisible(false);
    ui->listWidget->setVisible(false);
}

void Dialog::on_Idr_input_textEdited()
{
    ui->listWidget_2->setVisible(false);
    ui->listWidget->setVisible(false);
}

void Dialog::on_TabP_activated(const QModelIndex &index)
{
    QString val=ui->TabP->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("Select * from produit where IDPRODUIT='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->Idp_input->setText(qry.value(0).toString());
            ui->Idfp_input->setText(qry.value(1).toString());
            ui->Ids_input->setText(qry.value(2).toString());
            ui->Eval_input->setText(qry.value(3).toString());
            ui->Prix_input->setText(qry.value(4).toString());
            ui->Poids_input->setText(qry.value(5).toString());

            ui->EditP_button->setEnabled(true);
           ui->Idp_input->setDisabled(true);
            ui->Idfp_input->setDisabled(true);
            ui->Ids_input->setDisabled(true);

                } }
}

void Dialog::ResetProduit()
{
    ui->Idp_input->setText("");
    ui->Idfp_input->setText("");
    ui->Ids_input->setText("");
    ui->Eval_input->setText("");
    ui->Prix_input->setText("");
    ui->Poids_input->setText("");
    ui->Idp_input->setDisabled(false);
    ui->Idfp_input->setDisabled(false);
    ui->Ids_input->setDisabled(false);
}

void Dialog::on_AddP_button_clicked()
{
    sound->play();
    int idp = ui->Idp_input->text().toInt();
    int idf = ui->Idfp_input->text().toInt();
    int ids = ui->Ids_input->text().toInt();
    int eval = ui->Eval_input->text().toInt();
    int prix = ui->Prix_input->text().toInt();
    int poids = ui->Poids_input->text().toInt();
    Produit P(idp, idf, ids, eval, prix, poids);
    bool test = P.ajouter();
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Ajout avec succes.");
        ResetProduit();
        ui->TabP->setModel(P.afficher1());
    }
    else
    {
        msgBox.setText("Echec d'ajout");
    }
    msgBox.exec();
}

void Dialog::on_ResetP_button_clicked()
{
    Produit P;
    sound->play();
    ResetProduit();
    ui->EditP_button->setEnabled(false);
    ui->TabP->setModel(P.afficher1());

    ui->Idp_remove->setText("");
}




void Dialog::on_RemoveP_button_clicked()
{
    int idproduit = ui->Idp_remove->text().toInt();
    QSqlQuery query;
    query.prepare("Select * from produit where idproduit = ?");
    query.addBindValue(idproduit);
    query.exec();
    if(query.next()) {
    bool test=P.supprimer(idproduit);
    if(test)
    {
        ui->TabP->setModel(P.afficher1());
        QMessageBox::information(nullptr, QObject::tr("DELETE"),
                    QObject::tr("DELETED SUCCESFULLY.\n"
                                "Click Cancel to exit."), QMessageBox::Close);
        ui->Idp_remove->clear();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                    QObject::tr("ID NOT FOUND !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                    QObject::tr("ID NOT FOUND !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
         ui->Idp_remove->clear();
    }


}

void Dialog::on_TriP_Idp_clicked()
{
    sound->play();
    ui->TabP->setModel(P.afficher1());

}

void Dialog::on_TriP_Idf_clicked()
{
    sound->play();
        ui->TabP->setModel(P.afficher2());

}

void Dialog::on_TriP_Ids_clicked()
{
    sound->play();
    ui->TabP->setModel(P.afficher3());
}

void Dialog::on_pb_ajouterE_clicked()
{
    int id = ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int cin = ui->le_cin->text().toInt();
   // QString date=ui->le_date->text();
    int tele = ui->le_tele->text().toInt();
    float salaire = ui->le_sal->text().toFloat();
    QDate date= ui->dateEdit->date();

    QString dateS =date.toString("dd/MM/yyyy");
    QDate d=QDate::fromString(dateS,"dd/MM/yyyy");
 employe E(id,nom,prenom,cin,d,tele,salaire);
 bool test=E.ajouter();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Ajout avec succes.");
     ui->tab_employe->setModel(E.afficher());
 }
 else
     msgBox.setText("Echec d'ajout");
   sound->play();
     msgBox.exec();
}

void Dialog::on_pb_updateE_clicked()
{
    int id = ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int cin = ui->le_cin->text().toInt();
   // QDate date=ui->le_date->text();
    int tele = ui->le_tele->text().toInt();
    float salaire = ui->le_sal->text().toFloat();
  QDate date= ui->dateEdit->date();
 employe E2(id,nom,prenom,cin,date,tele,salaire);
 bool test=E2.modifier();
   sound->play();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("modifier avec succes.");
     ui->tab_employe->setModel(E.afficher());
 }
 else
     msgBox.setText("Echec de modification");
     msgBox.exec();
     ui->tab_employe->setModel(E.afficher());
      sound->play();
}

void Dialog::on_deleteE_clicked()
{

    employe E1; E1.setid(ui->id_delete->text().toInt());
    bool test=E1.supprimer(E1.getid());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
    ui->tab_employe->setModel(E.afficher());

    }
    else
        msgBox.setText("Echec de suppression");
      sound->play();
        msgBox.exec();
}

void Dialog::on_tab_employe_activated(const QModelIndex &index)
{
    employe E3;
     int rowidx = index.row();
    QString id=ui->tab_employe->model()->data(ui->tab_employe->model()->index(rowidx,0)).toString();

 QString nom=ui->tab_employe->model()->data(ui->tab_employe->model()->index(rowidx,1)).toString();
 QString prenom=ui->tab_employe->model()->data(ui->tab_employe->model()->index(rowidx,2)).toString();
 QDate date=ui->tab_employe->model()->data(ui->tab_employe->model()->index(rowidx,4)).toDate();
 QString cin=ui->tab_employe->model()->data(ui->tab_employe->model()->index(rowidx,3)).toString();
 QString telephone=ui->tab_employe->model()->data(ui->tab_employe->model()->index(rowidx,5)).toString();
    QString salaire=ui->tab_employe->model()->data(ui->tab_employe->model()->index(rowidx,6)).toString();
if(ui->tabWidget->currentIndex()==0){
     ui->le_id->setText(id);
     ui->le_id->setDisabled(true);
     ui->le_nom->setText(nom);
     ui->le_prenom->setText(prenom);
     ui->dateEdit->setDate(date);
     ui->le_cin->setText(cin);
     ui->le_tele->setText(telephone);
       ui->le_sal->setText(salaire);}
else if(ui->tabWidget->currentIndex()==1)
    ui->id_delete->setText(id);
sound->play();
}

void Dialog::on_Tri_IdE_clicked()
{
     ui->tab_employe->setModel(E.trier_i()); sound->play();
}

void Dialog::on_Tri_nomE_clicked()
{
    ui->tab_employe->setModel(E.trier_n()); sound->play();
}

void Dialog::on_Tri_prenomE_clicked()
{
     ui->tab_employe->setModel(E.trier_p()); sound->play();
}

void Dialog::on_pb_ajouterPr_clicked()
{
    int id  = ui->le_id2->text().toInt();
       QString user=ui->le_user->text();
       QString pass=ui->le_pass->text();
       QString  mail=ui->le_mail->text();
       QString role=ui->le_role->text();
   QDateTime date=QDateTime::currentDateTime();
   QString datec=date.toString("dd.MM.yyyy");
    profil P(id,user,pass,mail,role,date);
     QMessageBox msgBox;
    if(mail.contains(QRegExp("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$"))){


    bool test=P.ajouterP();

    if(test)
      {
        msgBox.setText("Ajout avec succes.");
        ui->tab_profil->setModel(P.afficherP());
    }
    else
        msgBox.setText("changer l'id");

   }
          else
            msgBox.setText("Adresse mail incorrect");
              sound->play();
            msgBox.exec();
}

void Dialog::on_pb_updatePr_clicked()
{ int id  = ui->le_id2->text().toInt();
    QString user=ui->le_user->text();
    QString pass=ui->le_pass->text();
    QString  mail=ui->le_mail->text();
    QString role=ui->le_role->text();
QDateTime date=QDateTime::currentDateTime();
QString datec=date.toString("dd.MM.yyyy");
 profil P2(id,user,pass,mail,role,date);
 bool test=P2.modifier();
 QMessageBox msgBox;

 if(test)
   {  msgBox.setText("Modification avec succes.");
     ui->tab_profil->setModel(PR.afficherP());
 }
 else
     msgBox.setText("Echec de modification");
   sound->play();
     msgBox.exec();

}

void Dialog::on_bt_deletePr_clicked()
{profil P1; P1.setid(ui->le_delete->text().toInt());
    bool test=P1.supprimerP(P1.getid());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
    ui->tab_profil->setModel(PR.afficherP());

    }
    else
        msgBox.setText("Echec de suppression");
      sound->play();
        msgBox.exec();


}

void Dialog::on_Tri_idPr_clicked()
{profil P2;
    QString val="id";
  ui->tab_profil->setModel( P2.tri(val)) ;
sound->play();

}

void Dialog::on_Tri_userPr_clicked()
{ profil P2;
    QString val="username";
  ui->tab_profil->setModel( P2.tri(val)) ;
sound->play();

}

void Dialog::on_Tri_datePr_clicked()
{profil P2;
    QString val="date_creation";
  ui->tab_profil->setModel( P2.tri(val)) ;
sound->play();

}

void Dialog::on_find_Employe_clicked()
{
    QMessageBox msgBox;
        employe E3;
        QString tele=ui->tele_find->text();
        QString id=ui->id_find->text();
        QString cin=ui->cin_find->text();
        if(ui->id_find->text().isEmpty() && ui->cin_find->text().isEmpty() && ui->tele_find->text().isEmpty()  ){
             msgBox.setText("line edit est vide");}
       else{
             ui->tab_employe->setModel(E3.recherche(id,cin,tele));
             msgBox.setText("recherche effectuer");}

      sound->play();
       msgBox.exec();

}

void Dialog::on_find_profil_clicked()
{
    QMessageBox msgBox;
        profil P3;
        QString user=ui->user_find->text();
        QString id=ui->id2_find->text();
        QString role=ui->role_find->text();
        if(ui->id2_find->text().isEmpty() && ui->role_find->text().isEmpty() && ui->user_find->text().isEmpty()  ){
             msgBox.setText("line edit est vide");}
       else{
             ui->tab_profil->setModel(P3.recherche(id,user,role));
               msgBox.setText("recherche effectuer");}

    sound->play();
       msgBox.exec();

}

void Dialog::on_tab_profil_activated(const QModelIndex &index)
{
    profil P3;
        int rowidx = index.row();
       QString id=ui->tab_profil->model()->data(ui->tab_profil->model()->index(rowidx,0)).toString();

    QString nom=ui->tab_profil->model()->data(ui->tab_profil->model()->index(rowidx,1)).toString();
    QString prenom=ui->tab_profil->model()->data(ui->tab_profil->model()->index(rowidx,2)).toString();

    QString cin=ui->tab_profil->model()->data(ui->tab_profil->model()->index(rowidx,3)).toString();
    QString telephone=ui->tab_profil->model()->data(ui->tab_profil->model()->index(rowidx,4)).toString();
    if(ui->tabWidget_2->currentIndex()==0){

        ui->le_id2->setText(id);
           ui->le_id2->setDisabled(true);
        ui->le_user->setText(nom);
        ui->le_pass->setText(prenom);

        ui->le_mail->setText(cin);
        ui->le_role->setText(telephone);}
    else if(ui->tabWidget->currentIndex()==1)
         ui->le_delete->setText(id);
     sound->play();
}

void Dialog::on_pb_resetE_clicked()
{
    ui->le_id->clear();
    ui->le_nom->clear();
    ui->le_prenom->clear();
    ui->dateEdit->clear();
    ui->le_cin->clear();
    ui->le_tele->clear();
      ui->le_sal->clear();
       ui->le_id->setDisabled(false);
    sound->play();
}

void Dialog::on_pb_reset2_clicked()
{ ui->le_id2->clear();
    ui->le_id2->setDisabled(false);
    ui->le_user->clear();
    ui->le_pass->clear();
    ui->le_mail->clear();
    ui->le_role->clear();
     sound->play();

}

void Dialog::on_pb_envoyer_clicked()
{QMessageBox msgBox;
    QString mail=ui->le_envoyer->text();
    QString objet=ui->le_objet->text();
    QString msg=ui->te_mail->toPlainText();
    if(mail.contains(QRegExp("^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$")))
    {request.setUrl(QUrl("http://playpals.io/mailerkhalilsecret.php?email="+mail+"&subject="+objet+"&content="+msg+"&psw=testttesttttaztatga"));
         manager->get(request);
          msgBox.setText("mail envoyer");
    }
    else
      msgBox.setText("adresse  mail incorrect");
      sound->play();
     msgBox.exec();

}

void Dialog::on_PrintE_clicked()
{
    QPrinter printer;

    printer.setPrinterName("Employe");

    QPrintDialog dialog(&printer, this);

    if(dialog.exec() == QDialog::Rejected)

        return;
}

void Dialog::on_reload_stat_clicked()
{
    QVector<float> x;
        employe E3;
         x=E3.stat();





         QBarSeries *series2= new QBarSeries();

         *set0 <<x[0];
         *set1 <<x[1] ;
         *set2 << x[2] ;
         *set3 << x[3] ;


    series2->append(set0);
    series2->append(set1);
    series2->append(set2);
    series2->append(set3);
    chart->removeAllSeries();
     chart->addSeries(series2);
     chartView->update();
     sound->play();
}

void Dialog::on_PrintR_4_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    QDateTime datec=QDateTime::currentDateTime();
    QString date=datec.toString("dd/MM/yyyy");
    const int rowCount = ui->tab_profil->model()->rowCount();
    const int columnCount = ui->tab_profil->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("strTitle")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"

        //     "<align='right'> " << datefich << "</align>"
        "<center> <H1>Liste Des Profils </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tab_profil->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tab_profil->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    out<<"date";

    // data table
    for (int row = 0; row < rowCount; row++)
    {
        out << "<tr> <td bkcolor=0>" << row + 1 << "</td>";
        for (int column = 0; column < columnCount; column++)
        {
            if (!ui->tab_profil->isColumnHidden(column))
            {
                QString data = ui->tab_profil->model()->data(ui->tab_profil->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table> </center>\n"

         <<  "</head>\n"
         "<body bgcolor=#ffffff link=#5000A0>\n"

         //     "<align='right'> " << datefich << "</align>"
         "<right> <H1>"+date+"</H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";
        "</body>\n"
        "</html>\n";

    QString fileName = QFileDialog::getSaveFileName((QWidget * )0, "Sauvegarder en PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
    {
        fileName.append(".pdf");
    }

    QPrinter printer (QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    doc.setHtml(strStream);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);
}

void Dialog::update_label()
{
    data=A.read_from_arduino();

    if(data=="1")

        ui->arduino->setText("reclamation en cours "); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

    else if (data=="0")

        ui->arduino->setText("reclamation finie");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}

void Dialog::on_SaveP_clicked()
{
    QPrinter *imprimante;
       QPrintDialog pd(ui->TabP);
       if(pd.exec()== QDialog::Accepted) return;
       imprimante=pd.printer();
       imprimante->setOutputFormat(QPrinter::PdfFormat);
       imprimante->setOutputFileName("C:/Users/ME/Desktop/pdf/doc.pdf");
}

void Dialog::on_Psearch_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM Produit WHERE IdProduit  LIKE'"+arg1+"%' or IdFournisseur  LIKE'"+arg1+"%' or IdStock  LIKE'"+arg1+"%' or Evaluation like'"+arg1+"%' or Prix  like '"+arg1+"%' or Poids  like '"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->TabP->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->Psearch->clear();}
}

void Dialog::on_EditP_button_clicked()
{

    int IdProduit = ui->Idp_input->text().toInt();
    int IdFournisseur = ui->Idfp_input->text().toInt();
    int IdStock = ui->Ids_input->text().toInt();
    int Evaluation = ui->Eval_input->text().toInt();
    int Prix = ui->Prix_input->text().toInt();
    int Poids = ui->Poids_input->text().toInt();
    Produit P(IdProduit,IdFournisseur,IdStock,Evaluation,Prix,Poids);
    bool test=P.modifier(IdProduit);

    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("MODIFED SUCCESFULLY avec succes.");
        ResetProduit();
        ui->TabP->setModel(P.afficher1());
        ui->EditP_button->setEnabled(false);

    }
    else
    {
        msgBox.setText("ERROR CAN'T MODIFY");
    }
    msgBox.exec();


}

void Dialog::on_TabC_activated(const QModelIndex &index)
{
    QString val=ui->TabC->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("Select * from client where id_client='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->id_client->setText(qry.value(0).toString());
            ui->nom->setText(qry.value(1).toString());
            ui->prenom->setText(qry.value(2).toString());
            ui->adresse->setText(qry.value(3).toString());
            ui->telephone->setText(qry.value(4).toString());
            ui->nbr_cmd->setText(qry.value(5).toString());
            ui->id_ab->setText(qry.value(6).toString());

            ui->EditP_button_2->setEnabled(true);
           ui->id_client->setDisabled(true);
            ui->nbr_cmd->setDisabled(true);
            ui->id_ab->setDisabled(true);

                } }
}

void Dialog::on_AddC_button_clicked()
{
    sound->play();
    int id_client  = ui->id_client->text().toInt();
    QString nom  = ui->nom->text();
    QString prenom  = ui->prenom->text();
    QString adresse  = ui->adresse->text();
    int telephone  = ui->telephone->text().toInt();
    int nbr_cmd  = ui->nbr_cmd->text().toInt();
    int id_ab   = ui->id_ab->text().toInt();
    client c(id_client, nom, prenom, adresse, telephone, nbr_cmd,id_ab);
    bool test = c.ajouter();
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Ajout avec succes.");
        ResetProduit();
        ui->TabC->setModel(c.afficher1());
    }
    else
    {
        msgBox.setText("Echec d'ajout");
    }
    msgBox.exec();
}

void Dialog::on_EditP_button_2_clicked()
{
    int id_client = ui->id_client->text().toInt();
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString adresse = ui->adresse->text();
    int telephone = ui->telephone->text().toInt();
    int nbr_cmd = ui->nbr_cmd->text().toInt();
    int id_ab  = ui->id_ab ->text().toInt();
    client c(id_client,nom,prenom,adresse,telephone,nbr_cmd,id_ab);
    bool test=c.modifier(id_client);

    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("MODIFED SUCCESFULLY avec succes.");
        ResetProduit();
        ui->TabC->setModel(c.afficher1());
        ui->EditP_button_2->setEnabled(false);

    }
    else
    {
        msgBox.setText("ERROR CAN'T MODIFY");
    }
    msgBox.exec();

}

void Dialog::on_Csearch_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM client WHERE id_client  LIKE'"+arg1+"%' or nom  LIKE'"+arg1+"%' or prenom  LIKE'"+arg1+"%' or adresse like'"+arg1+"%' or telephone  like '"+arg1+"%' or nbr_cmd  like '"+arg1+"%'or id_ab   like '"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->TabC->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->Csearch->clear();}
}

void Dialog::on_RemoveP_button_2_clicked()
{
    int id_client= ui->Idc->text().toInt();
    QSqlQuery query;
    query.prepare("Select * from client where id_client = ?");
    query.addBindValue(id_client);
    query.exec();
    if(query.next()) {
    bool test=C.supprimer(id_client);
    if(test)
    {
        ui->TabC->setModel(C.afficher1());
        QMessageBox::information(nullptr, QObject::tr("DELETE"),
                    QObject::tr("DELETED SUCCESFULLY.\n"
                                "Click Cancel to exit."), QMessageBox::Close);
        ui->Idc->clear();

    }
    else
    QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                    QObject::tr("ERROR  !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
     ui->Idc->clear();}
    else
    { QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                    QObject::tr("ID NOT FOUND !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
     ui->Idc->clear();}

}

void Dialog::on_ResetP_button_2_clicked()
{
 ui->id_client ->clear();
 ui->nom ->clear();
 ui-> prenom->clear();
 ui-> adresse->clear();
 ui-> telephone->clear();
 ui->nbr_cmd ->clear();
 ui-> id_ab ->clear();
   ui->id_client->setEnabled(true);
   ui->nbr_cmd->setEnabled(true);
   ui->id_ab->setEnabled(true);


}


void Dialog::on_AddP_button_2_clicked()
{
    sound->play();
    int id_commande  = ui->id_commande->text().toInt();
    QString date_livraison  = ui->date_livraison->text();
    QString destination  = ui->destination->text();
    int  id_produit  = ui->id_produit->text().toInt();
    int id_client= ui->id_cli->text().toInt();

    Commande CM(id_commande,date_livraison,destination, id_produit, id_client);
    bool test = CM.ajouter();
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("ADDED SUCCESFULLY");
        ResetProduit();
        ui->TabP_2->setModel(CM.afficher());
    }
    else
    {
        msgBox.setText("FAILED TO ADD");
    }
    msgBox.exec();
}

void Dialog::on_TabP_2_activated(const QModelIndex &index)
{
    QString val=ui->TabP_2->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("Select * from commande where id_commande='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->id_commande->setText(qry.value(0).toString());
            ui->date_livraison->setText(qry.value(1).toString());
            ui->destination->setText(qry.value(2).toString());
            ui->id_produit->setText(qry.value(3).toString());
            ui->id_cli->setText(qry.value(4).toString());


            ui->EditP_button_3->setEnabled(true);
           ui->id_commande->setDisabled(true);
            ui->id_produit->setDisabled(true);
            ui->id_cli->setDisabled(true);

                } }
}

void Dialog::on_EditP_button_3_clicked()
{
    sound->play();
    int id_commande  = ui->id_commande->text().toInt();
    QString date_livraison  = ui->date_livraison->text();
    QString destination  = ui->destination->text();
    int  id_produit  = ui->id_produit->text().toInt();
    int id_client= ui->id_cli->text().toInt();

    Commande CM(id_commande,date_livraison,destination, id_produit, id_client);
    bool test = CM.modifier(id_commande);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("MODIFED SUCCESFULLY.");
        ResetProduit();
        ui->TabP_2->setModel(CM.afficher());
        ui->EditP_button_3->setEnabled(false);

    }
    else
    {
        msgBox.setText("ERROR CAN'T MODIFY ! ");
    }
    msgBox.exec();
}

void Dialog::on_Psearch_2_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM commande WHERE id_commande  LIKE'"+arg1+"%' or date_livraison  LIKE'"+arg1+"%' or destination  LIKE'"+arg1+"%' or id_produit like'"+arg1+"%' or id_client  like '"+arg1+"%'");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->TabP_2->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->Psearch_2->clear();}
}

void Dialog::on_RemoveP_button_3_clicked()
{

            int id_commande= ui->Idp_remove_3->text().toInt();
            QSqlQuery query;
            query.prepare("Select * from commande where id_commande = ?");
            query.addBindValue(id_commande);
            query.exec();
            if(query.next()) {
            bool test=CM.supprimer(id_commande);
            if(test)
            {
                ui->TabP_2->setModel(CM.afficher());
                QMessageBox::information(nullptr, QObject::tr("DELETE"),
                            QObject::tr("DELETED SUCCESFULLY.\n"
                                        "Click Cancel to exit."), QMessageBox::Close);
                ui->Idp_remove_3->clear();

            }
            else
            QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                            QObject::tr("ERROR  !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             ui->Idp_remove_3->clear();}
            else
            { QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                            QObject::tr("ID NOT FOUND !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             ui->Idp_remove_3->clear();}

}

void Dialog::on_AddP_button_3_clicked()
{
    sound->play();
    int id_abonnement  = ui->id_abonnement->text().toInt();
    int  nbr_commande  = ui->nbr_commande->text().toInt();
    int id_client= ui->id_clie->text().toInt();

    abonnement ab(id_abonnement,nbr_commande,id_client);
    bool test = ab.ajouter();
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("ADDED SUCCESFULLY");
        ResetProduit();
        ui->TabP_3->setModel(ab.afficher1());
        ui->id_abonnement->clear();
        ui->nbr_commande->clear();
        ui->id_clie->clear();
    }
    else
    {
        msgBox.setText("FAILED TO ADD");
        ui->id_abonnement->clear();
        ui->nbr_commande->clear();
        ui->id_clie->clear();
    }
    msgBox.exec();
}

void Dialog::on_EditP_button_4_clicked()
{ int id_abonnement = ui->id_abonnement->text().toInt();
    int nbr_commande = ui->nbr_commande->text().toInt();
    int id_client = ui->id_clie->text().toInt();

    abonnement ab(id_abonnement,nbr_commande,id_client);
    bool test=ab.modifier(id_abonnement);

    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("MODIFED SUCCESFULLY .");
        ResetProduit();
        ui->TabP_3->setModel(ab.afficher1());
        ui->EditP_button_4->setEnabled(false);
        ui->id_abonnement->setEnabled(true);
        ui->id_abonnement->clear();
        ui->nbr_commande->clear();
        ui->id_clie->clear();

    }
    else
    {
        msgBox.setText("ERROR CAN'T MODIFY");
        ui->EditP_button_4->setEnabled(false);
        ui->id_abonnement->setEnabled(true);
        ui->id_abonnement->clear();
        ui->nbr_commande->clear();
        ui->id_clie->clear();
    }
    msgBox.exec();

}

void Dialog::on_TabP_3_activated(const QModelIndex &index)
{
    QString val=ui->TabP_3->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("Select * from abonnement where id_abonnement='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->id_abonnement->setText(qry.value(0).toString());
            ui->nbr_commande->setText(qry.value(1).toString());
            ui->id_clie->setText(qry.value(2).toString());


            ui->EditP_button_4->setEnabled(true);
           ui->id_abonnement->setDisabled(true);


                } }
}

void Dialog::on_Psearch_3_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM abonnement WHERE id_abonnement  LIKE'"+arg1+"%' or nbr_commande  LIKE'"+arg1+"%' or id_client  LIKE'"+arg1+"%' ");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->TabP_3->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->Psearch_3->clear();}
}

void Dialog::on_RemoveP_button_4_clicked()
{

            int id_abonnement= ui->Idp_remove_4->text().toInt();
            QSqlQuery query;
            query.prepare("Select * from abonnement where id_abonnement = ?");
            query.addBindValue(id_abonnement);
            query.exec();
            if(query.next()) {
            bool test=ab.supprimer(id_abonnement);
            if(test)
            {
                ui->TabP_3->setModel(ab.afficher1());
                QMessageBox::information(nullptr, QObject::tr("DELETE"),
                            QObject::tr("DELETED SUCCESFULLY.\n"
                                        "Click Cancel to exit."), QMessageBox::Close);
                ui->Idp_remove_4->clear();

            }
            else
            QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                            QObject::tr("ERROR  !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             ui->Idp_remove_4->clear();}
            else
            { QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                            QObject::tr("ID NOT FOUND !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             ui->Idp_remove_4->clear();}
}


void Dialog::on_AddP_button_4_clicked()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString time_text = dateTime.toString("dd.MM.yyyy hh:mm:ss");
    ui->date_ajout->setText(time_text);
    int id_stock = ui->id_stock->text().toInt();
     QString date_ajout =ui->date_ajout->text();
     QString date_reservation= ui->date_reservation->text();
     stock e(id_stock, date_ajout,date_reservation);
     bool test=e.ajouter();
     if(test)
     { ui->TabP_4->setModel(e.afficher());
         ui->id_stock->clear();
         ui->date_reservation->clear();
         QMessageBox::information(nullptr, QObject::tr("ADD"),
                               QObject::tr("ADDED SUCCESFULLY ! .\n"
                                           "Click Close to exit."), QMessageBox::Close);


     }
     else
         QMessageBox::critical(nullptr, QObject::tr("ADD"),
                     QObject::tr("ERROR.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
     ui->id_stock->clear();
     ui->date_reservation->clear();
}

void Dialog::on_TabP_4_activated(const QModelIndex &index)
{
    QString val=ui->TabP_4->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("Select * from stock where id_stock='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->id_stock->setText(qry.value(0).toString());

            ui->date_reservation->setText(qry.value(2).toString());


            ui->EditP_button_5->setEnabled(true);
           ui->id_stock->setDisabled(true);


                } }
}

void Dialog::on_EditP_button_5_clicked()
{
    sound->play();
    QDateTime dateTime = QDateTime::currentDateTime();
    QString time_text = dateTime.toString("dd.MM.yyyy hh:mm:ss");
    ui->date_ajout->setText(time_text);
    int id_stock  = ui->id_stock->text().toInt();

    QString date_ajout =ui->date_ajout->text();
    QString date_reservation  = ui->date_reservation->text();


    stock e(id_stock,date_ajout,date_reservation);
    bool test = e.modifier(id_stock);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("MODIFED SUCCESFULLY.");
        ResetProduit();
        ui->TabP_4->setModel(e.afficher());
        ui->EditP_button_5->setEnabled(false);
        ui->id_stock->clear();
        ui->date_reservation->clear();
        ui->date_reservation->clear();

       ui->id_stock->setDisabled(false);
       ui->id_stock->clear();
    }
    else
    {
        msgBox.setText("ERROR CAN'T MODIFY ! ");
    }
    msgBox.exec();
}


void Dialog::on_Psearch_4_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM stock WHERE id_stock  LIKE'"+arg1+"%' or date_ajout  LIKE'"+arg1+"%' or date_reservation  LIKE'"+arg1+"%' ");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->TabP_4->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->Psearch_4->clear();}
}

void Dialog::on_ResetP_button_5_clicked()
{
    QSqlQuery query;
    query.prepare("DELETE FROM stock");
    query.exec();
    if(query.exec())
    {
        QMessageBox::critical(nullptr, QObject::tr("DELETE DB "),
                        QObject::tr("ALL ELEMENTS HAS BEEN DELETED !.\n"
                                    "Click Ok to exit."), QMessageBox::Ok);
         ui->TabP_4->setModel(e.afficher());

    }
}

void Dialog::on_RemoveP_button_5_clicked()
{

            int id_stock= ui->Idp_remove_5->text().toInt();
            QSqlQuery query;
            query.prepare("Select * from stock where id_stock = ?");
            query.addBindValue(id_stock);
            query.exec();
            if(query.next()) {
            bool test=e.supprimer(id_stock);
            if(test)
            {
                ui->TabP_4->setModel(e.afficher1());
                QMessageBox::information(nullptr, QObject::tr("DELETE"),
                            QObject::tr("DELETED SUCCESFULLY.\n"
                                        "Click Cancel to exit."), QMessageBox::Close);
                ui->Idp_remove_5->clear();

            }
            else
            QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                            QObject::tr("ERROR  !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             ui->Idp_remove_5->clear();}
            else
            { QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                            QObject::tr("ID NOT FOUND !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             ui->Idp_remove_5->clear();}

}

void Dialog::on_TriP_Idp_5_clicked()
{
     ui->TabP_4->setModel(e.afficher1());

}

void Dialog::on_TriP_Idp_7_clicked()
{
    ui->TabP_4->setModel(e.afficher11());

}

void Dialog::on_TriP_Idf_5_clicked()
{
     ui->TabP_4->setModel(e.afficher2());

}

void Dialog::on_TriP_Idf_7_clicked()
{
    ui->TabP_4->setModel(e.afficher22());

}

void Dialog::on_TriP_Ids_5_clicked()
{
    ui->TabP_4->setModel(e.afficher3());

}

void Dialog::on_TriP_Ids_7_clicked()
{
    ui->TabP_4->setModel(e.afficher33());

}

void Dialog::on_TriP_Idp_4_clicked()
{
     ui->TabP_3->setModel(ab.afficher1());

}

void Dialog::on_TriP_Idp_8_clicked()
{
    ui->TabP_3->setModel(ab.afficher1_1());

}

void Dialog::on_TriP_Idf_4_clicked()
{
    ui->TabP_3->setModel(ab.afficher2());

}

void Dialog::on_TriP_Idf_8_clicked()
{
    ui->TabP_3->setModel(ab.afficher2_1());

}

void Dialog::on_TriP_Ids_4_clicked()
{
    ui->TabP_3->setModel(ab.afficher3());

}

void Dialog::on_TriP_Ids_8_clicked()
{
    ui->TabP_3->setModel(ab.afficher3_1());

}

void Dialog::on_SaveP_4_clicked()
{
    QPrinter *imprimante;
       QPrintDialog pd(ui->TabP_3);
       if(pd.exec()== QDialog::Accepted) return;
       imprimante=pd.printer();
       imprimante->setOutputFormat(QPrinter::PdfFormat);
       imprimante->setOutputFileName("C:/Users/ME/Desktop/pdf/doc.pdf");
}

void Dialog::on_SaveP_5_clicked()
{
    QPrinter *imprimante;
       QPrintDialog pd(ui->TabP_4);
       if(pd.exec()== QDialog::Accepted) return;
       imprimante=pd.printer();
       imprimante->setOutputFormat(QPrinter::PdfFormat);
       imprimante->setOutputFileName("C:/Users/ME/Desktop/pdf/doc.pdf");
}

void Dialog::on_SaveP_3_clicked()
{
    QPrinter *imprimante;
       QPrintDialog pd(ui->TabP_2);
       if(pd.exec()== QDialog::Accepted) return;
       imprimante=pd.printer();
       imprimante->setOutputFormat(QPrinter::PdfFormat);
       imprimante->setOutputFileName("C:/Users/ME/Desktop/pdf/doc.pdf");

}

void Dialog::on_SaveP_2_clicked()
{
    QPrinter *imprimante;
       QPrintDialog pd(ui->TabC);
       if(pd.exec()== QDialog::Accepted) return;
       imprimante=pd.printer();
       imprimante->setOutputFormat(QPrinter::PdfFormat);
       imprimante->setOutputFileName("C:/Users/ME/Desktop/pdf/doc.pdf");
}


void Dialog::on_TriP_Idp_6_clicked()
{
    ui->TabP_5->setModel(ab.afficher1());

}

void Dialog::on_TriP_Idp_21_clicked()
{
    ui->TabP_5->setModel(ab.afficher1_1());

}

void Dialog::on_AddP_button_5_clicked()
{
    sound->play();
    int IdVehicule  = ui->IdVehicule->text().toInt();
    QString DateLivraison  = ui->DateLivraison->text();
    int IdEmploye  = ui->IdEmploye->text().toInt();
    int IdCommande  = ui->IdCom->text().toInt();
    vehicule h(IdVehicule, DateLivraison, IdEmploye, IdCommande);
    bool test = h.ajouter();
    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Ajout avec succes.");
        ResetProduit();
        ui->TabP_5->setModel(h.afficher1());
    }
    else
    {
        msgBox.setText("Echec d'ajout");
    }
    msgBox.exec();
}

void Dialog::on_RemoveP_button_6_clicked()
{

            int IdVehicule= ui->Idp_remove_6->text().toInt();
            QSqlQuery query;
            query.prepare("Select * from vehicule where IdVehicule = ?");
            query.addBindValue(IdVehicule);
            query.exec();
            if(query.next()) {
            bool test=h.supprimer(IdVehicule);
            if(test)
            {
                ui->TabP_5->setModel(h.afficher1());
                QMessageBox::information(nullptr, QObject::tr("DELETE"),
                            QObject::tr("DELETED SUCCESFULLY.\n"
                                        "Click Cancel to exit."), QMessageBox::Close);
                ui->Idp_remove_6->clear();

            }
            else
            QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                            QObject::tr("ERROR  !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             ui->Idp_remove_6->clear();}
            else
            { QMessageBox::critical(nullptr, QObject::tr("DELETE"),
                            QObject::tr("ID NOT FOUND !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
             ui->Idp_remove_6->clear();}

}

void Dialog::on_Psearch_5_textChanged(const QString &arg1)
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery   *query= new QSqlQuery();
    query->prepare("SELECT * FROM Vehicule WHERE IdVehicule  LIKE'"+arg1+"%' or DateLivraison  LIKE'"+arg1+"%' or IdEmploye  LIKE'"+arg1+"%' or IdCommande LIKE'"+arg1+"%' ");
     query->exec();
     if (query->next()) {
     model->setQuery(*query);
     ui->TabP_5->setModel(model);
     }
     else {
         QMessageBox::critical(nullptr, QObject::tr("SEARCH"),
                         QObject::tr("NO MATCH FOUND !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->Psearch_5->clear();}
}

void Dialog::on_TabP_5_activated(const QModelIndex &index)
{
    QString val=ui->TabP_5->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("Select * from vehicule where idvehicule='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->IdVehicule->setText(qry.value(0).toString());
            ui->DateLivraison->setText(qry.value(1).toString());
            ui->IdEmploye->setText(qry.value(2).toString());
            ui->IdCom->setText(qry.value(3).toString());



            ui->EditP_button_6->setEnabled(true);
           ui->IdVehicule->setDisabled(true);
}
    }
}

void Dialog::on_EditP_button_6_clicked()
{
    sound->play();
    int IdVehicule  = ui->IdVehicule->text().toInt();

    QString DateLivraison =ui->DateLivraison->text();
    int IdEmploye  = ui->IdEmploye->text().toInt();
    int IdCommande  = ui->IdCom->text().toInt();



    vehicule h(IdVehicule,DateLivraison,IdEmploye,IdCommande);
    bool test = h.modifier(IdVehicule);
    QMessageBox msgBox;
    if(test)
    {
            msgBox.setText("MODIFED SUCCESFULLY.");

            ui->TabP_5->setModel(h.afficher1());
            ui->EditP_button_6->setEnabled(false);

        }
        else
        {
            msgBox.setText("ERROR CAN'T MODIFY ! ");
        }
        msgBox.exec();
        msgBox.setText("MODIFED SUCCESFULLY.");
        ui->TabP_5->setModel(h.afficher1());
        ui->EditP_button_5->setEnabled(false);
        ui->IdVehicule->clear();
        ui->DateLivraison->clear();
        ui->IdEmploye->clear();
        ui->IdCom->clear();

       ui->IdVehicule->setDisabled(false);
       ui->IdVehicule->clear();
}


void Dialog::on_TriP_Ids_6_clicked()
{
        ui->TabP_5->setModel(h.afficher3());
        sound->play();
}

void Dialog::on_TriP_Idf_6_clicked()
{
        ui->TabP_5->setModel(h.afficher2());
        sound->play();
}

void Dialog::on_TriP_Idp_3_clicked()
{
    ui->TabP_2->setModel(CM.affichertri1());
    sound->play();
}

void Dialog::on_TriP_Idf_3_clicked()
{
    ui->TabP_2->setModel(CM.affichertri2());
    sound->play();
}

void Dialog::on_TriP_Ids_3_clicked()
{
    ui->TabP_2->setModel(CM.affichertri3());
    sound->play();
}

void Dialog::on_TriP_Idf_2_clicked()
{
    ui->TabC->setModel(C.afficher2());
    sound->play();
}

void Dialog::on_TriP_Idp_2_clicked()
{
        ui->TabC->setModel(C.afficher1());
        sound->play();
}

void Dialog::on_TriP_Ids_2_clicked()
{
        ui->TabC->setModel(C.afficher3());
        sound->play();
}

void Dialog::on_SaveP_6_clicked()
{
    QPrinter *imprimante;
       QPrintDialog pd(ui->TabP_5);
       if(pd.exec()== QDialog::Accepted) return;
       imprimante=pd.printer();
       imprimante->setOutputFormat(QPrinter::PdfFormat);
       imprimante->setOutputFileName("C:/Users/ME/Desktop/pdf/doc.pdf");
}

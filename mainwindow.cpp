#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reclamation.h"
#include "fournisseur.h"
#include "dialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include "profil.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::on_pushButton_connecter_clicked()
{
    QSqlQuery query;
        profil P1;
          bool login;

          QString user= ui->lineEdit_username->text();
           QString   pass=ui->lineEdit_password->text();

        login=P1.login(user,pass);
             if (login==true){
               dialog = new Dialog(this);

               dialog->setWindowTitle("Gestion employe et profil" );
                     dialog->show();
        }
             else
                 ui->label_3->setText("mot de passe incorrecte");
}

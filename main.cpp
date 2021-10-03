#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "connexion.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;
    QFile styleSheetFile(":/styleSheet/Integrid.qss");
        styleSheetFile.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(styleSheetFile.readAll());
        a.setStyleSheet(styleSheet);
    bool test=c.ouvrirConnexion();
    MainWindow w;
    Dialog d;
         if(test)
         {

             w.show();
         }
         else

             QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                         QObject::tr("connection failed.\n""Click Cancel to exit."), QMessageBox::Cancel);

    return a.exec();
}

#include "MainWindow_Equipements.h"
#include <QApplication>
#include <QMessageBox>
#include "Connection.h"
#include <QUrl>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QPainter>
//#include "QZXing.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 a.setStyle("fusion ");
    Connection c;
    bool test=c.createconnect();
      MainWindow_Equipements w;
      if(test)
    {w.show();
        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}
void MainWindow_Equipements::on_pushButtonPDF_clicked()
{

    QPdfWriter pdf("C:/pdf/list.pdf");

   QPainter painter(&pdf);
   int i = 4100;
   const QImage image("C:/Logo.jpg");
               const QPoint imageCoordinates(155,0);
               int width1 = 1600;
               int height1 = 600;
               QImage img=image.scaled(width1,height1);
               painter.drawImage(imageCoordinates, img );


          QColor dateColor(0x4a5bcf);
          painter.setPen(dateColor);

          painter.setFont(QFont("Montserrat SemiBold", 11));
          QDate cd = QDate::currentDate();
          painter.drawText(7700,250,cd.toString("Ariana, El Ghazela"));
          painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

          QColor titleColor(0x341763);
          painter.setPen(titleColor);
          painter.setFont(QFont("Montserrat SemiBold", 25));

          painter.drawText(3000,2700,"Liste des Equipements");

          painter.setPen(Qt::black);
          painter.setFont(QFont("Time New Roman", 15));
          //painter.drawRect(100,100,9400,2500);
          painter.drawRect(100,3300,9400,500);

          painter.setFont(QFont("Montserrat SemiBold", 10));

          painter.drawText(300,3600,"ID");
          painter.drawText(1000,3600,"Nom   ");
          painter.drawText(2300,3600,"Type      ");
          painter.drawText(3300,3600," Prix   ");
          painter.drawText(4300,3600,"Quantite");
          painter.setFont(QFont("Montserrat", 10));
          painter.drawRect(100,3300,9400,9000);

          QSqlQuery query;
          query.prepare("select * from Equipements");
          query.exec();
          int y=4300;
          while (query.next())
          {
              painter.drawLine(100,y,9490,y);
              y+=500;
              painter.drawText(300,i,query.value(0).toString());
              painter.drawText(1000,i,query.value(1).toString());
              painter.drawText(2300,i,query.value(2).toString());
              painter.drawText(3300,i,query.value(3).toString());
              painter.drawText(4300,i,query.value(4).toString());
              painter.drawText(5300,i,query.value(5).toString());
            //  painter.drawText(6300,i,query.value(6).toString());
              //painter.drawText(7300,i,query.value(7).toString());

             i = i + 500;
          }

          int reponse = QMessageBox::question(this, "Génerer PDF", "PDF Enregistré.\nVous voulez l'affichez ?", QMessageBox::Yes |  QMessageBox::No);
          if (reponse == QMessageBox::Yes)
          {
              QDesktopServices::openUrl( QUrl ::fromLocalFile("C:/pdf/list.pdf"));
              painter.end();
          }
          else
          {
              painter.end();
          }


}



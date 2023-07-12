#include "Equipements.h"
#include <QSqlQuery>
#include <QtDebug>
#include <cctype>
#include <QSystemTrayIcon>
#include <QIcon>
//#include <QZXing>
Equipements::Equipements(QString ID_Equipements, QString Nom, QString Type, double Prix, int Quantite)
{
    this-> ID_Equipements= ID_Equipements;
    this->Nom = Nom;
    this->Type = Type;
    this->Prix = Prix ;
    this->Quantite = Quantite;

}

bool Equipements::ajouter()
{
    QSqlQuery query;
       query.prepare("INSERT INTO EQUIPEMENTS (ID_EQUIPEMENTS,NOM ,TYPE ,PRIX, QUANTITE) "
                     "VALUES (:ID_Equipements, :Nom, :Type, :Prix, :Quantite)");
       query.bindValue(":ID_Equipements", ID_Equipements);
       query.bindValue(":Nom", Nom);
       query.bindValue(":Type", Type);
       query.bindValue(":Prix", Prix);
       query.bindValue(":Quantite", Quantite);
    //    query.exec();
       if(query.exec()){
           return true;
      } else {
           return false;
}
}
QSqlQueryModel * Equipements::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
 model->setQuery("SELECT * FROM EQUIPEMENTS");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Equipements"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantite"));

    return model;
}


bool Equipements::supprimer(QString ID_Equipements)
{
QSqlQuery query;
query.prepare("Delete from EQUIPEMENTS where ID_EQUIPEMENTS= :id");
query.bindValue(":id",ID_Equipements);
query.exec();
return query.exec();
}

bool Equipements :: modifier(QString recherche)
{
    QSqlQuery query;
        query.prepare("UPDATE EQUIPEMENTS SET ID_EQUIPEMENTS = :id_equipements, NOM = :nom, TYPE = :type, PRIX = :prix, QUANTITE = :quantite WHERE ID_EQUIPEMENTS LIKE '"+recherche+"%'");
        query.bindValue(":id_equipements", ID_Equipements);
        query.bindValue(":nom", Nom);
        query.bindValue(":type", Type);
        query.bindValue(":prix", Prix);
        query.bindValue(":quantite", Quantite);
        query.exec();
       return  query.exec();
}
QSqlQueryModel* Equipements::chercher (QString champ, QString recherche)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString query = "SELECT * FROM EQUIPEMENTS WHERE " + champ + " LIKE '" + recherche + "%'";
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Equipements"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantite"));
    return model;
}

QSqlQueryModel* Equipements::trierNom()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM Equipements ORDER BY Nom ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Equipements"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantite"));

    return model;
}


QSqlQueryModel* Equipements::trierType()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM Equipements ORDER BY Type ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Equipements"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Quantite"));

    return model;
}





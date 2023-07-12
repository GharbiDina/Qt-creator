#pragma once
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
using namespace std;
class Equipements
{
private:
    QString ID_Equipements;
    QString Nom;
    QString Type;
    double Prix;
    int Quantite;

public:
    Equipements(){};
    Equipements(QString ID_Equipements,QString Nom,QString Type,double Prix, int Quantite);

    QString getIDEquipements() {return ID_Equipements;};
    QString getNom() const;
    QString getType() const;
    float getPrix() const;
    int getQuantite() const;
//    void setID(int id){this->id=id;}

    void setIDEquipements(QString ID_Equipements){this->ID_Equipements=ID_Equipements;};
    void setNom(const QString & Nom);
    void setType(const QString & Type);
    void setPrix(float Prix);
    void setQuantite(int Quantite);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool modifier(QString ID_Equipements);
 QSqlQueryModel*chercher(QString champ, QString cherche);
QSqlQueryModel*trierNom();
QSqlQueryModel* trierType();

};


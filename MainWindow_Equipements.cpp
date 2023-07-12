#include "MainWindow_Equipements.h"
#include "ui_Equipements.h"
#include "Equipements.h"
#include "QtDebug"
#include "QrCode.h"
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
using qrcodegen::QrCode;

MainWindow_Equipements::MainWindow_Equipements(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_Equipements)
{
    ui->setupUi(this);
    ui->tab_etudiant->setModel(Etmp.afficher());
connect(ui->qr_code, &QPushButton::clicked, this, &MainWindow_Equipements::on_qr_code_clicked);
//ui->setupUi(this);
mSystemTrayIcon =new QSystemTrayIcon(this);
mSystemTrayIcon->setIcon(QIcon(":/myappico.png"));
mSystemTrayIcon->setVisible(true);

}

MainWindow_Equipements::~MainWindow_Equipements()
{
    delete ui;
}
void MainWindow_Equipements::on_pushButton_ajouter_clicked()
{
        QString ID_Equipements = ui->le_id->text();
        QString Nom = ui->le_nam->text();
        QString Type = ui->le_Type->text();
        double Prix = ui->le_prix->text().toDouble();
        int Quantite = ui->le_quantite->text().toInt();
        // Vérification du champ ID
        if (ID_Equipements.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Veuillez entrer un identifiant pour l'équipement!!");
            return;
        }
        QRegExp regex("^[0-9]+$");
            if (!regex.exactMatch(ID_Equipements)) {
                QMessageBox::warning(this, "Erreur", "L'ID ne doit contenir que des chiffres.");
                return;
            }

            // Vérifier que l'ID est unique dans la base de données
            Equipements equipement;
            if (equipement.chercher("ID_EQUIPEMENTS",ID_Equipements)->rowCount() != 0) {
                QMessageBox::warning(this, "Erreur", "L'ID existe déjà dans la base de données.");
                return;
            }
            // Vérifier que nom est unique dans la base de données
            Equipements equi;
            if (equi.chercher("NOM",Nom)->rowCount() != 0) {
                QMessageBox::warning(this, "Erreur", "le nom existe déjà dans la base de données.");
                return;
            }
        // Vérification du champ Nom
        if (Nom.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Veuillez entrer un nom pour l'équipement.");
            return;
        }
        QRegularExpression regexNom("^[A-Za-z0-9 ]+$"); // Expression régulière pour valider le nom
        QRegularExpressionMatch matchNom = regexNom.match(Nom);

        if (!matchNom.hasMatch()) {
            QMessageBox::critical(this, "Erreur", "Nom invalide : Nom ne doit contenir que des lettres, des chiffres et des espaces!");
            return;
        }

        // Vérification du champ Type
     /*   if (Type.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Veuillez entrer un type pour l'équipemen.");
            return;
        }
        if (Type.contains(QRegExp("^[a-zA-Z\\s]*$")) == false) {
                QMessageBox::warning(this, "Erreur", "Le type ne doit contenir que des lettres et des espaces.");
                return;
            }*/
       // QString Type = ui->le_Type->text();
        if (Type.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Veuillez entrer un type pour l'équipement.");
            return;
        }
        if (!Type.contains(QRegExp("^[a-zA-Z\\s]*$"))) {
            QMessageBox::warning(this, "Erreur", "Le type ne doit contenir que des lettres et des espaces.");
            return;
        }
        if ( Type != "logiciel" && Type != "materiel" && Type != "ordinateur") {
            QMessageBox::warning(this, "Erreur", "Le type doit être  'logiciel', 'materiel' ou 'ordinateur'.");
            return;
        }


        // Vérification du champ Prix
        QRegExp prixRegex("[1-9][0-9]*(\\.[0-9]{1,2})?$");  // Le prix doit être un nombre positif avec au plus 2 chiffres après la virgule
            if (!prixRegex.exactMatch(ui->le_prix->text())) {
                QMessageBox::critical(this, "Erreur", " Le prix doit être un nombre positif avec au plus 2 chiffres après la virgule!");
                return;
            }
            if (Prix <= 0) {
                QMessageBox::critical(this, "Erreur", "le prix doit etre >0");
                return;
            }

        // Vérification du champ Quantite
             QString Quantite_str = ui->le_quantite->text();
            if (Quantite_str.isEmpty()) {
                QMessageBox::critical(this, "Erreur", "Veuillez entrer une quantite pour l'équipement.");
                return;
            }







        // Create a new instance of Equipements with the user inputs
        Equipements newEquipement(ID_Equipements, Nom, Type, Prix, Quantite);

        // Call the addEquipement() function to add the new Equipement to the database
        if (newEquipement.ajouter()) {
            QMessageBox::information(this, "Success", " ajouté avec succès.");
            ui->tab_etudiant->setModel(Etmp.afficher());

        } else {
            QMessageBox::critical(this, "Error", "Failed to add Equipement.");
        }

        // Clear the input fields
        ui->le_id->clear();
        ui->le_nam->clear();
        ui->le_Type->clear();
        ui->le_prix->clear();
        ui->le_quantite->clear();      
}


void MainWindow_Equipements::on_pushButton_supprimer_clicked()
{
    Equipements E1;

 E1.setIDEquipements(ui->le_IDS->text());
bool test=Etmp.supprimer(E1.getIDEquipements());

if(test)
{

    //Refresh (actualiser)
    ui->tab_etudiant->setModel(Etmp.afficher());

QMessageBox::information(nullptr, QObject::tr("OK"),
QObject::tr("Suppression effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);
ui->le_IDS->clear();

}
else
QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
QObject::tr("Suppression non effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow_Equipements::on_pb_modifier_clicked() {
    QString ID_Equipements = ui->le_id->text();
    QString Nom = ui->le_nam->text();
    QString Type = ui->le_Type->text();
    double Prix = ui->le_prix->text().toDouble();
    int Quantite = ui->le_quantite->text().toInt();
    QString cherche = ui->le_find->text();

    // Vérification du champ ID
   if (ID_Equipements.isEmpty()) {
        QMessageBox::critical(this, "Error", "Veuillez entrer un identifiant pour l'équipement.");
        return;
    }
    QRegExp regex("^[0-9]+$");
        if (!regex.exactMatch(ID_Equipements)) {
            QMessageBox::warning(this, "Erreur", "L'ID ne doit contenir que des chiffres.");
            return;

        }
    // Vérification du champ Nom
    if (Nom.isEmpty()) {
        QMessageBox::critical(this, "Error", "Veuillez entrer un nom pour l'équipement");
        return;
    }
    QRegularExpression regexNom("^[A-Za-z0-9 ]+$"); // Expression régulière pour valider le nom
    QRegularExpressionMatch matchNom = regexNom.match(Nom);

    if (!matchNom.hasMatch()) {
        QMessageBox::critical(this, "Error", "Invalid Nom: Nom must contain only letters, digits and spaces.");
        return;
    }

    // Vérification du champ Type
    if (Type.isEmpty()) {
        QMessageBox::critical(this, "Error", "Veuillez saisir un type d'équipement.");
        return;
    }
    if (Type.contains(QRegExp("^[a-zA-Z\\s]*$")) == false) {
            QMessageBox::warning(this, "Erreur", "Le type ne doit contenir que des lettres et des espaces.");
            return;
        }

    // Vérification du champ Prix
    QRegExp prixRegex("[1-9][0-9]*(\\.[0-9]{1,2})?$");  // Le prix doit être un nombre positif avec au plus 2 chiffres après la virgule
        if (!prixRegex.exactMatch(ui->le_prix->text())) {
            QMessageBox::critical(this, "Error", "Invalid price. The price should be a positive number with at most 2 decimal places.");
            return;
        }
        if (Prix <= 0) {
            QMessageBox::critical(this, "Error", "Invalid price. The price should be greater than 0.");
            return;
        }

    // Vérification du champ Quantite
        QString Quantite_str = ui->le_quantite->text();
        if (Quantite_str.isEmpty() || Quantite_str.toInt() <= 0) {
            QMessageBox::critical(this, "Error", "Please enter a positive quantity.");
            return;
        }

    Equipements newEquipement(ID_Equipements, Nom, Type, Prix, Quantite);

        if (newEquipement.chercher(ID_Equipements , ID_Equipements)->rowCount() != 0 and cherche.length() != 0) {
            bool test = newEquipement.modifier(cherche);

            if (test) {
                QMessageBox::information(nullptr, QObject::tr("Base de données ouverte"), QObject::tr("Modification effectuée.\nCliquez sur Annuler pour quitter."));
                ui->tab_etudiant->setModel(newEquipement.afficher());
            } else {
                QMessageBox::critical(nullptr, QObject::tr("Base de données non ouverte"), QObject::tr("Modification non effectuée.\nCliquez sur Annuler pour quitter."));
            }
        } else {
            QMessageBox::critical(nullptr, QObject::tr("ERREUR"), QObject::tr("Modification non effectuée !\nCliquer sur Annuler pour quitter."));
        }

        ui->tab_etudiant->setModel(newEquipement.afficher());

        // Efface les champs d'entrée
        ui->le_id->clear();
        ui->le_nam->clear();
        ui->le_Type->clear();
        ui->le_prix->clear();
        ui->le_quantite->clear();
    }
void MainWindow_Equipements::on_rechercher_clicked()
{  Equipements E;
    QString Type= ui->lineEdit_rechercher->text();
        QSqlQueryModel * model = E.chercher("TYPE",Type);
        ui->tab_etudiant->setModel(model);
}
void MainWindow_Equipements::on_pushButton_stat_clicked()
{

    for (QObject *child : ui->tableView->children()) {
            if (child->inherits("QtCharts::QChartView")) {
                child->deleteLater();
            }
        }


    // Récupération des données de la table "EQUIPEMENTS" de la base de données
    QSqlQuery query;
    query.exec("SELECT TYPE, COUNT(*) FROM EQUIPEMENTS GROUP BY TYPE ");

    // Création des barres pour chaque type d'équipement
    QtCharts::QBarSet *set = new QtCharts::QBarSet("Nombre d'équipements");
    while (query.next()) {
        QString Type = query.value(0).toString();
        int count = query.value(1).toInt();
        *set << count;
        set->setLabel(Type);

    }

    // Ajout des barres au graphique
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();
    series->append(set);

    // Création de l'axe des catégories
    QtCharts::QCategoryAxis *axis = new QtCharts::QCategoryAxis();
    axis->append(set->label(), 0);

    // Création de l'axe des valeurs (nombre d'équipements)
    QtCharts::QValueAxis *valueAxis = new QtCharts::QValueAxis();
    valueAxis->setRange(0, set->at(set->count() - 1));
    valueAxis->setLabelFormat("%d");


    // Création du graphique et ajout des axes et des barres
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques sur les types d'équipements");
    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->setAxisY(valueAxis);

    // Affichage du graphique dans l'élément "tableView" de votre interface utilisateur
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->tableView);
    chartView->resize(ui->tableView->size());
    chartView->show();
}
void MainWindow_Equipements::on_pb_trier_clicked()
{
    Equipements E;
    if(ui->comboBoxTrie->currentIndex()==0){
        ui->tab_etudiant->setModel(E.trierNom());
    }
    else if(ui->comboBoxTrie->currentIndex()==1){
        ui->tab_etudiant->setModel(E.trierType());
    }
}

void MainWindow_Equipements::on_qr_code_clicked()
{
    QMessageBox msg;
                  QItemSelectionModel * select = ui->tab_etudiant->selectionModel();
                  if (!select->hasSelection()){
                       msg.setText("Please select something");

                       msg.setIcon(msg.Critical);
                       msg.exec();
                       return;
                  }
            int tabeq=ui->tab_etudiant->currentIndex().row();//selectionner dons le tab  ligne
                   QVariant ID=ui->tab_etudiant->model()->data(ui->tab_etudiant->model()->index(tabeq,0));//selectionne le id exactement
                   QString idd= ID.toString();//convertir a une chaine
                   QSqlQuery qry;//navigating and retrieving data from SQL queries which are executed on a QSqlDatabase.

                   qry.prepare("select * from EQUIPEMENTS where ID_EQUIPEMENTS=:idd");//Prepares the SQL query  for execution. Returns true or false
                   qry.bindValue(":idd",idd);//prendre valeur id et mettre dans table
                   qry.exec();//Executes a previously prepared SQL query
                      QString  id,Type,Nom,Quantite,Prix,idc;

                   while(qry.next()){

                       Nom=qry.value(1).toString();
                       Type=qry.value(2).toString();
                       Prix=qry.value(3).toString();
                       Quantite=qry.value(4).toString();


                   }
                   idc=QString(idd);
                          idc="ID_EQUIPEMENTS:"+idd+"Nom:"+Nom+"Type:"+Type+"QUANTITE:"+Quantite+"PRIX:"+Prix;//pendre la chaine a code
                   QrCode qr = QrCode::encodeText(idc.toUtf8().constData(), QrCode::Ecc::HIGH);

                   // Read the black & white pixels
                QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
                   for (int y = 0; y < qr.getSize(); y++) {
                       for (int x = 0; x < qr.getSize(); x++) {
                           int color = qr.getModule(x, y);  // 0 for white, 1 for black*/


                           if(color==0)
                               im.setPixel(x, y,qRgb(254, 254, 254));
                           else
                               im.setPixel(x, y,qRgb(0, 0, 0));
                       }
                   }
                   im=im.scaled(200,200);
                   ui->label_2->setPixmap(QPixmap::fromImage(im));
}

void MainWindow_Equipements::on_showMessagePushButton_clicked()
{
    Equipements equi;
    QSqlQueryModel* model = equi.chercher("Quantite", "0");
    if (model->rowCount() > 0) {
        QString message = tr("Les équipements suivants ont une quantité égale à 0 :\n");
        for (int i = 0; i < model->rowCount(); ++i) {
            QString idEquip = model->data(model->index(i, 0)).toString();
            QString nom = model->data(model->index(i, 1)).toString();
            QString type = model->data(model->index(i, 2)).toString();
            QString prix = model->data(model->index(i, 3)).toString();
            message += idEquip + " - " + nom + " (" + type + ") - Prix : " + prix + "\n";
        }
        mSystemTrayIcon->showMessage(tr("Quantité épuisée"), message);
    }



   else { mSystemTrayIcon ->showMessage(tr("Pas de Quantité épuisée"),
                                        tr("vous n'avez pas de Quantité épuisée "));}

}

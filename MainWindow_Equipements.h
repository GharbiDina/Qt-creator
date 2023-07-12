#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Equipements.h"
namespace Ui {
class MainWindow_Equipements;
}
class QSystemTrayIcon;
QT_END_NAMESPACE
class MainWindow_Equipements : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_Equipements(QWidget *parent = nullptr);
    ~MainWindow_Equipements();

private slots:
     void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pb_modifier_clicked();
void on_pushButtonPDF_clicked();
void on_pushButtonQR_clicked();
void on_rechercher_clicked();
void on_pushButton_stat_clicked();
void on_pb_trier_clicked();
void on_qr_code_clicked();



void on_showMessagePushButton_clicked();

private:
    Ui::MainWindow_Equipements *ui;
    Equipements Etmp;
 QSystemTrayIcon *mSystemTrayIcon;
};

#endif // MAINWINDOW_H

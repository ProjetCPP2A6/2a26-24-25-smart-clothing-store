#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"acceuil.h"
#include<QString>
#include<QMessageBox>
#include <QtCharts>
#include <QChartView>


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

void MainWindow::on_connexion_clicked()
{
//     QString user = ui->nom->text();
//     QString pass = ui->mdp->text();
//     QSqlQuery query;
//     query.prepare("SELECT * FROM employes WHERE  EMAIL  = :EMAIL AND ADRESSE = :ADRESSE");
//     query.bindValue(":EMAIL", user);
//     query.bindValue(":ADRESSE", pass);
//     query.exec();
//     if (query.next()) {


//         QSqlQuery updateQuery;
//         updateQuery.prepare("UPDATE employes SET presence = :presence WHERE username = :username");
//         updateQuery.bindValue(":presence", "in");
//         updateQuery.bindValue(":username", user);
//         updateQuery.exec();
// acc = new acceuil();  // Use no parent to keep `acceuil` independent of `MainWindow`
// acc->show();


// }
QString NOM = ui->nom->text();
QString MDP = ui->mdp->text();

if (NOM == "test" && MDP == "test")
{
    QMessageBox::information(this, "LOGIN", "Connexion établie");

    // Show the acceuil window without hiding MainWindow
    acc = new acceuil();  // Use no parent to keep `acceuil` independent of `MainWindow`
    acc->show();
}
else
{
    QMessageBox::warning(this, "Login", "Nom d'utilisateur ou mot de passe incorrect");
}

}





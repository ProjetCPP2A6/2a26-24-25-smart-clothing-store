#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"acceuil.h"
#include<Qstring>
#include<QMessageBox>
#include <QSqlError>
#include "ui_acceuil.h"
#include "arduino.h"
Arduino A;  // Déclarer l'objet Arduino

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    A.close_arduino();  // Assurez-vous de fermer le port série ici
    delete ui;
}
void MainWindow::configurerInterface(acceuil* acc, const QString& statut)
{
    // Masquer ou afficher les sections en fonction du statut
    if (statut == "RH") {
        // RH : Tous les widgets visibles
        acc->show();
    }
    else if (statut == "Livreur")
    {
        // Livreur : Seule la livraison visible
        acc->ui->tabWidget_2->show();
        acc->ui->tabWidget_4->hide();
        acc->ui->tabWidget_7->hide();
        acc->ui->tabWidget_8->hide();
        acc->ui->ajouter_e->hide();
        acc->ui->supprimer_e_2->hide();
        acc->ui->pushButton_56->hide();
        acc->ui->rechercher_e->hide();
        acc->ui->trier_e->hide();
    }
    else if (statut == "Vendeur")
    {
        // Vendeur : Bonus et livraison masqués
        acc->ui->tabWidget_2->hide();
        acc->ui->tabWidget_4->show();
        acc->ui->tabWidget_7->show();
        acc->ui->tabWidget_8->show();
        acc->ui->tabWidget_6->show();
    }
}

void MainWindow::on_connexion_clicked()
{

    QString IDENTIFIANT = ui->id->text();
    QString MDP = ui->mdp->text();

    // Vérification des identifiants dans la base de données
    if (MDP != "test") {  // Vérification du mot de passe fixe pour tous les employés
        QMessageBox::warning(this, "Login", "Mot de passe incorrect");
        return;
    }

    // Si le mot de passe est correct, vérifier si l'identifiant existe dans la base de données
    QSqlQuery query;
    query.prepare("SELECT statut FROM EMPLOYES WHERE IDE = :IDENTIFIANT");
    query.bindValue(":IDENTIFIANT", IDENTIFIANT);  // Bind pour l'identifiant

    if (query.exec() && query.next())
    {
        QString statut = query.value(0).toString(); // Récupère le statut

        QMessageBox::information(this, "LOGIN", "Connexion établie");
        hide();

        // Passer le statut à l'accueil
        acc = new acceuil();
        configurerInterface(acc, statut); // Configurer l'interface en fonction du statut
        acc->show();
    } else {
        QMessageBox::warning(this, "Login", "Identifiant incorrect");
    }
    A.close_arduino();

}


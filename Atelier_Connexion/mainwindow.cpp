#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"acceuil.h"
#include<QString>
#include<QMessageBox>


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
    QString NOM=ui->nom->text();
    QString MDP=ui->mdp->text();

    if (NOM=="test" && MDP=="test")
    {
        QMessageBox::information(this,"LOGIN","connexion établie");
        hide();

        acc=new acceuil();
        acc->show();
    }
    else {
        QMessageBox::warning(this,"Login","nom d'utilisateur ou mot de passe incorect");
    }

}



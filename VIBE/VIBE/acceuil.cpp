#include "acceuil.h"
#include "ui_acceuil.h"

acceuil::acceuil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acceuil)
{
    ui->setupUi(this);
}

acceuil::~acceuil()
{
    delete ui;
}

void acceuil::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void acceuil::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void acceuil::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void acceuil::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void acceuil::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void acceuil::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}



#ifndef EMPLOYÉS_CPP
#define EMPLOYÉS_CPP
#include "Employés.h"
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

Employe::Employe()
{
    IDE = 0;
    IDS = 0;
    IDC = 0;
    NOM = "";
    PRENOM = "";
    ADRESSE="";
    DATEN="";
    EMAIL="";
    NUMTEL=0;
    DATEEMBAUCHE="";
    DATEFIN="";
    STATUT="";
    NUMCB=0;
}

Employe::Employe(int IDE , QString NOM, QString PRENOM, QString ADRESSE, QString DATEN, QString EMAIL, int NUMTEL, QString DATEEMBAUCHE, QString DATEFIN, QString STATUT, int NUMCB, int IDS, int IDC)
{
    this->IDE = IDE;
    this->NOM = NOM;
    this->PRENOM = PRENOM;
    this->ADRESSE = ADRESSE;
    this->DATEN=DATEN;
    this->EMAIL=EMAIL;
    this->NUMTEL=NUMTEL;
    this->DATEEMBAUCHE=DATEEMBAUCHE;
    this->DATEFIN=DATEFIN;
    this->STATUT=STATUT;
    this->NUMCB=NUMCB;
    this->IDS = IDS;
    this->IDC = IDC;
}
int Employe::getIde()
{
    return IDE;
}
QString Employe::getNom()
{
    return NOM;
}
QString Employe::getPrenom()
{
    return PRENOM;
}
QString Employe::getStatut()
{
    return STATUT;
}
QString Employe::getAdresse()
{
    return ADRESSE;
}
QString Employe::getDateDeNaissance()
{
    return DATEN;
}
QString Employe::getEmail()
{
    return EMAIL;
}
QString Employe::getDateEmbauche()
{
    return DATEEMBAUCHE;
}
QString Employe::getDateFinContrat()
{
    return DATEFIN;
}
int Employe::getNumTel()
{
    return NUMTEL;
}
int Employe::getNumCB()
{
    return NUMCB;
}
int Employe::getIds()
{
    return IDS;
}
int Employe::getIdc()
{
    return IDC;
}
void Employe::setIde(int)
{
    this->IDE=IDE;
}
void Employe::setNom(QString)
{
    this->NOM=NOM;
}
void Employe::setPrenom(QString)
{
    this->PRENOM=PRENOM;
}
void Employe::setStatut(QString)
{
    this->STATUT=STATUT;
}
void Employe::setAdresse(QString)
{
    this->ADRESSE=ADRESSE;
}
void Employe::setDateDeNaissance(QString)
{
    this->DATEN=DATEN;
}
void Employe::setEmail(QString)
{
    this->EMAIL=EMAIL;
}
void Employe::setDateEmbauche(QString)
{
    this->DATEEMBAUCHE=DATEEMBAUCHE;
}
void Employe::setDateFinContrat(QString)
{
    this->DATEFIN=DATEFIN;
}
void Employe::setNumTel(int)
{
    this->NUMTEL=NUMTEL;
}
void Employe::setNumCB(int)
{
    this->NUMCB=NUMCB;
}
void Employe::setIds(int)
{
    this->IDS=IDS;
}
void Employe::setIdc(int)
{
    this->IDC=IDC;
}

bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employe (IDE ,NOM, PRENOM,ADRESSE, DATEN,EMAIL,NUMTEL,DATEEMBAUCHE,DATEFIN,STATUT,NUMCB,IDS,IDC) VALUES (:IDE , :NOM, :PRENOM, :ADRESSE, :DATEN, :EMAIL, :NUMTEL, :DATEEMBAUCHE, :DATEFIN, :STATUT, :NUMCB, :IDS, :IDC)");
    query.bindValue(":IDE", IDE);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":DATEN", DATEN);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMTEL", NUMTEL);
    query.bindValue(":DATEEMBAUCHE", DATEEMBAUCHE);
    query.bindValue(":DATEFIN", DATEFIN);
    query.bindValue(":SATUT", STATUT);
    query.bindValue(":NUMCB", NUMCB);
    query.bindValue(":IDS", IDS);
    query.bindValue(":IDC", IDC);
    return query.exec();
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Employe");
    return model;
}

bool Employe::supprimer(int IDE)
{
    QSqlQuery query;
    query.prepare("DELETE FROM employe WHERE IDE = :IDE");
    query.bindValue(":IDE", IDE);
    return query.exec();
}

bool Employe::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE Employe SET NOM=:NOM, PRENOM=:PRENOM, ADRESSE=:ADRESSE,DATEN=:DATEN, EMAIL=:EMAIL, NUMTEL=:NUMTEL, DATEEMBAUCHE=:DATEEMBAUCHE, DATEFIN=:DATE, STATUT=:STATUT, NUMCB=:NUMCB , IDS=:IDS , IDC=:IDC WHERE IDE=:IDE");
    query.bindValue(":IDE", this->IDE);
    query.bindValue(":NOM", this->NOM);
    query.bindValue(":PRENOM", this->PRENOM);
    query.bindValue(":ADRESSE", this->ADRESSE);
    query.bindValue(":DATEN", this->DATEN);
    query.bindValue(":EMAIL", this->EMAIL);
    query.bindValue(":NUMTEL", this->NUMTEL);
    query.bindValue(":DATEEMBAUCHE", this->DATEEMBAUCHE);
    query.bindValue(":DATEFIN", this->DATEFIN);
    query.bindValue(":STATUT", this->STATUT);
    query.bindValue(":NUMCB", this->NUMCB);
    query.bindValue(":IDS", this->IDS);
    query.bindValue(":IDC", this->IDC);
    return query.exec();
}
#endif // EMPLOYÉS_CPP

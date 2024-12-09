#ifndef LIVRAISONS_H
#define LIVRAISONS_H

#include "qdatetime.h"
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class livraisons
{
private:
    long REFL , IDE , IDC , REFPROD ;
    QString TAILLEPROD , METHODEP , ETAT , COULEURPROD ;
    QDate DATECOMMANDE , DATEARRIVEE;
    float MONTANTCOMMANDE ;
public:
    // Constructeur par défaut
    livraisons();
    livraisons(long REFL , long IDE , long IDC , long REFPROD, QString TAILLEPROD , QString METHODEP , QString ETAT , QString COULEURPROD , QDate DATECOMMANDE , float MONTANTCOMMANDE);


    // Destructeur
    ~livraisons() {}

    // Getters
    long getREFL() const { return REFL; }
    long getIDE() const { return IDE; }
    long getIDC() const { return IDC; }
    long getREFPROD() const { return REFPROD; }
    QString getTAILLEPROD() const { return TAILLEPROD; }
    QString getMETHODEP() const { return METHODEP; }
    QString getETAT() const { return ETAT; }
    QString getCOULEURPROD() const { return COULEURPROD; }
    QDate getDATECOMMANDE() const { return DATECOMMANDE; }
    QDate getDATEARRIVEE() const { return DATEARRIVEE; }
    float getMONTANTCOMMANDE() const { return MONTANTCOMMANDE; }

    // Setters
    void setREFL(long value) { REFL = value; }
    void setIDE(long value) { IDE = value; }
    void setIDC(long value) { IDC = value; }
    void setREFPROD(long value) { REFPROD = value; }
    void setTAILLEPROD(QString value) { TAILLEPROD = value; }
    void setMETHODEP(QString value) { METHODEP = value; }
    void setETAT(QString value) { ETAT = value; }
    void setCOULEURPROD(QString value) { COULEURPROD = value; }
    void setDATECOMMANDE(QDate value) { DATECOMMANDE = value; }
    void setDATEARRIVEE(QDate value) { DATEARRIVEE = value; }
    void setMONTANTCOMMANDE(float value) { MONTANTCOMMANDE = value; }

    //méthode CRUD
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer (long);
    bool modifier (long);

    QSqlQueryModel* recherche_aff_refl (long REFL);
    QSqlQueryModel* recherche_aff_IDC (long IDC);
    QSqlQueryModel* recherche_aff_DATECOMMANDE (QDate DATECOMMANDE);
    QSqlQueryModel* trier();

    bool ajouterb ();
    QSqlQueryModel* afficherb();
    bool supprimerb (long);

    bool exporter();
};

#endif // LIVRAISONS_H

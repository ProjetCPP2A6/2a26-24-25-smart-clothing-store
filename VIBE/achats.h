#ifndef ACHATS_H
#define ACHATS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class ACHATS
{
    QString TAILLEPROD , METHODEP ,DATEACHAT;
    int REF, IDE ,IDC ,REFPROD;
    float MONTANTACHAT;
public:
    ACHATS(){}
    ACHATS(QString TAILLEPROD,QString METHODEP,QString DATEACHAT,int REF,int IDE,int IDC,int REFPROD,float MONTANTACHAT);


     QString getTAILLEPROD(){return TAILLEPROD;}
     QString getMETHODEP(){return METHODEP;}
     QString getDATEACHAT(){return DATEACHAT;}
     int getREF(){return REF;}
     int getIDE(){return IDE;}
     int getIDC(){return IDC;}
     int getREFPROD(){return REFPROD;}
     float getMONTANTACHAT(){return MONTANTACHAT;}

     void setTAILLEPROD(QString T){TAILLEPROD=T;}
     void setMETHODEP(QString M){METHODEP=M;}
     void setDATEACHAT(QString D){DATEACHAT=D;}
     void setREF(int REF){this->REF=REF;}
     void setIDE(int IDE){this->IDE=IDE;}
     void setIDC(int IDC){this->IDC=IDC;}
     void setREFPROD(int REFPROD){this->REFPROD=REFPROD;}
     void setMONTANTACHAT(float MONTANTACHAT){this->MONTANTACHAT=MONTANTACHAT;}

     bool ajouter();
     QSqlQueryModel * afficher();
     bool supprimer(int REF);
     QSqlQueryModel *rechercher(int REF);
     QSqlQueryModel * trier();
     bool exporter();
    /* QSqlQueryModel *rechercher2(int REF);
     void appliquerDémarque(QString typeDémarque, int selectedRefAchat);*/

};



#endif // ACHATS_H

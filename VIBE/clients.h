#ifndef CLIENTS_H
#define CLIENTS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Clients
{
    QString NOM,PRENOM,ADRESSE,EMAIL;
    int NUMTEL,POINTF;

    QString COULEUR,STYLE,SEXE;
    int AGE;

public:
    Clients();
    Clients(QString NOM, QString PRENOM, QString ADRESSE, QString EMAIL, int NUMTEL, int POINTF);
    //getters
    QString getNom() {return NOM;}
    QString getPrenom() {return PRENOM;}
    QString getAdresse() {return ADRESSE;}
    QString getEmail() {return EMAIL;}
    int getNumtel() {return NUMTEL;}
    int getPointf() {return POINTF;}

    QString getCouleur(){return COULEUR;}
    QString getStyle(){return STYLE;}
    QString getSexe(){return SEXE;}
    int getAge(){return AGE;}


    //setters
    void setNom(QString n) {NOM=n;}
    void setPrenom(QString p) {PRENOM=p;}
    void setAdresse(QString a) {ADRESSE=a;}
    void setEmail(QString e) {EMAIL=e;}
    void setNumtel(int num) {NUMTEL=num;}
    void setPointf(int point) {POINTF=point;}

    void setCouleur(QString cou) {COULEUR=cou;}
    void setStyle(QString sty) {STYLE=sty;}
    void setSexe(QString s) {SEXE=s;}
    void setAge(int age) {AGE=age;}

    //fonctionnalités
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int NUMTEL);
    bool modifier(int numtel);
    bool exporter();
    void calculerPointsFidelite();


};

#endif // CLIENTS_H

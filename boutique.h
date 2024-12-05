#ifndef BOUTIQUE_H
#define BOUTIQUE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QTableView>
#include <QVector>

class boutique
{

    int id;
    int num;
    QString nom,adr;
public:
    boutique();
    boutique(int);
    boutique(int,QString,QString,int);
    QString getnom(){return nom;}
    QString getadr(){return adr;}
    int getid(){return id ;}
    int getnum(){return num;}

    void setnom(QString nom){this->nom=nom;}
    void setadr(QString adr){this->adr=adr;}
    void setid(int id){this->id=id; }
    void setnum(int num){this->num=num;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel* rechercher(int id);
    bool enregistrer();
    bool chargerDepuisBD();
    QString getPhoneNumberByName(const QString& nom);
    QVector<boutique> recupererBoutique();
    QList<QString> recupererBoutiqueNom(QVector<boutique> boutiques);

};

#endif // BOUTIQUE_H

#ifndef PRODUIT_H
#define PRODUIT_H
#include <QString>
#include <ctime>
#include <QSqlQueryModel>

class PRODUIT
{
public:
    PRODUIT();
    PRODUIT(int,QString,QString,QString,int,QString);
    int getREFPROD();
    QString getTYPEP();
    QString getNOMP();
    QString getTAILLEPROD();
    int getQUANTITE();
    QString getCOULEUR();
    void setREFPROD(int REFPROD);
    void setTYPEP(QString TYPEP);
    void setNOMP(QString NOMP);
    void setTAILLEPROD(QString TAILLEPROD);
    void setQUANTITE(int QUANTITE);
    void setCOULEUR(QString COULEUR);
    bool ajouter();
    bool supprimer(int REFPROD);
    QSqlQueryModel* afficher();
    bool modifier(int REFPROD, QString newNOMP, QString newTYPEP, QString newTAILLEPROD, int newQUANTITE, QString newCOULEUR);



private:
    int REFPROD;
        QString TYPEP;
        QString NOMP;
        QString TAILLEPROD;
        int QUANTITE;
        QString COULEUR;
};

#endif // PRODUIT_H

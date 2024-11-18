#ifndef EMPLOYÉS_H
#define EMPLOYÉS_H
#include <Qstring>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employe
{
private:
    int IDE;
    QString NOM;
    QString PRENOM;
    QString ADRESSE;
    QString DATEN;
    QString EMAIL;
    int NUMTEL;
    QString DATEEMBAUCHE;
    QString DATEFIN;
    QString STATUT;
    int NUMCB;
    int IDS,IDC;
public:
    Employe();
    Employe(int IDE , QString NOM, QString PRENOM, QString ADRESSE, QString DATEN, QString EMAIL, int NUMTEL, QString DATEEMBAUCHE, QString DATEFIN, QString STATUT, int NUMCB, int IDS, int IDC);
    int getIde();
    QString getNom();
    QString getPrenom();
    QString getAdresse();
    QString getDateDeNaissance();
    QString getEmail();
    int getNumTel();
    QString getDateEmbauche();
    QString getDateFinContrat();
    QString getStatut();
    int getNumCB();
    int getIds();
    int getIdc();

    void setIde(int);
    void setNom(QString);
    void setPrenom(QString);
    void setAdresse(QString);
    void setDateDeNaissance(QString);
    void setEmail(QString);
    void setNumTel(int);
    void setDateEmbauche(QString);
    void setDateFinContrat(QString);
    void setStatut(QString);
    void setNumCB(int);
    void setIds(int);
    void setIdc(int);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
};

#endif // EMPLOYÉS_H

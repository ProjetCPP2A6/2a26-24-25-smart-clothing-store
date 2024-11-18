#ifndef EMPLOYES_H
#define EMPLOYES_H
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
    int IDS;
    int SALAIRE;
public:

    Employe();
    Employe(int IDE , QString NOM, QString PRENOM, QString ADRESSE, int NUMTEL, QString DATEN, QString EMAIL, QString DATEEMBAUCHE, QString DATEFIN, QString STATUT, int NUMCB, int IDS, int SALAIRE);

    int getIde() { return IDE; }
    QString getNom() { return NOM; }
    QString getPrenom() { return PRENOM; }
    QString getAdresse() { return ADRESSE; }
    QString getDaten() { return DATEN; }
    QString getEmail() { return EMAIL; }
    int getNumTel() { return NUMTEL; }
    QString getDateEmbauche() { return DATEEMBAUCHE; }
    QString getDateFin() { return DATEFIN; }
    QString getStatut() { return STATUT; }
    int getNumCB() { return NUMCB; }
    int getIds() { return IDS; }
    int getSalaire() { return SALAIRE; }

    void setIDE(int newIde) { IDE = newIde; }
    void setNom(QString newNom) { NOM = newNom; }
    void setPrenom(QString newPrenom) { PRENOM = newPrenom; }
    void setAdresse(QString newAdresse) { ADRESSE = newAdresse; }
    void setDaten(QString newDaten) { DATEN = newDaten; }
    void setEmail(QString newEmail) { EMAIL = newEmail; }
    void setNumTel(int newNumTel) { NUMTEL = newNumTel; }
    void setDateEmbauche(QString newDate) { DATEEMBAUCHE = newDate; }
    void setDateFin(QString newDate) { DATEFIN = newDate; }
    void setStatut(QString newStatut) { STATUT = newStatut; }
    void setNumCB(int newNumCB) { NUMCB = newNumCB; }
    void setIds(int newIds) { IDS = newIds; }
    void setSalaire(int newSalaire) { SALAIRE = newSalaire; }

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int IDE);
    bool modifier(int IDE);
    QSqlQueryModel* rechercher(int IDE);
    QSqlQueryModel* trier();
    bool exporter();
    double calculerBonusGlobal(int nombreEmployes, bool inclureAchats, bool inclureLivraisons);
};

#endif // EMPLOYES_H

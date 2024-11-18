#include "Employes.h"
#include <Qstring>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
using namespace std;
Employe::Employe()
{
    IDE=0;
    NOM=0;
    PRENOM=0;
    ADRESSE=0;
    DATEN=0;
    EMAIL=0;
    NUMTEL=0;
    DATEEMBAUCHE=0;
    DATEFIN=0;
    STATUT=0;
    NUMCB=0;
    IDS=0;
    SALAIRE=0;
}
Employe::Employe(int IDE , QString NOM, QString PRENOM, QString ADRESSE, int NUMTEL, QString DATEN, QString EMAIL, QString DATEEMBAUCHE, QString DATEFIN, QString STATUT, int NUMCB, int IDS, int SALAIRE)
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
    this->SALAIRE = SALAIRE;
}


bool Employe::ajouter()
{
    QString res= QString::number(IDE);
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYES (IDE , NOM, PRENOM, ADRESSE,NUMTEL, DATEN, EMAIL,DATEEMBAUCHE,DATEFIN,STATUT,NUMCB,IDS, SALAIRE) VALUES (:IDE , :NOM, :PRENOM, :ADRESSE, :NUMTEL, :DATEN, :EMAIL, :DATEEMBAUCHE, :DATEFIN, :STATUT, :NUMCB, :IDS, :SALAIRE)");
    query.bindValue(":IDE", res);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":ADRESSE", ADRESSE);
    query.bindValue(":DATEN", DATEN);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":NUMTEL", NUMTEL);
    query.bindValue(":DATEEMBAUCHE", DATEEMBAUCHE);
    query.bindValue(":DATEFIN", DATEFIN);
    query.bindValue(":STATUT", STATUT);
    query.bindValue(":NUMCB", NUMCB);
    query.bindValue(":IDS", IDS);
    query.bindValue(":SALAIRE", SALAIRE);
    return query.exec();
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT IDE , NOM, PRENOM, ADRESSE,CAST(NUMTEL AS VARCHAR(20))AS NUMTEL, DATEN, EMAIL,DATEEMBAUCHE,DATEFIN,STATUT,NUMCB,IDS, SALAIRE FROM EMPLOYES");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUMTEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("DATEEN"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("DATEEMBAUCHE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATEFIN"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("STATUT"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("NUMCB"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("IDS"));
    model->setHeaderData(12,Qt::Horizontal,QObject::tr("SALAIRE"));
    return model;
}

bool Employe::supprimer(int IDE)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE IDE = :IDE");
    query.bindValue(":IDE", IDE);
    return query.exec();
}

bool Employe::modifier(int IDE)
{
    QSqlQuery query;
    query.prepare("UPDATE Employes SET NOM=:NOM, PRENOM=:PRENOM, ADRESSE=:ADRESSE, NUMTEL=:NUMTEL, DATEN=:DATEN, EMAIL=:EMAIL, DATEEMBAUCHE=:DATEEMBAUCHE, DATEFIN=:DATEFIN, STATUT=:STATUT, NUMCB=:NUMCB, IDS=:IDS, SALAIRE=:SALAIRE WHERE IDE=:IDE");
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
    query.bindValue(":SALAIRE", this->SALAIRE);

    return query.exec();
}

QSqlQueryModel* Employe::rechercher(int IDE)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = QString("SELECT * FROM EMPLOYES WHERE IDE = %1").arg(IDE);
    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUMTEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATEN"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("DATEEMBAUCHE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATEFIN"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("STATUT"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("NUMCB"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("IDS"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("SALAIRE"));
    return model;
}
QSqlQueryModel* Employe::trier()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = "SELECT IDE, NOM, PRENOM, ADRESSE, NUMTEL, DATEN, EMAIL, DATEEMBAUCHE, DATEFIN, STATUT, NUMCB, IDS, SALAIRE FROM EMPLOYES ORDER BY IDE ASC";

    model->setQuery(queryStr);
    if (model->lastError().isValid())
    {
        qDebug() << "Erreur lors du tri par IDE :" << model->lastError().text();
    }

    return model;
}
bool Employe::exporter()
{
    QSqlQuery query;
    query.prepare("SELECT IDE, NOM, PRENOM, ADRESSE, NUMTEL, DATEN, EMAIL, DATEEMBAUCHE, DATEFIN, STATUT, NUMCB, IDS, SALAIRE FROM EMPLOYES WHERE IDE = :IDE");
    query.bindValue(":IDE", IDE);
    if(query.exec() && query.next())
    {
        IDE =query.value(0).toInt();
        NOM =query.value(1).toString();
        PRENOM =query.value(2).toString();
        ADRESSE =query.value(3).toString();
        NUMTEL =query.value(4).toInt();
        DATEN =query.value(5).toString();
        EMAIL =query.value(6).toString();
        DATEEMBAUCHE =query.value(7).toString();
        DATEFIN =query.value(8).toString();
        STATUT =query.value(9).toString();
        NUMCB =query.value(10).toInt();
        IDS =query.value(11).toInt();
        SALAIRE =query.value(12).toInt();
        return true;
    }
    return false;
}
double Employe::calculerBonusGlobal(int nombreEmployes, bool inclureAchats, bool inclureLivraisons)
{
    QSqlQuery query;
    double totalAchats = 0.0;
    double totalLivraisons = 0.0;
    double tauxBonus = 0.05;
    if (inclureAchats)
    {
        query.prepare("SELECT SUM (MONTANTACHAT) FROM ACHATS");
        if (query.exec() && query.next())
        {
            totalAchats = query.value(0).toDouble();
        }
    }
    if (inclureLivraisons)
    {
        query.prepare("SELECT SUM(MONTANTCO) FROM LIVRAISONS");
        if (query.exec() && query.next())
        {
            totalLivraisons = query.value(0).toDouble();
        }
    }
    double totalGlobal = totalAchats + totalLivraisons;
    double bonusGlobal = totalGlobal * tauxBonus;

    if (nombreEmployes > 0)
    {
        return bonusGlobal / nombreEmployes;
    } else
    {
        return 0.0;
    }
}

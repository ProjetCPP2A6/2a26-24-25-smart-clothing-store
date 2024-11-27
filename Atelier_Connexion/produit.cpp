#include "produit.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QObject>
#include <QSqlQueryModel>


PRODUIT::PRODUIT()
{
    REFPROD=0; TYPEP=" "; NOMP=" "; TAILLEPROD=" "; QUANTITE=0; COULEUR=" ";
}
PRODUIT::PRODUIT(int REFPROD, QString TYPEP, QString NOMP, QString TAILLEPROD, int QUANTITE, QString COULEUR)
{
    this->REFPROD=REFPROD;
    this->TYPEP=TYPEP;
    this->NOMP=NOMP;
    this->TAILLEPROD=TAILLEPROD;
    this->QUANTITE=QUANTITE;
    this->COULEUR=COULEUR;
}
int PRODUIT::getREFPROD()
{return REFPROD;}
QString PRODUIT::getTYPEP()
{return TYPEP;}
QString PRODUIT::getNOMP()
{return NOMP;}
QString PRODUIT::getTAILLEPROD()
{return TAILLEPROD;}
int PRODUIT::getQUANTITE()
{return QUANTITE;}
QString PRODUIT::getCOULEUR()
{return COULEUR;}
void PRODUIT::setREFPROD(int REFPROD){
    this->REFPROD=REFPROD;
}
void PRODUIT::setTYPEP(QString TYPEP)
{
    this->TYPEP=TYPEP;
}
void PRODUIT::setNOMP(QString NOMP)
{
    this->NOMP=NOMP;
}
void PRODUIT::setTAILLEPROD(QString TAILLEPROD)
{
    this->TAILLEPROD=TAILLEPROD;
}
void PRODUIT::setQUANTITE(int QUANTITE)
{
    this->QUANTITE=QUANTITE;
}
void PRODUIT::setCOULEUR(QString COULEUR)
{
    this->COULEUR=COULEUR;
}


bool PRODUIT::ajouter()
{
    bool test = false;
    QSqlQuery query;

    // Prepare the SQL insert query with the correct field names and member variables
    query.prepare("INSERT INTO PRODUITS (REFPROD, TYPEP, NOMP, TAILLEPROD, QUANTITE, COULEUR) "
                  "VALUES (:REFPROD, :TYPEP, :NOMP, :TAILLEPROD, :QUANTITE, :COULEUR)");

    // Bind values from the member variables
    query.bindValue(":REFPROD", REFPROD);
    query.bindValue(":TYPEP", TYPEP);
    query.bindValue(":NOMP", NOMP);
    query.bindValue(":TAILLEPROD", TAILLEPROD);
    query.bindValue(":QUANTITE", QUANTITE);
    query.bindValue(":COULEUR", COULEUR);

    // Execute the query and check for success
    if (query.exec()) {
        test = true;
    } else {
        qDebug() << "Error: " << query.lastError().text();
    }

    return test;
}

bool PRODUIT::supprimer(int REFPROD)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PRODUITS WHERE REFPROD = :REFPROD");
    query.bindValue(":REFPROD", REFPROD);
    return query.exec();
}

QSqlQueryModel* PRODUIT::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    if (!model)
    {
        qDebug() << "Failed to create QSqlQueryModel.";
        return nullptr;
    }

    model->setQuery("SELECT * FROM PRODUITS");

    if (model->lastError().isValid())
    {
        qDebug() << "Error in SQL query: " << model->lastError().text();
        return nullptr;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPEP"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TAILLEPROD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("COULEUR"));

    return model;
}

bool PRODUIT::modifier(int REFPROD, QString newNOMP, QString newTYPEP, QString newTAILLEPROD, int newQUANTITE, QString newCOULEUR) {
    QSqlQuery query;
    query.prepare("UPDATE PRODUITS SET NOMP = :newNOMP, TYPEP = :newTYPEP, TAILLEPROD = :newTAILLEPROD, QUANTITE = :newQUANTITE,  COULEUR = :newCOULEUR WHERE REFPROD = :REFPROD");
    query.bindValue(":newNOMP", newNOMP);
    query.bindValue(":newTYPEP", newTYPEP);
    query.bindValue(":newTAILLEPROD", newTAILLEPROD);
    query.bindValue(":newQUANTITE", newQUANTITE);
    query.bindValue(":newCOULEUR", newCOULEUR);
    query.bindValue(":REFPROD", REFPROD);

    bool success = query.exec();

    if (success) {
        qDebug() << "Record modified successfully!";
    } else {
        qDebug() << "Error modifying record: " << query.lastError().text();
    }

    return success;
}

QSqlQueryModel* PRODUIT::afficher2() //stock
{
    QSqlQueryModel* model = new QSqlQueryModel();

    if (!model)
    {
        qDebug() << "Failed to create QSqlQueryModel.";
        return nullptr;
    }

    model->setQuery("SELECT * FROM PRODUITS");

    if (model->lastError().isValid())
    {
        qDebug() << "Error in SQL query: " << model->lastError().text();
        return nullptr;
    }

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));

    return model;
}

QSqlQueryModel* PRODUIT::afficher3() //rupture
{
    QSqlQueryModel* model = new QSqlQueryModel();

    if (!model)
    {
        qDebug() << "Failed to create QSqlQueryModel.";
        return nullptr;
    }

    // Modify the SQL query to filter rows where QUANTITE = 0
    model->setQuery("SELECT * FROM PRODUITS WHERE QUANTITE = 0");

    if (model->lastError().isValid())
    {
        qDebug() << "Error in SQL query: " << model->lastError().text();
        return nullptr;
    }

    // Set headers for the columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));

    return model;
}


QSqlQueryModel* PRODUIT::afficher4() //alert
{
    QSqlQueryModel* model = new QSqlQueryModel();

    if (!model)
    {
        qDebug() << "Failed to create QSqlQueryModel.";
        return nullptr;
    }

    // Modify the SQL query to filter rows where QUANTITE
    model->setQuery("SELECT * FROM PRODUITS WHERE QUANTITE > 0 AND QUANTITE <= 5");

    if (model->lastError().isValid())
    {
        qDebug() << "Error in SQL query: " << model->lastError().text();
        return nullptr;
    }

    // Set headers for the columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));

    return model;
}


QSqlQueryModel* PRODUIT::afficher5() //prévision
{
    QSqlQueryModel* model = new QSqlQueryModel();

    if (!model)
    {
        qDebug() << "Failed to create QSqlQueryModel.";
        return nullptr;
    }

    // Updated SQL query to select and modify QUANTITE for different product types
    QString queryStr = "SELECT REFPROD, TYPEP, NOMP, "
                       "CASE "
                       "  WHEN TYPEP = 'pull' THEN -(QUANTITE - 50) "
                       "  WHEN TYPEP = 'chemise' THEN -(QUANTITE - 50) "
                       "  WHEN TYPEP = 'pantalon' THEN -(QUANTITE - 50) "
                       "  WHEN TYPEP = 'manteau' THEN -(QUANTITE - 20) "
                       "  WHEN TYPEP = 'chaussure' THEN -(QUANTITE - 30) "
                       "  WHEN TYPEP = 'chaussette' THEN -(QUANTITE - 100) "
                       "  ELSE QUANTITE "
                       "END AS QUANTITE, "
                       "TAILLEPROD, COULEUR "
                       "FROM PRODUITS";

    model->setQuery(queryStr);

    if (model->lastError().isValid())
    {
        qDebug() << "Error in SQL query: " << model->lastError().text();
        return nullptr;
    }

    // Setting headers for the columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPEP"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TAILLEPROD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("COULEUR"));

    return model;
}



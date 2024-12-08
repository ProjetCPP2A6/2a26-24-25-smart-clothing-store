#include "achats.h"
#include <QString>
#include <QSqlQuery>
#include <iostream>
#include <QSqlQueryModel>
#include <QSqlError>


ACHATS::ACHATS( QString TAILLEPROD ,QString METHODEP ,QString DATEACHAT ,int REF,int IDE ,int IDC ,int REFPROD ,float MONTANTACHAT)
{

    this->TAILLEPROD = TAILLEPROD;
    this->REFPROD = REFPROD;
    this->METHODEP = METHODEP;
    this->DATEACHAT = DATEACHAT;
    this->REF = REF;
    this->IDE = IDE;
    this->IDC = IDC;
    this->MONTANTACHAT = MONTANTACHAT;
}
bool ACHATS::ajouter()
{
    QString res = QString::number(REF);
    QSqlQuery query;


    query.prepare("INSERT INTO ACHATS (DATEACHAT, IDC,IDE,METHODEP, MONTANTACHAT,REF, REFPROD, TAILLEPROD) "
                  "VALUES (:DATEACHAT, :IDC, :IDE, :METHODEP, :MONTANTACHAT, :REF, :REFPROD, :TAILLEPROD)");


    query.bindValue(":DATEACHAT", DATEACHAT);
    query.bindValue(":IDC", IDC);
    query.bindValue(":IDE", IDE);
    query.bindValue(":METHODEP", METHODEP);
    query.bindValue(":MONTANTACHAT", MONTANTACHAT);
    query.bindValue(":REF", res);
    query.bindValue(":REFPROD", REFPROD);
    query.bindValue(":TAILLEPROD", TAILLEPROD);



    return query.exec();
 }
    QSqlQueryModel* ACHATS::afficher()
    {
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery("SELECT DATEACHAT, IDC,IDE,METHODEP, MONTANTACHAT,CAST(REF as varchar(20)) AS REF, REFPROD, TAILLEPROD FROM achats");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATEACHAT"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDC"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("METHODEP"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("MONTANTACHAT"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("REF"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("REFPROD"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("TAILLEPROD"));

        return model;
    }
    bool ACHATS::supprimer(int REF)
    {
        QSqlQuery query;
        QString res=QString::number(REF);
        query.prepare("DELETE FROM ACHATS WHERE REF=:REF");
        query.bindValue(":REF", res);
        return query.exec();
    }


    QSqlQueryModel * ACHATS ::rechercher(int REF)
    {
        QSqlQueryModel* model = new QSqlQueryModel();
        QString queryStr = QString("SELECT DATEACHAT, IDC,IDE,METHODEP, MONTANTACHAT,CAST(REF as varchar(20)) AS REF, REFPROD, TAILLEPROD FROM ACHATS WHERE REF=%1").arg(REF);
        model->setQuery(queryStr);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATEACHAT"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDC"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("METHODEP"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("MONTANTACHAT"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("REF"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("REFPROD"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("TAILLEPROD"));

        return model;
    }

    QSqlQueryModel * ACHATS ::trier()
    {
        QSqlQueryModel* model = new QSqlQueryModel();
        QString querystr = "SELECT DATEACHAT, IDC,IDE,METHODEP, MONTANTACHAT,CAST(REF as varchar(20)) AS REF, REFPROD, TAILLEPROD FROM achats ORDER BY REF ASC";
        model->setQuery(querystr);
        if (model->lastError().isValid())
        {
            qDebug()<<"ERREUR LORS DU TRI PAR REF:"<<model->lastError().text();
        }
        return model;


    }
    bool ACHATS::exporter()
    {
        QSqlQuery query;
        query.prepare("SELECT DATEACHAT, IDC,IDE,METHODEP, MONTANTACHAT,CAST(REF as varchar(20)) AS REF, REFPROD, TAILLEPROD FROM ACHATS WHERE REF= :REF");
        query.bindValue(":REF",REF);
        if (query.exec() && query.next())
        {
            DATEACHAT =query.value(0).toString();
            IDC =query.value(1).toInt();
            IDE =query.value(2).toInt();
            METHODEP =query.value(3).toString();
            MONTANTACHAT =query.value(4).toFloat();
            REF =query.value(5).toInt();
            REFPROD =query.value(6).toInt();
            TAILLEPROD =query.value(7).toString();
            return true ;

        }
        return false;

    }
   /* QSqlQueryModel * ACHATS ::rechercher2(int REF)
    {
        QSqlQueryModel* model = new QSqlQueryModel();
        QString queryStr = QString("SELECT DATEACHAT, IDC,IDE,METHODEP, MONTANTACHAT,CAST(REF as varchar(20)) AS REF, REFPROD, TAILLEPROD FROM ACHATS WHERE REF=%1").arg(REF);
        model->setQuery(queryStr);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("DATEACHAT"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDC"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("METHODEP"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("MONTANTACHAT"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("REF"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("REFPROD"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("TAILLEPROD"));

        return model;
    }
    void ACHATS::appliquerDémarque(QString typeDémarque, int selectedRefAchat)
    {
        QSqlQuery query;
        float pourcentageReduction = 0.0;

        // Déterminer le pourcentage de réduction basé sur le type de démarque
        if (typeDémarque == "1ère") {
            pourcentageReduction = 20.0;
        } else if (typeDémarque == "2ème") {
            pourcentageReduction = 30.0;
        } else if (typeDémarque == "3ème") {
            pourcentageReduction = 50.0;
        }

        // Appliquer la réduction sur chaque produit dans les achats (table ACHATS)
        QString updateQuery = QString("UPDATE ACHATS SET MONTANTACHAT = MONTANTACHAT - (MONTANTACHAT * %1 / 100) WHERE REF = :REF").arg(pourcentageReduction);

        query.prepare(updateQuery);
        query.bindValue(":REF", selectedRefAchat);  // Utiliser la référence de l'achat passée en paramètre
        if (!query.exec()) {
            qDebug() << "Erreur lors de l'application de la démarque : " << query.lastError();
        }
    }*/



  /*  bool ACHATS::modifier(int REF)
    {
        QSqlQuery query;
        query.prepare("UPDATE ACHATS SET DATEACHAT=:DATEACHAT, IDC=:IDC, IDE=:IDE, METHODEP=:METHODEP, MONTANTACHAT=:MONTANTACHAT, REF=:REF, REFPROD=:REFPROD,TAILLEPROD=:TAILLEPROD");
        query.bindValue(":DATEACHAT", this->DATEACHAT);
        query.bindValue(":IDC", this->IDC);
        query.bindValue(":IDE", this->IDE);
        query.bindValue(":METHODEP", this->METHODEP);
        query.bindValue(":MONTANTACHAT", this->MONTANTACHAT);
        query.bindValue(":REF", this->REF);
        query.bindValue(":REFPROD", this->REFPROD);
        query.bindValue(":TAILLEPROD", this->TAILLEPROD);


        return query.exec();
    }*/

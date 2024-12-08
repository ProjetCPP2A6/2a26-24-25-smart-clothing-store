#include "clients.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>

Clients::Clients()
{
    NOM="";
    PRENOM="";
    ADRESSE="";
    EMAIL="";
    NUMTEL=0;
    POINTF=0;
}
Clients::Clients(QString NOM, QString PRENOM, QString ADRESSE, QString EMAIL, int NUMTEL, int POINTF)
{
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->ADRESSE=ADRESSE;
    this->EMAIL=EMAIL;
    this->NUMTEL=NUMTEL;
    this->POINTF=POINTF;
}
bool Clients::ajouter()
{
        QSqlQuery query;
        query.prepare("INSERT INTO Clients (NOM, PRENOM, ADRESSE, EMAIL, NUMTEL, POINTF)" "VALUES (:NOM, :PRENOM, :ADRESSE, :EMAIL, :NUMTEL,:POINTF)");
        query.bindValue(":NOM",NOM);
        query.bindValue(":PRENOM",PRENOM);
        query.bindValue(":ADRESSE",ADRESSE);
        query.bindValue(":EMAIL",EMAIL);
        query.bindValue(":NUMTEL",NUMTEL);
        query.bindValue(":POINTF",POINTF);
        return query.exec();
}
QSqlQueryModel *Clients::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT NOM, PRENOM, ADRESSE, EMAIL, CAST(NUMTEL AS VARCHAR(20)) AS NU, POINTF FROM Clients");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUMTEL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("POINTF"));
    return model;
}
bool Clients::supprimer(int NUMTEL)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLients WHERE NUMTEL=:NUMTEL");
    query.bindValue(":NUMTEL",NUMTEL);
    return query.exec();
}
bool Clients::modifier(int NUMTEL)
{
    QSqlQuery query;
    //QString res = QString::number(NUMTEL);
    query.prepare("UPDATE Clients SET NOM=:NOM, PRENOM=:PRENOM, ADRESSE=:ADRESSE,EMAIL=:EMAIL, POINTF=:POINTF WHERE NUMTEL=:NUMTEL");
    query.bindValue("NOM",NOM);
    query.bindValue("PRENOM",PRENOM);
    query.bindValue("ADRESSE",ADRESSE);
    query.bindValue("EMAIL",EMAIL);
    query.bindValue("NUMTEL",NUMTEL);
    query.bindValue("POINTF",POINTF);
    return query.exec();
}
bool Clients::exporter()
{
    QSqlQuery query;
    query.prepare("SELECT NOM, PRENOM, ADRESSE, EMAIL, NUMTEL, POINTF FROM Clients WHERE NUMTEL=:NUMTEL");
    query.bindValue(":NUMTEL",NUMTEL);
    if(query.exec() && query.next())
    {
        NOM=query.value(0).toString();
        PRENOM=query.value(1).toString();
        ADRESSE=query.value(2).toString();
        EMAIL=query.value(3).toString();
        NUMTEL=query.value(4).toInt();
        POINTF=query.value(5).toInt();
        return true;
    }
    return false;
}
void Clients::calculerPointsFidelite()
{
    QString selectQuery = R"(SELECT NUMTEL, SUM(MONTANTACHAT) AS TOTALACHAT FROM ACHAT GROUP BY NUMTEL)";


        QSqlQuery query;
        if (query.exec(selectQuery))
        {
            while (query.next())
            {
                int numtel = query.value("NUMTEL").toInt();
                double totalAchat = query.value("TOTALACHAT").toDouble();

                int pointf = static_cast<int>(totalAchat / 10); // 1 point pour chaque 10 dinars

                // Mise à jour des points de fidélité
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE Client SET POINTF = :POINTF WHERE NUMTEL = :NUMTEL");
                updateQuery.bindValue(":POINTF", pointf);
                updateQuery.bindValue(":NUMTEL", NUMTEL);
                if (!updateQuery.exec())
                {
                    qDebug() << "Erreur lors de la mise à jour pour" << numtel << ":" << updateQuery.lastError().text();
                }
            }
        } else
        {
            qDebug() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        }
}


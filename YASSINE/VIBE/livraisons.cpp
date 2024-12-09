#include "livraisons.h"
#include "ui_acceuil.h"
#include<QMessageBox>

livraisons::livraisons() {}

livraisons::livraisons(long REFL , long IDE , long IDC , long REFPROD, QString TAILLEPROD , QString METHODEP , QString ETAT , QString COULEURPROD , QDate DATECOMMANDE , float MONTANTCOMMANDE)
{
    this->REFL=REFL;
    this->IDE = IDE;
    this->IDC = IDC;
    this->REFPROD = REFPROD;
    this->TAILLEPROD = TAILLEPROD;
    this->METHODEP = METHODEP;
    this->ETAT = ETAT;
    this->COULEURPROD = COULEURPROD;
    this->DATECOMMANDE = DATECOMMANDE;
    this->MONTANTCOMMANDE = MONTANTCOMMANDE;
}

bool livraisons::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(REFL);

    query.prepare("INSERT INTO LIVRAISONS (REFL , IDE , IDC , REFPROD , TAILLEPROD , MONTANTCOMMANDE , METHODEP , DATECOMMANDE , ETAT , COULEURPROD)""VALUES(:REFL , :IDE , :IDC , :REFPROD , :TAILLEPROD , :MONTANTCOMMANDE , :METHODEP , :DATECOMMANDE , :ETAT , :COULEURPROD)");
    query.bindValue(":REFL",res);
    query.bindValue(":IDE", QString::number(IDE));
    query.bindValue(":IDC", QString::number(IDC));
    query.bindValue(":REFPROD",QString::number(REFPROD));
    query.bindValue(":TAILLEPROD", TAILLEPROD);
    query.bindValue(":MONTANTCOMMANDE", MONTANTCOMMANDE);
    query.bindValue(":METHODEP", METHODEP);
    query.bindValue(":DATECOMMANDE", DATECOMMANDE);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":COULEURPROD", COULEURPROD);

    return query.exec();
}

QSqlQueryModel* livraisons::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT CAST(REFL AS VARCHAR(20)) AS REFL,CAST(IDE AS VARCHAR(20)) AS IDE,CAST(IDC AS VARCHAR(20)) AS IDC,REFPROD,TAILLEPROD,COULEURPROD,MONTANTCOMMANDE,METHODEP, DATECOMMANDE,DATEARRIvEE,ETAT FROM LIVRAISONS");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TAILLEPROD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("COULEURPROD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MONTANTCOMMANDE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("METHODEP"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATECOMMANDE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("DATEARRIVEE"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}

bool livraisons::supprimer(long REFL)
{
    QSqlQuery query;
    QString res = QString::number(REFL);

    query.prepare("SELECT CAST(REFL AS VARCHAR(20)) AS REFL,CAST(IDE AS VARCHAR(20)) AS IDE,CAST(IDC AS VARCHAR(20)) AS IDC,REFPROD,TAILLEPROD,COULEURPROD,MONTANTCOMMANDE,METHODEP, DATECOMMANDE,DATEARRIvEE,ETAT FROM LIVRAISONS WHERE REFL=:REFL");
    query.bindValue(":REFL",res);
    if ((query.exec())&&(query.next()))
    {
        this->REFL=REFL;
        IDC = query.value("IDC").toLongLong();
        IDE = query.value("IDE").toLongLong();
        REFPROD = query.value("REFPROD").toLongLong();
        TAILLEPROD = query.value("TAILLEPROD").toString();
        COULEURPROD = query.value("COULEURPROD").toString();
        MONTANTCOMMANDE = query.value("MONTANTCOMMANDE").toFloat();
        METHODEP = query.value("METHODEP").toString();
        DATECOMMANDE = query.value("DATECOMMANDE").toDate();
        ETAT=query.value("ETAT").toString();

        ajouterb();
    }
    QSqlQuery query1;
    query1.prepare("DELETE FROM LIVRAISONS WHERE REFL =:REFL");
    query1.bindValue(":REFL",res);

    return query1.exec();
}

bool livraisons::modifier(long REFL)
{
    QSqlQuery query;
    QString res = QString::number(REFL);

    query.prepare("UPDATE LIVRAISONS SET IDE=:IDE , IDC=:IDC , REFPROD=:REFPROD , TAILLEPROD=:TAILLEPROD , MONTANTCOMMANDE=:MONTANTCOMMANDE , METHODEP=:METHODEP , DATECOMMANDE=:DATECOMMANDE , ETAT=:ETAT , COULEURPROD=:COULEURPROD WHERE REFL=:REFL");
    query.bindValue(":REFL",res);
    query.bindValue(":IDE", QString::number(IDE));
    query.bindValue(":IDC", QString::number(IDC));
    query.bindValue(":REFPROD",QString::number(REFPROD));
    query.bindValue(":TAILLEPROD", TAILLEPROD);
    query.bindValue(":MONTANTCOMMANDE", MONTANTCOMMANDE);
    query.bindValue(":METHODEP", METHODEP);
    query.bindValue(":DATECOMMANDE", DATECOMMANDE);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":COULEURPROD", COULEURPROD);

    return query.exec();
}

QSqlQueryModel* livraisons::recherche_aff_refl (long REFL)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QString queryStr = QString("SELECT CAST(REFL AS VARCHAR(20)) AS REFL,CAST(IDE AS VARCHAR(20)) AS IDE,CAST(IDC AS VARCHAR(20)) AS IDC,REFPROD,TAILLEPROD,COULEURPROD,MONTANTCOMMANDE,METHODEP, DATECOMMANDE,DATEARRIVEE,ETAT FROM LIVRAISONS WHERE REFL= %1").arg(REFL);
    model->setQuery(queryStr);


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TAILLEPROD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("COULEURPROD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MONTANTCOMMANDE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("METHODEP"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATECOMMANDE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("DATEARRIVEE"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}


QSqlQueryModel* livraisons::recherche_aff_IDC(long IDC)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QString queryStr = QString("SELECT CAST(REFL AS VARCHAR(20)) AS REFL,CAST(IDE AS VARCHAR(20)) AS IDE,CAST(IDC AS VARCHAR(20)) AS IDC,REFPROD,TAILLEPROD,COULEURPROD,MONTANTCOMMANDE,METHODEP, DATECOMMANDE,DATEARRIVEE,ETAT FROM LIVRAISONS WHERE IDC= %1").arg(IDC);
    model->setQuery(queryStr);


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TAILLEPROD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("COULEURPROD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MONTANTCOMMANDE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("METHODEP"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATECOMMANDE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("DATEARRIVEE"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}

QSqlQueryModel* livraisons::recherche_aff_DATECOMMANDE (QDate DATECOMMANDE)
{


    QSqlQuery query ;
    query.prepare("SELECT CAST(REFL AS VARCHAR(20)) AS REFL,CAST(IDE AS VARCHAR(20)) AS IDE,CAST(IDC AS VARCHAR(20)) AS IDC,REFPROD,TAILLEPROD,COULEURPROD,MONTANTCOMMANDE,METHODEP, DATECOMMANDE,DATEARRIVEE,ETAT FROM LIVRAISONS WHERE DATECOMMANDE= :DATECOMMANDE");
    query.bindValue(":DATECOMMANDE",DATECOMMANDE);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête : " ;
        return nullptr; // Retourner nullptr en cas d'échec
    }

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TAILLEPROD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("COULEURPROD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MONTANTCOMMANDE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("METHODEP"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATECOMMANDE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("DATEARRIVEE"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}

QSqlQueryModel* livraisons::trier()
{
    QSqlQuery query;
    query.prepare("SELECT CAST(REFL AS VARCHAR(20)) AS REFL,CAST(IDE AS VARCHAR(20)) AS IDE,CAST(IDC AS VARCHAR(20)) AS IDC,REFPROD,TAILLEPROD,COULEURPROD,MONTANTCOMMANDE,METHODEP, DATECOMMANDE,DATEARRIVEE,ETAT FROM LIVRAISONS ORDER BY DATECOMMANDE DESC");
    query.exec();
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(query);


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TAILLEPROD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("COULEURPROD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MONTANTCOMMANDE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("METHODEP"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATECOMMANDE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("DATEARRIVEE"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}

bool livraisons::exporter()
{
    QSqlQuery query;
    query.prepare("SELECT CAST(REFL AS VARCHAR(20)) AS REFL,CAST(IDE AS VARCHAR(20)) AS IDE,CAST(IDC AS VARCHAR(20)) AS IDC,REFPROD,TAILLEPROD,COULEURPROD,MONTANTCOMMANDE,METHODEP, DATECOMMANDE,DATEARRIVEE,ETAT FROM LIVRAISONS WHERE REFL= REFL");
    query.bindValue(":REFL",QString::number(REFL));

    if(query.exec())
    {
        if(query.next())
        {
            REFL=query.value("REFL").toLongLong();
            IDC = query.value("IDC").toLongLong();
            IDE = query.value("IDE").toLongLong();
            REFPROD = query.value("REFPROD").toLongLong();
            TAILLEPROD = query.value("TAILLEPROD").toString();
            COULEURPROD = query.value("COULEURPROD").toString();
            MONTANTCOMMANDE = query.value("MONTANTCOMMANDE").toFloat();
            METHODEP = query.value("METHODEP").toString();
            DATECOMMANDE = query.value("DATECOMMANDE").toDate();
            ETAT=query.value("ETAT").toString();
            return true;
        }
        else
        {
            QMessageBox::warning(nullptr,"COMMANDE","COMMANDE INTROUVABLE");
        }
    }
    return false;
}

bool livraisons::ajouterb()
{
    QSqlQuery query;
    QString res = QString::number(REFL);

    query.prepare("INSERT INTO LIVRAISONSB (REFL , IDE , IDC , REFPROD , TAILLEPROD , MONTANTCOMMANDE , METHODEP , DATECOMMANDE , ETAT , COULEURPROD)""VALUES(:REFL , :IDE , :IDC , :REFPROD , :TAILLEPROD , :MONTANTCOMMANDE , :METHODEP , :DATECOMMANDE , :ETAT , :COULEURPROD)");
    query.bindValue(":REFL",res);
    query.bindValue(":IDE", QString::number(IDE));
    query.bindValue(":IDC", QString::number(IDC));
    query.bindValue(":REFPROD",QString::number(REFPROD));
    query.bindValue(":TAILLEPROD", TAILLEPROD);
    query.bindValue(":MONTANTCOMMANDE", MONTANTCOMMANDE);
    query.bindValue(":METHODEP", METHODEP);
    query.bindValue(":DATECOMMANDE", DATECOMMANDE);
    query.bindValue(":ETAT", ETAT);
    query.bindValue(":COULEURPROD", COULEURPROD);

    return query.exec();
}

QSqlQueryModel* livraisons::afficherb()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT CAST(REFL AS VARCHAR(20)) AS REFL,CAST(IDE AS VARCHAR(20)) AS IDE,CAST(IDC AS VARCHAR(20)) AS IDC,REFPROD,TAILLEPROD,COULEURPROD,MONTANTCOMMANDE,METHODEP, DATECOMMANDE,DATEARRIvEE,ETAT FROM LIVRAISONSB");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFL"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TAILLEPROD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("COULEURPROD"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MONTANTCOMMANDE"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("METHODEP"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("DATECOMMANDE"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("DATEARRIVEE"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("ETAT"));

    return model;
}

bool livraisons::supprimerb(long REFL)
{
    QString res = QString::number(REFL);

    QSqlQuery query1;
    query1.prepare("DELETE FROM LIVRAISONSB WHERE REFL =:REFL");
    query1.bindValue(":REFL",res);

    return query1.exec();
}

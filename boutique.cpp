#include "boutique.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include "QDebug"

boutique::boutique() : id(0), num(0), nom(""), adr("") {}

boutique::boutique(int id)
{
    this->id=id;

}
boutique::boutique(int id,QString nom,QString adr,int num)
{
    this->id=id;
    this->nom=nom;
    this->adr=adr;
    this->num=num;
}
bool boutique::ajouter()
{
    QSqlQuery query;
    QString res=QString::number(id);
    QString nu=QString::number(num);
    query.prepare("insert into BOUTIQUES (IDB,NOM,ADRESSE,NUMB)""values(:id,:nom,:adr,:num)");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":adr",adr);
    query.bindValue(":num",nu);
    return query.exec();
}

QSqlQueryModel *boutique::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select CAST(IDB AS VARCHAR(20))AS IDB , NOM ,ADRESSE,CAST(NUMB AS VARCHAR(20))AS NUMB from BOUTIQUES");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDB"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NUMB"));
    return model;
}

bool boutique::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("DELETE FROM BOUTIQUES WHERE IDB= :id");
    query.bindValue(":id", res);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            return true; // Deletion successful, row was affected
        } else {
            return false; // No rows were affected, id does not exist
        }
    } else {
        return false; // Query execution failed
    }
}
bool boutique::modifier() {
    QSqlQuery query;
    QString res = QString::number(id);
    QString nu = QString::number(num);
    // Corrected SQL query without the extra comma
    query.prepare("UPDATE BOUTIQUES SET NOM = :nom, ADRESSE = :adr, NUMB = :num WHERE IDB = :id");
    query.bindValue(":id", res);
    query.bindValue(":nom", nom);
    query.bindValue(":adr", adr);
    query.bindValue(":num", nu);

    return query.exec();
}
QSqlQueryModel* boutique::rechercher(int id)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString queryStr = QString("SELECT * FROM BOUTIQUES WHERE IDB = %1").arg(id);

    model->setQuery(queryStr);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDB"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMB"));

    return model;
}

bool boutique::enregistrer() {
    // Vérifier la connexion à la base de données
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "La base de données n'est pas connectée.";
        return false;
    }

    // Créer la requête INSERT INTO
    QSqlQuery query;
    query.prepare("INSERT INTO BOUTIQUES (NOM, ADRESSE, NUMB) VALUES (:nom, :adresse, :num)");

    // Lier les valeurs aux paramètres de la requête
    query.bindValue(":nom", nom);
    query.bindValue(":adr", adr);
    query.bindValue(":num", num);

    // Exécuter la requête
    if (query.exec()) {
        qDebug() << "Enregistrement effectué avec succès.";
        return true;
    } else {
        qDebug() << "Erreur lors de l'enregistrement : " << query.lastError().text();
        return false;
    }
}
bool boutique::chargerDepuisBD()
{
    QSqlQuery query;
    query.prepare("SELECT NOM, ADRESSE, NUMB FROM BOUTIQUES WHERE IDB = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        nom = query.value(0).toString();
        adr= query.value(1).toString();
        num= query.value(2).toInt();
        return true;
    }
    return false;
}
QString boutique::getPhoneNumberByName(const QString &nom) {
    QSqlQuery query;
    query.prepare("SELECT NUMTEL FROM EMPLOYES WHERE NOM = :nom");
    query.bindValue(":", nom);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "";
}

QVector<boutique> boutique::recupererBoutique() {
    QVector<boutique> boutiques;
    QSqlQuery query;
    query.prepare("SELECT * FROM BOUTIQUES");
    if(query.exec()){
        while(query.next())
            boutiques.push_back(
                boutique(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toInt())
                );
    }
    return boutiques;
}

QList<QString> boutique::recupererBoutiqueNom(QVector<boutique> boutiques){
    QList<QString> noms;
    for(int i = 0; i < boutiques.size(); i++){
        noms.push_back(boutiques[i].getnom());
    }
    return noms;

}

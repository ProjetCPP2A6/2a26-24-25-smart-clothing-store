#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QVector>
#include <QSqlQuery>

class employe
{
private:
    QString nom;
    QString prenom;
public:
    employe();
    employe(QString, QString);
    QVector<employe> recupererEmployeParBoutique(int idb);
    QString getNom() {return this->nom;}
    QString getPrenom() {return this->prenom;}
};

#endif // EMPLOYE_H

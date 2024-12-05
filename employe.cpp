#include "employe.h"

employe::employe() {}
employe::employe(QString nom, QString prenom){
    this->nom = nom;
    this->prenom = prenom;
}
QVector<employe> employe::recupererEmployeParBoutique(int idb){
    QVector<employe> liste;
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE id_boutique = :idb");
    if(query.exec()){

    }
    return liste;
}

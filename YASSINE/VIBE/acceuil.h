#ifndef ACCEUIL_H
#define ACCEUIL_H

#include <QMainWindow>
#include "qlineedit.h"
#include"qcombobox.h"
#include"qdatetimeedit.h"
#include"livraisons.h"
#include"ArduinoDatabaseLink.h"

namespace Ui {
class acceuil;
}

class acceuil : public QMainWindow
{
    Q_OBJECT

public:
    explicit acceuil(QWidget *parent = nullptr);
    ~acceuil();

private slots:
    void extraire_derRef();

    int extraire_nb_livre();

    int extraire_nb_en_traitement();

    int extraire_nb_retour();

    void afficher_livreur();

    void stats();

    void init_livraions();

    void rafraichir();

    void on_b_produits_clicked();

    void on_b_achats_clicked();

    void on_b_clients_clicked();

    void on_b_employes_clicked();

    void on_b_boutiques_clicked();

    void on_b_livraisons_clicked();

    void on_b_ajouterl_clicked();

    void extraire_client (QLineEdit* numc , QLineEdit* nom , QLineEdit* prenom , QLineEdit* adresse);

    void extraire_produit(QLineEdit* refprod , QLineEdit* nomprod, QComboBox *tailleprod, QLineEdit *couleur, QLineEdit *montant);

    void extraire_livreur(QLineEdit* num , QLineEdit* nom);

    void rechercher(QComboBox *num, QLineEdit* numc, QLineEdit* nom, QLineEdit* prenom, QLineEdit* adresse, QLineEdit* refprod, QLineEdit* nomprod, QComboBox* taillep, QLineEdit* couleurp  , QLineEdit* montantc , QComboBox* methodep , QDateEdit* datec, QLineEdit* nume, QLineEdit* nome);

    void rechercherb(QLineEdit* num,QLineEdit* numc,QLineEdit* nom,QLineEdit* prenom,QLineEdit* adresse,QLineEdit* refprod,QLineEdit* nomprod,QComboBox* taillep,QLineEdit* couleurp  , QLineEdit* montantc , QComboBox* methodep ,QDateEdit* datec, QLineEdit* nume,QLineEdit* nome);

    void nettoyer(QLineEdit* numc, QLineEdit* nomc, QLineEdit* prenomc, QLineEdit* adressec, QLineEdit* refp, QLineEdit* nomp, QLineEdit* couleurp,QLineEdit* montanta, QLineEdit* numl, QLineEdit* noml);

    void on_l_idcl_a_returnPressed();

    void on_l_refArticlel_a_returnPressed();

    void on_l_idel_a_returnPressed();

    void on_b_supprimer_clicked();

    void on_b_modifier_clicked();

    void on_b_rechercher_s_3_clicked();

    void on_b_rech_refl_clicked();

    void on_l_refl_r_activated();

    void on_b_rech_idc_clicked();

    void on_l_idcl_r_returnPressed();

    void on_b_rech_date_clicked();

    void on_l_dateCommande_r_editingFinished();

    void on_b_tri_clicked();

    void on_b_exporter_clicked();

    void on_b_rechercher_s_2_clicked();

    void on_b_supprimer_2_clicked();

    void on_b_restaurer_clicked();

    void on_consulter_l_clicked(const QModelIndex &index);

    void on_consulter_l_2_clicked(const QModelIndex &index);
    void on_consulter_l_doubleClicked(const QModelIndex &index);

private:
    Ui::acceuil *ui;
    livraisons ltmp;
    ArduinoDatabaseLink *arduinoLink;
};

#endif // ACCEUIL_H

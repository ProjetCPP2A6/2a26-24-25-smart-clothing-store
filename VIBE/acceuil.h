#ifndef ACCEUIL_H
#define ACCEUIL_H
#include "achats.h"
#include <QMainWindow>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_ajouterachat_clicked();

    void on_supprimerachat_clicked();

    void on_RECHERCHERachat_clicked();

    void on_trierachat_clicked();

    void on_exporterachat_clicked();

    void on_premierdemarque_clicked();

    /*void on_dexiemedemarque_clicked();

    void on_troisiemedemarque_clicked();*/

    //void on_RECHERCHER_promo_clicked();

    void afficherStatsRefProd();

    void on_dexiemedemarque_clicked();

    void on_troisiemedemarque_clicked();

    void on_statachat_clicked();

private:
    Ui::acceuil *ui;
    ACHATS achats;
};

#endif // ACCEUIL_H

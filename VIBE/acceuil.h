#ifndef ACCEUIL_H
#define ACCEUIL_H

#include "Employes.h"
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
    Ui::acceuil *ui;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_ajouter_e_clicked();

    /*void on_supprimer_e_2_clicked();
    void on_modifier_e_clicked();*/

    void on_supprimer_e_2_clicked();
    void on_rechercher_e_clicked();
    void on_trier_e_clicked();
    void on_Exporter_e_clicked();

    void on_pushButton_56_clicked();

    void on_lineEdit_IDE_Modifier_returnPressed();
    void on_bonusButton_clicked();
private:

    Employe emtp;
};

#endif // ACCEUIL_H

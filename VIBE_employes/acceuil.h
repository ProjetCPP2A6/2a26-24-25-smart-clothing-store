#ifndef ACCEUIL_H
#define ACCEUIL_H
#include "arduino.h"
#include "Employes.h"
#include "qtableview.h"
#include <QMainWindow>

namespace Ui
{
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

    void on_supprimer_e_2_clicked();
    void on_rechercher_e_clicked();
    void on_trier_e_clicked();
    void on_Exporter_e_clicked();

    void on_pushButton_56_clicked();

    void on_lineEdit_IDE_Modifier_returnPressed();

    void on_bonusButton_clicked();

    void afficherStatsEmployes();

    void on_pushButton_graph_clicked();

    void on_pushButton_arduino_clicked();

    void update_label();

private:

    Employe emtp;
    explicit acceuil(QSqlDatabase& db, QWidget* parent = nullptr);
    void on_tabWidget_6_tabBarClicked(int index);
    void calculatePostStatistics(QTableView *tableView);
    QSqlDatabase db;
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire

};

#endif // ACCEUIL_H

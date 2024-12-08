#ifndef ACCEUIL_H
#define ACCEUIL_H
#include "arduino.h"
#include "clients.h"
#include "qserialport.h"
#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>


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

    void on_pushButton_ajouter_clicked();

    void on_pushButton_supp_clicked();

    void on_pushButton_rech_clicked();

    void on_pushButton_rech1_clicked();

    void on_pushButton_mod_clicked();

    void on_pushButton_exporter_clicked();

    void on_pushButton_calcul_clicked();

    void gererChatbot(const QString& reponse);

    void afficherRecommandations();

    void on_pushButton_envoie_clicked();

    void afficherStatsFidelite();

    void on_pushButton_graph_clicked();

    //void on_pushButton_arduino_clicked();   // Implémentation du bouton unique

    void on_pushButton_arduino_clicked();






private:
    Ui::acceuil *ui;
    Clients Etmp;
    QString etape = "DEBUT";  // Initialisation à "DEBUT"
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire

};

#endif // ACCEUIL_H

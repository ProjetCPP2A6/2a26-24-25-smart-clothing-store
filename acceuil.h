#ifndef ACCEUIL_H
#define ACCEUIL_H
#include <QMainWindow>
#include "boutique.h"
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include "employe.h"
#include <QDate>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <qrcode.h>
#include "notif.h"
#include "arduino.h"
namespace Ui {class acceuil;}

class acceuil : public QMainWindow
{
    Q_OBJECT

public:
    explicit acceuil(QWidget *parent = nullptr);
    ~acceuil();
    void sendSms(QDate date_debut, QDate date_fin, QString event, QString nom, QString prenom);
    void eventSms(QString event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_ajouter_clicked();

    void on_modifier_clicked();

    void on_annuler_clicked();

    void on_enregistrer_clicked();

    void on_supprimer_clicked();

    void on_rechercher_clicked();

    void on_lineEdit_recherche_textChanged(const QString &text);

    void on_trier_clicked();

    void on_exporter_clicked();

    void on_envoyerNoel_clicked();

    void on_envoyerBlackFriday_clicked();

    void on_envoyerFinAnnee_clicked();

    void on_statButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void input();

    void on_pushButton_7_clicked();

private:
    Ui::acceuil *ui;

    boutique btq;
    employe emp;
    notif notification;
    QList<QString> getPhoneNumbersOfEmployees();
    bool isBlackFridaySent = false;  // Variable d'état pour Black Friday
    bool isNoelSent = false;         // Variable d'état pour Noël
    bool isFinAnneeSent = false;     // Variable d'état pour Fin d'année
    QVector<boutique> listeBoutiques;
    QByteArray data;  // Contient les données reçues de l'Arduino
    Arduino A;  // Objet pour la communication avec l'Arduino
    QStringList scannedUIDs;  // Liste pour stocker les UIDs scannés


};

#endif // ACCEUIL_H

#include "acceuil.h"
#include "clients.h"
#include "ui_acceuil.h"
#include <QString>
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>
#include <QDebug>
#include <QSqlError>
#include <QTextBrowser>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtSql>
#include <QCategoryAxis>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "arduino.h"


acceuil::acceuil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acceuil)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
    int ret = A.connect_arduino(); // Lancer la connexion à Arduino
    switch (ret) {
    case 0:
        qDebug() << "Arduino is available and connected to :" << A.getarduino_port_name();
        QMessageBox::information(this, "Connection", "Connexion à Arduino validée !");
        return;
        break;
    case 1:
        qDebug() << "Arduino is available but not connected to :" << A.getarduino_port_name();
        break;
    case -1:
        qDebug() << "Arduino is not available";
        QMessageBox::warning(this, "Erreur", "Connexion à Arduino échouée !");

    }

    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(update_label())); // Lancer le slot update_label suite à la réception de readyRead
}

acceuil::~acceuil()
{
    delete ui;
}

void acceuil::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void acceuil::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void acceuil::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void acceuil::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void acceuil::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void acceuil::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}
void acceuil::on_pushButton_ajouter_clicked()
{
    QString NOM=ui->lineEdit_nom->text();
    QString PRENOM=ui->lineEdit_prenom->text();
    QString ADRESSE=ui->lineEdit_adresse->text();
    QString EMAIL=ui->lineEdit_email->text();
    int NUMTEL=ui->lineEdit_numtel->text().toInt();
    int POINTF=ui->lineEdit_pointf->text().toInt();
    Clients Cl(NOM,PRENOM,ADRESSE,EMAIL,NUMTEL,POINTF);
    bool test=Cl.ajouter();
    if(test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué\n" "Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout non effectué\n" "Click Cancel to exit."),QMessageBox::Cancel);
}
void acceuil::on_pushButton_supp_clicked()
{
    int NUMTEL=ui->lineEdit_supp->text().toInt();
    bool test=Etmp.supprimer(NUMTEL);
    if (test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression effectué\n" "Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectué\n" "Click Cancel to exit."),QMessageBox::Cancel);
}
void acceuil::on_pushButton_rech_clicked()
{
    int NUMTEL=ui->lineEdit_rech->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT *FROM Clients WHERE NUMTEL=:NUMTEL");
    query.bindValue(":NUMTEL",NUMTEL);
    if(query.exec())
    {
        if(query.next())
        {
            QString NOM = query.value("NOM").toString();
            QString PRENOM = query.value("PRENOM").toString();
            QString ADRESSE = query.value("ADRESSE").toString();
            QString EMAIL = query.value("EMAIL").toString();
            QString NUMTEL = query.value("NUMTEL").toString();
            QString POINTF = query.value("POINTF").toString();
            ui->lineEdit_n->setText(NOM);
            ui->lineEdit_p->setText(PRENOM);
            ui->lineEdit_ad->setText(ADRESSE);
            ui->lineEdit_e->setText(EMAIL);
            ui->lineEdit_nu->setText(NUMTEL);
            ui->lineEdit_po->setText(POINTF);
            ui->label_nom->setText(NOM);
            ui->label_prenom->setText(PRENOM);
            ui->label_adresse->setText(ADRESSE);
            ui->label_email->setText(EMAIL);
            ui->label_num->setText(NUMTEL);
            ui->label_pointf->setText(POINTF);
        }
        else
        {
            QMessageBox::warning(this, "Clients", "Client non retrouvé.");
        }
    }
}
void acceuil::on_pushButton_mod_clicked()
{
    QString nom=ui->lineEdit_n->text();
    QString prenom=ui->lineEdit_p->text();
    QString adresse=ui->lineEdit_ad->text();
    QString email=ui->lineEdit_e->text();
    int numtel=ui->lineEdit_nu->text().toInt();
    int pointf=ui->lineEdit_po->text().toInt();

    Clients cl1(nom,prenom,adresse,email,numtel,pointf);

    bool test=cl1.modifier(numtel);
    if(test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Modification effectuée\n" "Click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Modification non effectuée\n" "Click Cancel to exit."),QMessageBox::Cancel);
}

void acceuil::on_pushButton_exporter_clicked()
{
    //Demander le num de telephone du client a exporter
    int numtel=QInputDialog::getInt(this,"Exporter un client", "Entrer le numéro de téléphone du client a exporté:");
    if(numtel<=0)
    {
        QMessageBox::warning(this,"Erreur", "Numéro de téléphone invalide. Veuillez réessayer.");
        return;
    }
    //Creer un objet client et definir son NUMTEL
    Clients CL;
    CL.setNumtel(numtel);
    //Appel de la methode exporter
    if(!CL.exporter())
    {
        QMessageBox:: critical(this,"Erreur", "Impossible de récupérer les données du clients. Verifier le numéro de téléphone.");
        return;
    }
    //Demander ou enregistrer le fichier PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer sous ", QString("Employe_%1.pdf").arg(numtel), "Fichier PDF(*.pdf)");
    if(filePath.isEmpty())
    {
        QMessageBox::warning(this,"Annulation", "L'exportation a été annulée.");
        return;
    }
    //Generer le fichier pdf
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter(&printer);
    if(!painter.isActive())
    {
        QMessageBox::critical(this,"Erreur", "Impossible de créer le fichier PDF");
        return;
    }
    //Ajout les informations du client dnas le PDF
    painter.setFont(QFont("Arial",12));
    painter.drawText(100, 100, QString("Fiche du client: %1").arg(numtel));
    painter.drawText(100, 200, QString("NOM: %1").arg(CL.getNom()));
    painter.drawText(100, 200, QString("PRENOM: %1").arg(CL.getPrenom()));
    painter.drawText(100, 300, QString("ADRESSE: %1").arg(CL.getAdresse()));
    painter.drawText(100, 400, QString("EMAIL: %1").arg(CL.getEmail()));
    painter.drawText(100, 500, QString("POINTF: %1").arg(CL.getPointf()));
    painter.end();

    //Etape de confirmation
    QMessageBox::information(this, "Succés", "Le fichier PDF a été exporté avec succées.");
}
void acceuil::on_pushButton_rech1_clicked()
{
    int NUMTEL=ui->lineEdit_rech1->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT *FROM Clients WHERE NUMTEL=:NUMTEL");
    query.bindValue(":NUMTEL",NUMTEL);
    if(query.exec())
    {
        if(query.next())
        {
            QString NOM = query.value("NOM").toString();
            QString PRENOM = query.value("PRENOM").toString();
            QString ADRESSE = query.value("ADRESSE").toString();
            QString EMAIL = query.value("EMAIL").toString();
            QString NUMTEL = query.value("NUMTEL").toString();
            QString POINTF = query.value("POINTF").toString();

            ui->label_nom1->setText(NOM);
            ui->label_prenom1->setText(PRENOM);
            ui->label_adresse1->setText(ADRESSE);
            ui->label_email1->setText(EMAIL);
            ui->label_num1->setText(NUMTEL);
            //ui->label_pointf1->setText(POINTF);
        }
        else
        {
            QMessageBox::warning(this, "Clients", "Client non retrouvé.");
        }
    }
}
void acceuil::on_pushButton_calcul_clicked()
{
    Clients client;
    client.calculerPointsFidelite();
    qDebug() << "Calcul des points de fidélité exécuté.";
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT NOM, PRENOM, CAST(NUMTEL AS VARCHAR(20)) AS NU,POINTF FROM Clients");

        // Vérifier si la requête a échoué
        if (model->lastError().isValid())
    {
        qDebug() << "Erreur SQL : " << model->lastError().text();
            return; // ou afficher un message d'erreur à l'utilisateur
    }

        // Définir les en-têtes pour le QTableView
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUMTEL"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("POINTF"));

        // Associer le modèle au tableView
        ui->tableView_pointf->setModel(model);
}


void acceuil::gererChatbot(const QString& reponse)
{
    // Initialisation de l'étape
    if (etape == "DEBUT")
    {
        ui->textBrowser_chat->append("Chatbot : Bonjour ! Quel est votre numéro de téléphone ?");
        etape = "NUMTEL";
    }
    // Collecter le numéro de téléphone
    else if (etape == "NUMTEL")
    {
        int numtel = reponse.toInt();  // Conversion de QString en int sans vérifier 'ok'
        Etmp.setNumtel(numtel);  // Utiliser le setter
        ui->textBrowser_chat->append("Chatbot : Quel est votre genre ? (Homme/Femme)");
        etape = "SEXE";
    }
    // Collecter le genre
    else if (etape == "SEXE") {
        Etmp.setSexe(reponse);
        ui->textBrowser_chat->append("Chatbot : Quel est votre âge ?");
        etape = "AGE";
    }
    // Collecter l'âge
    else if (etape == "AGE")
    {
        int age = reponse.toInt();  // Conversion de QString en int
        Etmp.setAge(age);
        ui->textBrowser_chat->append("Chatbot : Quel est votre style préféré ? (Décontracté/Chic/Sportif/Classique)");
        etape = "STYLE";
    }
    // Collecter le style
    else if (etape == "STYLE")
    {
        Etmp.setStyle(reponse);
        ui->textBrowser_chat->append("Chatbot : Quelle est votre couleur préférée ? (bleu/rouge/vert/jaune)");
        etape = "COULEUR";
    }
    // Collecter la couleur
    else if (etape == "COULEUR")
    {
        Etmp.setCouleur(reponse);
        ui->textBrowser_chat->append("Chatbot : Voici nos recommandations :");
        afficherRecommandations();  // Appeler la méthode sans paramètres
        etape = "FIN";
    }
    // Fin de la conversation
    else if (etape == "FIN")
    {
        ui->textBrowser_chat->append("Chatbot : Voulez-vous faire autre chose ? (Oui/Non)");
        if (reponse== "oui")
        {
            etape = "DEBUT";
            ui->textBrowser_chat->clear();  // Nettoyer l'interface avant de redémarrer
            ui->textBrowser_chat->append("Chatbot : Vous avez encore besoin de moi ?");
        }
        else
        {
            ui->textBrowser_chat->append("Chatbot : Merci de votre visite ! À bientôt !");
        }


        /*if (reponse.toLower() == "oui") {
            etape = "DEBUT";
            ui->textBrowser_chat->clear();  // Nettoyer l'interface avant de redémarrer
            ui->textBrowser_chat->append("Chatbot : Vous avez besoin de quelque chose d'autre ?");
        } else {
            ui->textBrowser_chat->append("Chatbot : Merci de votre visite ! À bientôt !");
        }*/
    }
}


void acceuil::afficherRecommandations()
{

    QSqlQuery query;

    // Affichage des valeurs des paramètres pour le débogage
    qDebug() << "SEXE: " << Etmp.getSexe();
    qDebug() << "AGE: " << Etmp.getAge();
    qDebug() << "STYLE: " << Etmp.getStyle();
    qDebug() << "COULEUR: " << Etmp.getCouleur();


    query.prepare("SELECT NOMP, COULEUR, SEXE, STYLE "
                  "FROM PRODUITS "
                  "WHERE SEXE = :SEXE "
                  "AND :AGE BETWEEN AGE_MIN AND AGE_MAX "
                  "AND STYLE = :STYLE" "AND COULEUR = :COULEUR");

    query.bindValue(":SEXE", Etmp.getSexe());  // Utilisation du getter pour accéder au genre
    query.bindValue(":AGE", Etmp.getAge());     // Utilisation du getter pour accéder à l'âge
    query.bindValue(":STYLE", Etmp.getStyle()); // Utilisation du getter pour accéder au style
    query.bindValue(":COULEUR", Etmp.getCouleur()); // Utilisation du getter pour accéder a la couleur

    // Affichage de la requête SQL exécutée
    qDebug() << query.lastQuery();

    if (query.exec()) {
        while (query.next()) {
            QString produit = query.value("NOM").toString() + " - " +
                              query.value("COULEUR").toString() + " - " +
                              query.value("SEXE").toString() + " - " +
                              query.value("STYLE").toString();
            ui->textBrowser_chat->append("• " + produit);
        }
    } else {
        qDebug() << "Erreur d'exécution de la requête: " << query.lastError().text();
    }
}

void acceuil::on_pushButton_envoie_clicked()
{
    QString reponse = ui->lineEdit_envoie->text();
    ui->textBrowser_chat->append("Vous : " + reponse);
    ui->lineEdit_envoie->clear();
    gererChatbot(reponse);
}

void acceuil::afficherStatsFidelite()
{
    // Étape 1 : Récupération des données depuis la base de données
    QVector<int> stats(3, 0); // Peu fidèles, Modérément fidèles, Très fidèles

    QSqlQuery query;
    query.prepare(
        "SELECT "
        "SUM(CASE WHEN POINTF BETWEEN 0 AND 10 THEN 1 ELSE 0 END) AS PeuFideles, "
        "SUM(CASE WHEN POINTF BETWEEN 11 AND 100 THEN 1 ELSE 0 END) AS ModerementFideles, "
        "SUM(CASE WHEN POINTF > 100 THEN 1 ELSE 0 END) AS TresFideles "
        "FROM Clients");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données : " + query.lastError().text());
        return;
    }

    if (query.next())
    {
        stats[0] = query.value(0).toInt(); // Peu fidèles
        stats[1] = query.value(1).toInt(); // Modérément fidèles
        stats[2] = query.value(2).toInt(); // Très fidèles
    }
    else
    {
        QMessageBox::information(this, "Aucune donnée", "La table Client est vide ou ne contient pas de points de fidélité.");
        return;
    }

    // Étape 2 : Création du graphique avec QChart
    QBarSet *set = new QBarSet("Nombre de clients");
    *set << stats[0] << stats[1] << stats[2]; // Ajout des données

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des points de fidélité");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories = {"Peu fidèles", "Modérément fidèles", "Très fidèles"};
    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->append(categories[0], 0);
    axisX->append(categories[1], 1);
    axisX->append(categories[2], 2);

    chart->createDefaultAxes();
    chart->addAxis(axisX, Qt::AlignBottom); // Ajouter l'axe X au graphique
    series->attachAxis(axisX); // Associer l'axe X à la série
    chart->legend()->setVisible(false);

    // Étape 3 : Affichage dans QChartView
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Nettoyer tout graphique précédent
    if (ui->widget_graph->layout() != nullptr) {
        QLayoutItem *item;
        while ((item = ui->widget_graph->layout()->takeAt(0)) != nullptr) {
            delete item->widget(); // Supprime le widget du layout
            delete item;           // Supprime l'item lui-même
        }
    } else {
        // Si le widget_graph n'a pas de layout, créez-en un
        QVBoxLayout *layout = new QVBoxLayout(ui->widget_graph);
        ui->widget_graph->setLayout(layout);
    }

    // Ajouter le graphique au widget
    ui->widget_graph->layout()->addWidget(chartView);

    //QMessageBox::information(this, "Succès", "Le graphique des points de fidélité a été généré.");
}
void acceuil::on_pushButton_graph_clicked()
{
    ui->setupUi(this);
    //connect(ui->pushButton_graph, &QPushButton::clicked, this, &acceuil::afficherStatsFidelite);
    afficherStatsFidelite();
}

/*void acceuil::update_label()
{
    data = A.read_from_arduino();
    if (data == "90")
        ui->label_3->setText("90°");
    else if (data == "0")
        ui->label_3->setText("0°");
}*/

/*void acceuil::on_pushButton_arduino_clicked()   // Implémentation du bouton unique
{
    QSqlQuery query;
    query.prepare("SELECT NV FROM Boutiques WHERE IDB = :IDB");
    query.bindValue(":IDB", 1); // ID de la boutique cible (exemple ici)
    if (query.exec())
    {
        if (query.next())
        {
            int nbrVisites = query.value(0).toInt();  // Récupérer le nombre de visites actuel

            // Vérifier si le nombre de visites est 10 ou plus
            if (nbrVisites > 10)
            {
                // Faire bouger le servo deux fois
                A.write_to_arduino("n");  // Déplacer le servo à 90°
            }
            else
            {
                // Sinon, faire bouger le servo une seule fois
                A.write_to_arduino("m");  // Déplacer le servo
            }

            //Incrémenter "nombre de visite" dans la base de données
            query.prepare("UPDATE Boutiques SET NV = NV + 1 WHERE IDB = :IDB");
            query.bindValue(":IDB", 1); // IDB de la boutique cible (exemple ici)
            if (query.exec())
            {
                // Afficher un message dans une boîte de dialogue
                QMessageBox::information(this, "Succès", "Nombre de visite mis à jour avec succès.");
            } else
            {
                // Afficher un message d'erreur si la mise à jour échoue
                QMessageBox::warning(this, "Erreur", "Erreur lors de la mise à jour du nombre de visites : " + query.lastError().text());
                return;
            }
        }
        else{
                // Si la requête pour récupérer le nombre de visites échoue
                QMessageBox::warning(this, "Erreur", "Erreur lors de la récupération du nombre de visites : " + query.lastError().text());
            }
    }
}*/

void acceuil::on_pushButton_arduino_clicked() {
    Arduino arduino; // Créer une instance Arduino pour gérer la communication série

    // Connexion à Arduino si elle n'est pas déjà ouverte
    if (!arduino.getserial()->isOpen()) {
        if (arduino.connect_arduino() == 0) {
            QMessageBox::information(this, "Connexion", "Connexion à Arduino réussie !");
            qDebug() << "Connexion réussie à Arduino";
        } else {
            QMessageBox::warning(this, "Erreur", "Connexion à Arduino échouée !");
            qDebug() << "Erreur de connexion";
            return;
        }
    }

    // Lire les données envoyées par Arduino
    if (arduino.getserial()->bytesAvailable()) {
        QByteArray data = arduino.getserial()->readAll();
        QString command = QString::fromStdString(data.toStdString()).trimmed();
        qDebug() << "Données reçues depuis Arduino: " << command;

        if (command == "1") {
            // Lorsque le bouton Arduino est pressé, incrémenter NV dans la base de données

            QSqlQuery query;
            query.prepare("SELECT NV FROM Boutiques WHERE IDB = :IDB");
            query.bindValue(":IDB", 1); // ID de la boutique cible

            if (query.exec()) {
                if (query.next()) {
                    int nbrVisites = query.value(0).toInt();  // Récupérer le nombre de visites actuel

                    // Mettre à jour NV dans la base de données
                    query.prepare("UPDATE Boutiques SET NV = NV + 1 WHERE IDB = :IDB");
                    query.bindValue(":IDB", 1);
                    if (query.exec()) {
                        qDebug() << "Nombre de visites mis à jour avec succès.";

                        // Vérifier si NV est inférieur ou supérieur à 10 et envoyer la commande appropriée à Arduino
                        if (nbrVisites >= 10) {
                            // NV >= 10, envoyer 'n' pour faire tourner le moteur à 180°
                            arduino.write_to_arduino("n");
                            qDebug() << "NV >= 10, envoi de la commande 'n' à Arduino (moteur à 180°).";
                        } else {
                            // NV < 10, envoyer 'm' pour faire tourner le moteur à 90°
                            arduino.write_to_arduino("m");
                            qDebug() << "NV < 10, envoi de la commande 'm' à Arduino (moteur à 90°).";
                        }

                        QMessageBox::information(this, "Succès", "Incrémentation du nombre de visites réussie.");
                    } else {
                        QMessageBox::warning(this, "Erreur", "Erreur lors de la mise à jour du nombre de visites : " + query.lastError().text());
                    }
                } else {
                    QMessageBox::warning(this, "Erreur", "Erreur lors de la récupération du nombre de visites.");
                }
            } else {
                QMessageBox::warning(this, "Erreur", "Erreur lors de l'exécution de la requête SQL : " + query.lastError().text());
            }
        }
    }
}

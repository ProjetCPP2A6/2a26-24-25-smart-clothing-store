#include "acceuil.h"
#include "ui_acceuil.h"
#include "Employes.h"
#include <QSqlError>
#include<QMessageBox>
#include <QInputDialog>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QSqlRecord>
#include "arduino.h"
//#include <QtCharts/QPieSeries>
//#include <QtCharts/QPieSlice>

acceuil::acceuil(QWidget *parent) :QMainWindow(parent),ui(new Ui::acceuil)
{
    ui->setupUi(this);

    // Initialiser la tableView avec les données des employés
    ui->tableView->setModel(emtp.afficher());
    int ret = A.connect_arduino();
    switch (ret) {
    case 0:
        qDebug() << "Arduino connecté sur :" << A.getarduino_port_name();
        break;
    case 1:
        qDebug() << "Arduino disponible mais non connecté.";
        break;
    case -1:
        qDebug() << "Arduino non disponible.";
        break;
    }

    // Connexion du signal readyRead
    connect(A.getserial(), &QSerialPort::readyRead, this, &acceuil::update_label);
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
void acceuil::on_ajouter_e_clicked()
{
    int IDE = ui->lineEdit_IDE->text().toInt();
    QString NOM = ui->lineEdit_nom->text();
    QString PRENOM = ui->lineEdit_prenom->text();
    QString ADRESSE = ui->lineEdit_adresse->text();
    QString DATEN = ui->lineEdit_DATEN->text();
    QString EMAIL = ui->lineEdit_email->text();
    int NUMTEL = ui->lineEdit_numtel->text().toInt();
    QString DATEEMBAUCHE = ui->lineEdit_DATEM->text();
    QString DATEFIN = ui->lineEdit_Fin->text();
    QString STATUT = ui->lineEdit_statut->text();
    int NUMCB = ui->lineEdit_NUMCB->text().toInt();
    int IDS = ui->lineEdit_IDS->text().toInt();
    int SALAIRE = ui->lineEdit_SALAIRE->text().toInt();
    QString CODE = ui->lineEdit_CODE->text();
    QString PRESENCE = ui->lineEdit_PRESENCE->text();
    int NOMBRE_DENTREE = ui->lineEdit_NOMBRE_DENTREE->text().toInt();

    Employe e(IDE , NOM, PRENOM, ADRESSE,NUMTEL, DATEN, EMAIL,DATEEMBAUCHE,DATEFIN,STATUT,NUMCB,IDS, SALAIRE,CODE, PRESENCE, NOMBRE_DENTREE);
    bool test = e.ajouter();
    if (test) {
        ui->tableView->setModel(emtp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"), QObject::tr("Succès", "Employé ajouté avec succès!"), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr("Erreur", "Échec de l'ajout de l'employé."), QMessageBox::Cancel);
    }
}

void acceuil::on_supprimer_e_2_clicked()
{
    int IDE = ui->lineEdit_idSupprimer->text().toInt();  // Récupérer l'ID depuis l'interface
    Employe e;  // Créer un objet Employe
    if (e.supprimer(IDE)) {
        ui->tableView->setModel(emtp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"), QObject::tr("Employé supprimé avec succès!"), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr("Échec de la suppression de l'employé."), QMessageBox::Cancel);
    }
}
void acceuil::on_rechercher_e_clicked()
{
    QString text = ui->lineEdit_rechercher->text();
    Employe e;
    if(!text.isEmpty())
    {
        int ide=text.toInt();
        QSqlQueryModel* model = e.rechercher(ide);
        ui->tableView_recherche->setModel(model);
    }
    else
    {
        ui->tableView_recherche->setModel(e.afficher());
    }
}
void acceuil::on_trier_e_clicked()
{
    Employe emp;
    QSqlQueryModel* model = emp.trier();
    ui->tableView_tri->setModel(model);
}
void acceuil::on_Exporter_e_clicked()
{
    int employeIDE = QInputDialog::getInt(this, "Exporter un employé", "Entrez l'ID de l'employé à exporter :");
    if (employeIDE <= 0)
    {
        QMessageBox::warning(this, "Erreur", "ID invalide. Veuillez réessayer.");
        return;
    }
    Employe e;
    e.setIDE(employeIDE);
    if (!e.exporter())
    {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données de l'employé. Vérifiez l'ID.");
        return;
    }
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer sous", QString("Employe_%1.pdf").arg(employeIDE), "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty())
    {
        QMessageBox::warning(this, "Annulation", "L'exportation a été annulée.");
        return;
    }
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter(&printer);
    if (!painter.isActive())
    {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }
    painter.setFont(QFont("Arial", 19));
    painter.drawText(100, 100, QString("Fiche de l'employé : %1").arg(employeIDE));
    painter.drawText(100, 200, QString("Nom : %1").arg(e.getNom()));
    painter.drawText(100, 300, QString("Prénom : %1").arg(e.getPrenom()));
    painter.drawText(100, 400, QString("Adresse : %1").arg(e.getAdresse()));
    painter.drawText(100, 500, QString("Numéro de téléphone : %1").arg(e.getNumTel()));
    painter.drawText(100, 600, QString("Date de naissance : %1").arg(e.getDaten()));
    painter.drawText(100, 700, QString("Email : %1").arg(e.getEmail()));
    painter.drawText(100, 800, QString("Date d'embauche : %1").arg(e.getDateEmbauche()));
    painter.drawText(100, 900, QString("Date de fin : %1").arg(e.getDateFin()));
    painter.drawText(100, 1000, QString("Statut : %1").arg(e.getStatut()));
    painter.drawText(100, 1100, QString("Numéro CB : %1").arg(e.getNumCB()));
    painter.drawText(100, 1200, QString("ID Supérieur : %1").arg(e.getIds()));
    painter.drawText(100, 1300, QString("Salaire : %1").arg(e.getSalaire()));
    painter.drawText(100, 1400, QString("Code : %1").arg(e.getCode()));
    painter.drawText(100, 1500, QString("Présence : %1").arg(e.getprésence()));
    painter.drawText(100, 1600, QString("Nombre de présences : %1").arg(e.getNombre()));

    painter.end();
    QMessageBox::information(this, "Succès", "Le fichier PDF a été exporté avec succès !");
}


void acceuil::on_pushButton_56_clicked()
{
    int IDE = ui->lineEdit_IDE_Modifier->text().toInt();
    QString NOM = ui->lineEdit_nom_Modifier->text();
    QString PRENOM = ui->lineEdit_prenom_Modifier->text();
    QString ADRESSE = ui->lineEdit_adresse_Modifier->text();
    QString DATEN = ui->lineEdit_DATEN_Modifier->text();
    QString EMAIL = ui->lineEdit_email_Modifier->text();
    int NUMTEL = ui->lineEdit_numtel_Modifier->text().toInt();
    QString DATEEMBAUCHE = ui->lineEdit_DATEM_Modifier->text();
    QString DATEFIN = ui->lineEdit_Fin_Modifier->text();
    QString STATUT = ui->lineEdit_statut_Modifier->text();
    int NUMCB = ui->lineEdit_NUMCB_Modifier->text().toInt();
    int IDS = ui->lineEdit_IDS_Modifier->text().toInt();
    int SALAIRE = ui->lineEdit_SALAIRE_Modifier->text().toInt();
    QString CODE = ui->lineEdit_CODE_Modifier->text();
    QString PRESENCE = ui->lineEdit_PRESENCE_Modifier->text();
    int NOMBRE_DENTREE = ui->lineEdit_NOMBRE_DENTREE_Modifier->text().toInt();

    Employe e(IDE , NOM, PRENOM, ADRESSE,NUMTEL, DATEN, EMAIL,DATEEMBAUCHE,DATEFIN,STATUT,NUMCB,IDS, SALAIRE,CODE, PRESENCE, NOMBRE_DENTREE);

    bool test = e.modifier(IDE);
    if (test) {
        ui->tableView->setModel(emtp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"), QObject::tr("Succès", "Employé modifié avec succès!"), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("not ok"), QObject::tr("Erreur", "Échec de la modification de l'employé."), QMessageBox::Cancel);
    }

}


void acceuil::on_lineEdit_IDE_Modifier_returnPressed()
{
    int IDE = ui->lineEdit_IDE_Modifier->text().toInt();
    QSqlQuery query;
    query.prepare("SELECT * FROM EMPLOYES WHERE IDE=:IDE");
    query.bindValue(":IDE",IDE);

    if((query.exec())&&(query.next()))
    {
        QString NOM = query.value("NOM").toString();
        QString PRENOM = query.value("PRENOM").toString();
        QString ADRESSE = query.value("ADRESSE").toString();
        QString DATEN = query.value("DATEN").toString();
        QString EMAIL = query.value("EMAIL").toString();
        QString NUMTEL = query.value("NUMTEL").toString();
        QString DATEEMBAUCHE = query.value("DATEEMBAUCHE").toString();
        QString DATEFIN = query.value("DATEFIN").toString();
        QString STATUT = query.value("STATUT").toString();
        QString NUMCB = query.value("NUMCB").toString();
        QString IDS = query.value("IDS").toString();
        QString SALAIRE = query.value("SALAIRE").toString();
        QString CODE = query.value("CODE").toString();
        QString PRESENCE = query.value("PRESENCE").toString();
        QString NOMBRE_DENTREE = query.value("NOMBRE_DENTREE").toString();

        ui->lineEdit_nom_Modifier->setText(NOM);
        ui->lineEdit_prenom_Modifier->setText(PRENOM);
        ui->lineEdit_adresse_Modifier->setText(ADRESSE);
        ui->lineEdit_DATEN_Modifier->setText(DATEN);
        ui->lineEdit_email_Modifier->setText(EMAIL);
        ui->lineEdit_numtel_Modifier->setText(NUMTEL);
        ui->lineEdit_DATEM_Modifier->setText(DATEEMBAUCHE);
        ui->lineEdit_Fin_Modifier->setText(DATEFIN);
        ui->lineEdit_statut_Modifier->setText(STATUT);
        ui->lineEdit_NUMCB_Modifier->setText(NUMCB);
        ui->lineEdit_IDS_Modifier->setText(IDS);
        ui->lineEdit_SALAIRE_Modifier->setText(SALAIRE);
        ui->lineEdit_CODE_Modifier->setText(CODE);
        ui->lineEdit_PRESENCE_Modifier->setText(PRESENCE);
        ui->lineEdit_NOMBRE_DENTREE_Modifier->setText(NOMBRE_DENTREE);
    }
}
void acceuil::on_bonusButton_clicked()
{
    QString identifiant = ui->idInput->text();
    if (identifiant.isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un identifiant valide.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT salaire FROM EMPLOYES WHERE IDE = :identifiant");
    query.bindValue(":identifiant", identifiant);

    int salaire = 0;
    if (query.exec() && query.next())
    {
        salaire = query.value(0).toInt();
    } else
    {
        QMessageBox::warning(this, "Erreur", "Aucun employé trouvé avec cet identifiant.");
        return;
    }

    double totalAchats = 0.0;
    query.prepare("SELECT SUM (MONTANTACHAT) FROM ACHATS");
    if (query.exec() && query.next())
    {
        totalAchats = query.value(0).toFloat();
    }

    double totalLivraisons = 0.0;
    query.prepare("SELECT SUM(MONTANTCO) FROM LIVRAISONS");
    if (query.exec() && query.next())
    {
        totalLivraisons = query.value(0).toFloat();
    }

    double totalSalaires = 0;
    query.prepare("SELECT SALAIRE FROM EMPLOYES");
    if (query.exec())
    {
        while (query.next())
        {
            totalSalaires += query.value(0).toInt();
        }
    }

    if (totalSalaires <= 0)
    {
        QMessageBox::warning(this, "Erreur", "Impossible de calculer les bonus, les données des salaires sont invalides.");
        return;
    }

    double tauxBonus = 0.05; // 5% du total comme bonus global
    double bonusGlobal = (totalAchats + totalLivraisons) * tauxBonus;
    double bonusEmploye = bonusGlobal * (salaire / totalSalaires);

    QMessageBox::information(this, "Bonus Employé",QString("Le bonus pour l'employé avec l'identifiant '%1' est de : %2 €").arg(identifiant).arg(bonusEmploye, 0, 'f', 2)); // 2 décimales
}

void acceuil::afficherStatsEmployes()
{
    QVector<int> statsSALAIRE(3, 0);
    QVector<int> statsSTATUT(3, 0);
    QVector<int> statsDATEEMBAUCHE(3, 0);

    QSqlQuery query;

    // Salaires
    query.prepare(
        "SELECT "
        "COUNT(CASE WHEN SALAIRE BETWEEN 0 AND 2000 THEN 1 ELSE NULL END) AS Faibles, "
        "COUNT(CASE WHEN SALAIRE BETWEEN 2001 AND 5000 THEN 1 ELSE NULL END) AS Moyens, "
        "COUNT(CASE WHEN SALAIRE > 5000 THEN 1 ELSE NULL END) AS Eleves "
        "FROM EMPLOYES"
        );
    if (query.exec() && query.next()) {
        statsSALAIRE[0] = query.value(0).toInt();
        statsSALAIRE[1] = query.value(1).toInt();
        statsSALAIRE[2] = query.value(2).toInt();
    } else {
        qDebug() << "Erreur SQL pour les salaires:" << query.lastError();
    }

    // Statuts
    query.prepare(
        "SELECT "
        "COUNT(CASE WHEN STATUT = 'RH' THEN 1 ELSE NULL END) AS RH, "
        "COUNT(CASE WHEN STATUT = 'LIVREUR' THEN 1 ELSE NULL END) AS LIVREUR, "
        "COUNT(CASE WHEN STATUT = 'VENDEUR' THEN 1 ELSE NULL END) AS VENDEUR "
        "FROM EMPLOYES"
        );
    if (query.exec() && query.next()) {
        statsSTATUT[0] = query.value(0).toInt();
        statsSTATUT[1] = query.value(1).toInt();
        statsSTATUT[2] = query.value(2).toInt();
    } else {
        qDebug() << "Erreur SQL pour les statuts:" << query.lastError();
    }

    // Dates d'embauche
    query.prepare(
        "SELECT "
        "COUNT(CASE WHEN DATEEMBAUCHE < '2022-01-01' THEN 1 ELSE NULL END) AS Anciens, "
        "COUNT(CASE WHEN DATEEMBAUCHE BETWEEN '2022-01-01' AND '2023-12-31' THEN 1 ELSE NULL END) AS Moyens, "
        "COUNT(CASE WHEN DATEEMBAUCHE > '2023-12-31' THEN 1 ELSE NULL END) AS Recents "
        "FROM EMPLOYES"
        );
    if (query.exec() && query.next()) {
        statsDATEEMBAUCHE[0] = query.value(0).toInt();
        statsDATEEMBAUCHE[1] = query.value(1).toInt();
        statsDATEEMBAUCHE[2] = query.value(2).toInt();
    } else {
        qDebug() << "Erreur SQL pour les dates d'embauche:" << query.lastError();
    }

    // Créer les barres et séries pour afficher les données
    QBarSet *salaireSet = new QBarSet("Salaires");
    *salaireSet << statsSALAIRE[0] << statsSALAIRE[1] << statsSALAIRE[2];

    QBarSet *statutSet = new QBarSet("Statuts");
    *statutSet << statsSTATUT[0] << statsSTATUT[1] << statsSTATUT[2];

    QBarSet *dateSet = new QBarSet("Dates d'embauche");
    *dateSet << statsDATEEMBAUCHE[0] << statsDATEEMBAUCHE[1] << statsDATEEMBAUCHE[2];

    // Créer la série et le graphique
    QBarSeries *series = new QBarSeries();
    series->append(salaireSet);
    series->append(statutSet);
    series->append(dateSet);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des employés");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Catégories de l'axe X
    QStringList categories = {"Faibles", "Moyens", "Élevés"};
    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->append("Faibles", 0);
    axisX->append("Moyens", 1);
    axisX->append("Élevés", 2);

    chart->createDefaultAxes();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Ajouter le graphique au layout
    QVBoxLayout *layout = new QVBoxLayout(ui->widget_graph);
    ui->widget_graph->setLayout(layout);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);

    // Assurez-vous que le widget est suffisamment grand
    ui->widget_graph->resize(800, 600);

    chartView->repaint();
}
void acceuil::on_pushButton_graph_clicked()
{
    ui->setupUi(this);
    //connect(ui->pushButton_graph, &QPushButton::clicked, this, &acceuil::afficherStatsFidelite);
    afficherStatsEmployes();
}


void acceuil::on_pushButton_arduino_clicked()
{
    // Récupérer le code depuis l'interface utilisateur
    QString code = ui->lineEdit_2->text();
    if (code.isEmpty()) {
        ui->statusLabel->setText("Veuillez entrer un code.");
        return;
    }

    // Recherche de l'employé dans la base de données
    Employe employe;
    QSqlQueryModel *result = employe.Rechercher(code.toInt());
    if (result && result->rowCount() > 0) {
        // Extraction des informations de l'employé
        QString nom = result->record(0).value("NOM").toString();
        QString ide = result->record(0).value("IDE").toString();
        int nombreEntree = result->record(0).value("NOMBRE_DENTREE").toInt() + 1;
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE employes SET NOMBRE_DENTREE = :nombreEntree WHERE IDE = :ide");
        updateQuery.bindValue(":nombreEntree", nombreEntree);
        updateQuery.bindValue(":ide", ide);

        if (!updateQuery.exec()) {
            ui->statusLabel->setText("Erreur lors de la mise à jour de NOMBRE_DENTREE.");
            qDebug() << "Erreur SQL :" << updateQuery.lastError().text();
            return;
        }

        // Mise à jour de la base de données
        employe.setNombre(nombreEntree);
        if (!employe.modifier(code.toInt())) {
            ui->statusLabel->setText("Erreur lors de la mise à jour des données.");
            return;
        }

        // Préparation des données pour l'envoi à l'Arduino
        QString dataToSend = "Bonjour " + nom + "\nID: " + ide + "\nNb: " + QString::number(nombreEntree);
        QByteArray data = dataToSend.toUtf8();

        // Connexion à l'Arduino
        if (A.connect_arduino())
        {
            // Envoi des données
            A.write_to_arduino(data);
            qDebug() << "Données envoyées à l'Arduino :" << dataToSend;

            // Lecture de la réponse de l'Arduino
            QByteArray receivedData = A.read_from_arduino();
            if (!receivedData.isEmpty()) {
                qDebug() << "Données reçues de l'Arduino :" << receivedData;
            }

            // Mise à jour de l'interface utilisateur
            ui->statusLabel->setText("Données envoyées avec succès.");
        } else {
            // Gestion des erreurs de connexion Arduino
            ui->statusLabel->setText("Erreur : Impossible de se connecter à l'Arduino.");
            qDebug() << "Erreur de connexion avec l'Arduino.";
        }

        // Fermeture de la connexion série
        A.close_arduino();

    } else {
        // Gestion du cas où l'employé n'est pas trouvé
        ui->statusLabel->setText("Code employé introuvable.");
        qDebug() << "Aucun employé trouvé avec le code :" << code;
    }
}
void acceuil::update_label()
{
    ui->statusLabel->setText("Label mis à jour !");
}

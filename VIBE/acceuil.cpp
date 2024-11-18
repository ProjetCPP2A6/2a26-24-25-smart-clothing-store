#include "acceuil.h"
#include "ui_acceuil.h"
#include "Employes.h"
#include <QSqlError>
#include<QMessageBox>
#include <QInputDialog>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
acceuil::acceuil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acceuil)
{
    ui->setupUi(this);

    ui->tableView->setModel(emtp.afficher());
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

    Employe e(IDE , NOM, PRENOM, ADRESSE,NUMTEL, DATEN, EMAIL,DATEEMBAUCHE,DATEFIN,STATUT,NUMCB,IDS, SALAIRE);
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

    Employe e(IDE , NOM, PRENOM, ADRESSE,NUMTEL, DATEN, EMAIL,DATEEMBAUCHE,DATEFIN,STATUT,NUMCB,IDS, SALAIRE);

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

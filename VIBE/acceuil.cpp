#include "acceuil.h"
#include "ui_acceuil.h"
#include <QSqlError>
#include <QMessageBox>
#include "achats.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QPrinter>
#include<QPainter>
#include<qinputdialog.h>
#include<qfiledialog.h>
#include <QString>
#include <QLineEdit>
#include <QInputDialog>
#include <QFileDialog>
#include <QDebug>
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
acceuil::acceuil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acceuil)
{
    ui->setupUi(this);
    ui->tableView->setModel(achats.afficher());
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






void acceuil::on_ajouterachat_clicked()
{
    int REF = ui->ref->text().toInt();
    int IDE = ui->idtemploye->text().toInt();
    int IDC = ui->idtcommande->text().toInt();
    QString TAILLEPROD = ui->taille->text();
    int REFPROD = ui->refprod->text().toInt();
    QString DATEACHAT = ui->dateachat->text();
    float MONTANTACHAT = ui->montant->text().toFloat();
    QString METHODEP = ui->methdepayement->text();


    ACHATS A(TAILLEPROD , METHODEP ,DATEACHAT, REF, IDE ,IDC ,REFPROD, MONTANTACHAT);
    bool test = A.ajouter();

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }

}


void acceuil::on_supprimerachat_clicked()
{
    int REF=ui->refS->text().toInt();
    bool test=achats.supprimer(REF);
    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\n"
                                          "Click Cancel to exit."),QMessageBox::Cancel);
}



void acceuil::on_RECHERCHERachat_clicked()
{
    int REF = ui->lineEdit_rechercher->text().toInt();
    ui->tableView->setModel(achats.rechercher(REF));
}


void acceuil::on_trierachat_clicked()
{
    ACHATS achats;
    QSqlQueryModel* model = achats.trier();
    ui->tableView_TRIER->setModel(model);
}


void acceuil::on_exporterachat_clicked()
{
    // Étape 1 : Demander la ref de l'achat à exporter
    int ACHATSREF = QInputDialog::getInt(this, "Exporter un achats", "Entrez la reference de l'achat à exporter :");
    if ( ACHATSREF <= 0)
    {
        QMessageBox::warning(this, "Erreur", "ref invalide. Veuillez réessayer.");
        return;
    }


    ACHATS a;
    a.setREF(ACHATSREF);


    if (!a.exporter())
    {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données de l'achats. Vérifiez la reference.");
        return;
    }


    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer sous", QString("Achats_%1.pdf").arg(ACHATSREF), "Fichiers PDF (*.pdf)");
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


    painter.setFont(QFont("Arial", 12));
    painter.drawText(100, 100, QString("Fiche de l'employé : %1").arg(ACHATSREF));
    painter.drawText(100, 200, QString("DATEACHAT : %1").arg(a.getDATEACHAT()));
    painter.drawText(100, 300, QString("IDC : %1").arg(a.getIDC()));
    painter.drawText(100, 400, QString("IDE : %1").arg(a.getIDE()));
    painter.drawText(100, 500, QString(" METHODEP : %1").arg(a.getMETHODEP()));
    painter.drawText(100, 600, QString("REF: %1").arg(a.getREF()));
    painter.drawText(100, 700, QString("REFPROD : %1").arg(a.getREFPROD()));
    painter.drawText(100, 800, QString("TAILLEPROD : %1").arg(a.getTAILLEPROD()));


    painter.end();

    // Étape 6 : Confirmation
    QMessageBox::information(this, "Succès", "Le fichier PDF a été exporté avec succès !");
}

/*void acceuil::on_premierdemarque_clicked()
{
    // Récupérer la référence de l'achat à partir de la ligne sélectionnée dans la QTableView
    QModelIndexList selectedIndexes = ui->tableView_TRIER->selectionModel()->selectedRows();

    if (selectedIndexes.isEmpty()) {
        qDebug() << "Aucune ligne sélectionnée.";
        return;  // Ne pas appliquer la démarque si aucune ligne n'est sélectionnée
    }

    // Récupérer la référence de l'achat (par exemple, la première colonne contient la référence de l'achat)
    int selectedRefAchat = selectedIndexes.first().data().toInt();  // Récupère la valeur de la première colonne (REFACHAT)

    // Créer l'objet ACHATS et appliquer la 1ère démarque sur l'achat sélectionné
    ACHATS achats;
    achats.appliquerDémarque("1ère", selectedRefAchat);  // Passer la référence de l'achat à la méthode

    // Rafraîchir la tableview pour afficher les nouveaux montants après la mise à jour
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT DATEACHAT, IDC, IDE, METHODEP, MONTANTACHAT, CAST(REF as varchar(20)) AS REF, REFPROD, TAILLEPROD FROM achats");
    ui->tableView_TRIER->setModel(model);  // Mettre à jour la tableview avec les nouveaux montants
}


void acceuil::on_dexiemedemarque_clicked()
{
    // Récupérer la référence de l'achat à partir de la ligne sélectionnée dans la QTableView
    QModelIndexList selectedIndexes = ui->tableView_TRIER->selectionModel()->selectedRows();

    if (selectedIndexes.isEmpty()) {
        qDebug() << "Aucune ligne sélectionnée.";
        return;  // Ne pas appliquer la démarque si aucune ligne n'est sélectionnée
    }

    // Récupérer la référence de l'achat (par exemple, la première colonne contient la référence de l'achat)
    int selectedRefAchat = selectedIndexes.first().data().toInt();  // Récupère la valeur de la première colonne (REFACHAT)

    // Créer l'objet ACHATS et appliquer la 2ème démarque sur l'achat sélectionné
    ACHATS achats;
    achats.appliquerDémarque("2ème", selectedRefAchat);  // Passer la référence de l'achat à la méthode

    // Rafraîchir la tableview pour afficher les nouveaux montants après la mise à jour
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT DATEACHAT, IDC, IDE, METHODEP, MONTANTACHAT, CAST(REF as varchar(20)) AS REF, REFPROD, TAILLEPROD FROM achats");
    ui->tableView_TRIER->setModel(model);  // Mettre à jour la tableview avec les nouveaux montants
}


void acceuil::on_troisiemedemarque_clicked()
{

    QModelIndexList selectedIndexes = ui->tableView_TRIER->selectionModel()->selectedRows();

    if (selectedIndexes.isEmpty()) {
        qDebug() << "Aucune ligne sélectionnée.";
        return;  // Ne pas appliquer la démarque si aucune ligne n'est sélectionnée
    }

    // Récupérer la référence de l'achat (par exemple, la première colonne contient la référence de l'achat)
    int selectedRefAchat = selectedIndexes.first().data().toInt();  // Récupère la valeur de la première colonne (REFACHAT)

    // Créer l'objet ACHATS et appliquer la 3ème démarque sur l'achat sélectionné
    ACHATS achats;
    achats.appliquerDémarque("3ème", selectedRefAchat);  // Passer la référence de l'achat à la méthode

    // Rafraîchir la tableview pour afficher les nouveaux montants après la mise à jour
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT DATEACHAT, IDC, IDE, METHODEP, MONTANTACHAT, CAST(REF as varchar(20)) AS REF, REFPROD, TAILLEPROD FROM achats");
    ui->tableView_TRIER->setModel(model);  // Mettre à jour la tableview avec les nouveaux montants
}


void acceuil::on_RECHERCHER_promo_clicked()
{
    int REF = ui->promo->text().toInt();
    ui->tableView_promo->setModel(achats.rechercher(REF));

}
*/

void acceuil::on_premierdemarque_clicked()
{
    int REF =ui->promo->text().toInt();

    QSqlQuery query;
    query.prepare("SELECT MONTANTACHAT FROM ACHATS WHERE REF=:REF");
    query.bindValue(":REF",REF);
    if(!query.exec())
    {
        QMessageBox::warning(nullptr,"PROMOTION","REFERENCE INTROUVABLE");
    }
    else
    {
        if(query.next())
        {
            QString MONTANTACHAT=query.value("MONTANTACHAT").toString();
            float MONTANTACHAT1=query.value("MONTANTACHAT").toFloat();
            ui->montantachat_promo1->setText(MONTANTACHAT);
            MONTANTACHAT1=(MONTANTACHAT1*80)/100;
            ui->montantachat_promo2->setText(QString::number(MONTANTACHAT1));
        }
    }
}


void acceuil::on_dexiemedemarque_clicked()
{
    int REF =ui->promo->text().toInt();

    QSqlQuery query;
    query.prepare("SELECT MONTANTACHAT FROM ACHATS WHERE REF=:REF");
    query.bindValue(":REF",REF);
    if(!query.exec())
    {
        QMessageBox::warning(nullptr,"PROMOTION","REFERENCE INTROUVABLE");
    }
    else
    {
        if(query.next())
        {
            QString MONTANTACHAT=query.value("MONTANTACHAT").toString();
            float MONTANTACHAT1=query.value("MONTANTACHAT").toFloat();
            ui->montantachat_promo1->setText(MONTANTACHAT);
            MONTANTACHAT1=(MONTANTACHAT1*70)/100;
            ui->montantachat_promo2->setText(QString::number(MONTANTACHAT1));
        }
    }
}


void acceuil::on_troisiemedemarque_clicked()
{
    int REF =ui->promo->text().toInt();

    QSqlQuery query;
    query.prepare("SELECT MONTANTACHAT FROM ACHATS WHERE REF=:REF");
    query.bindValue(":REF",REF);
    if(!query.exec())
    {
        QMessageBox::warning(nullptr,"PROMOTION","REFERENCE INTROUVABLE");
    }
    else
    {
        if(query.next())
        {
            QString MONTANTACHAT=query.value("MONTANTACHAT").toString();
            float MONTANTACHAT1=query.value("MONTANTACHAT").toFloat();
            ui->montantachat_promo1->setText(MONTANTACHAT);
            MONTANTACHAT1=(MONTANTACHAT1*50)/100;
            ui->montantachat_promo2->setText(QString::number(MONTANTACHAT1));
        }
    }
}
void acceuil::afficherStatsRefProd()
{
    // Étape 1 : Récupération des données depuis la base de données
    QVector<int> stats(3, 0); // Catégorie 1, Catégorie 2, Catégorie 3 (modifiez les catégories selon vos besoins)

    QSqlQuery query;
    query.prepare(
        "SELECT "
        "SUM(CASE WHEN REFPROD BETWEEN 1 AND 100 THEN 1 ELSE 0 END) AS Categorie1, "
        "SUM(CASE WHEN REFPROD BETWEEN 101 AND 200 THEN 1 ELSE 0 END) AS Categorie2, "
        "SUM(CASE WHEN REFPROD > 200 THEN 1 ELSE 0 END) AS Categorie3 "
        "FROM Achats"); // Remplacez "Produits" par le nom de votre table

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données : " + query.lastError().text());
        return;
    }

    if (query.next())
    {
        stats[0] = query.value(0).toInt(); // Catégorie 1
        stats[1] = query.value(1).toInt(); // Catégorie 2
        stats[2] = query.value(2).toInt(); // Catégorie 3
    }
    else
    {
        QMessageBox::information(this, "Aucune donnée", "La table Produits est vide ou ne contient pas les références spécifiées.");
        return;
    }

    // Étape 2 : Création du graphique avec QChart
    QBarSet *set = new QBarSet("Nombre de produits");
    *set << stats[0] << stats[1] << stats[2]; // Ajout des données

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des produits par référence");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories = {"Catégorie 1", "Catégorie 2", "Catégorie 3"};
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
}

void acceuil::on_statachat_clicked()
{
    afficherStatsRefProd();

}


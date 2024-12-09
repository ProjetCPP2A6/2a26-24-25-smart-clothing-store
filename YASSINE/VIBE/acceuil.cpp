#include "acceuil.h"
#include "livraisons.h"
#include "ui_acceuil.h"
#include "qlineedit.h"
#include"qdatetime.h"
#include"qcombobox.h"
#include"qdatetimeedit.h"
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QInputDialog>
#include<QFileDialog>
#include <QPrinter>
#include<QPainter>
#include<QMessageBox>
#include <QVector>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QCategoryAxis>

void acceuil::extraire_derRef()
{
    //référence de livraison aléatoire
    long refl=1111111111;
    QSqlQuery query;
    query.prepare("SELECT REFL FROM LIVRAISONS ORDER BY REFL DESC");
    if (query.exec())
    {
        if(query.next())
            refl = (query.value("REFL")).toInt();
    }
    else
        qDebug()<<"extraction impossible";
    refl+=1;
    ui->l_refl_a->setText(QString::number(refl));
}

int acceuil::extraire_nb_livre()
{
    QSqlQuery query;
    int rowcount =0;
    query.prepare("SELECT COUNT(*) FROM LIVRAISONS WHERE ETAT='ARRIVEE'");
    if (!query.exec())
    {
        QMessageBox::warning(nullptr,"LIVRAISONS","EXTRACTION IMPOSSIBLE");
    }
    else
    {
        if(query.next())
        {
            rowcount = query.value(0).toInt();
            //ui->lcdNumber->display(rowcount);
        }
    }
    return rowcount;
}



int acceuil::extraire_nb_en_traitement()
{
    QSqlQuery query;
    int rowcount=0;
    query.prepare("SELECT COUNT(*) FROM LIVRAISONS WHERE ETAT='EN TRAITEMENT' OR ETAT='EN COURS'");
    if (!query.exec())
    {
        QMessageBox::warning(nullptr,"LIVRAISONS","EXTRACTION IMPOSSIBLE");
    }
    else
    {
        if(query.next())
        {
            rowcount = query.value(0).toInt();
            //ui->lcdNumber_2->display(rowcount);
        }
    }
    return rowcount;
}

int acceuil::extraire_nb_retour()
{
    QSqlQuery query;
    int rowcount =0;
    query.prepare("SELECT COUNT(*) FROM LIVRAISONSB");
    if (!query.exec())
    {
        QMessageBox::warning(nullptr,"LIVRAISONS","EXTRACTION IMPOSSIBLE");
    }
    else
    {
        if(query.next())
        {
            rowcount = query.value(0).toInt();
            //ui->lcdNumber_3->display(rowcount);
        }
    }
    return rowcount;
}

void acceuil::afficher_livreur()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT CAST(IDE AS VARCHAR(20)) AS IDE,NOM,PRENOM,CAST(NUMTEL AS VARCHAR(20)) AS NUMTEL FROM EMPLOYES");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMTEL"));

    ui->consulter_livreur->setModel(model);
}

void acceuil::stats()
{
    QVector<int>stats(3,0);

    stats[0] = extraire_nb_livre();
    stats[1] = extraire_nb_en_traitement();
    stats[2] = extraire_nb_retour();

    QBarSet *set = new QBarSet("Livraisons");
    *set << stats[0] << stats[1] << stats[2];


    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des livraisons");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories = {"commandes livrées", "commandes en traitement", "retour de commandes"};
    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->append(categories[0], 0);
    axisX->append(categories[1], 1);
    axisX->append(categories[2], 2);

    chart->createDefaultAxes();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chart->legend()->setVisible(false);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (ui->graphicsView->layout() != nullptr) {
        QLayoutItem *item;
        while ((item = ui->graphicsView->layout()->takeAt(0)) != nullptr) {
            delete item->widget(); // Supprime le widget du layout
            delete item;           // Supprime l'item lui-même
        }
    } else {
        QVBoxLayout *layout = new QVBoxLayout(ui->graphicsView);
        ui->graphicsView->setLayout(layout);
    }

    ui->graphicsView->layout()->addWidget(chartView);
}

void acceuil::init_livraions()
{
    extraire_derRef();

    ui->tabWidget_2->setTabVisible(5,false);

    //mettre tout les QDate dans la date du pc
    ui->l_dateCommande_a->setDate(QDate::currentDate());
    ui->l_dateCommande_s_2->setDate(QDate::currentDate());
    ui->l_dateCommande_m->setDate(QDate::currentDate());
    ui->l_dateCommande_r->setDate(QDate::currentDate());
    ui->tabWidget_2->setCurrentIndex(0);

    //ouverture dans la page bienvenue
    ui->stackedWidget->setCurrentIndex(6);
    ui->l_nomutilisateur->setText("Test");
}

void acceuil::rafraichir()
{
    extraire_derRef();
    ui->consulter_l->setModel(ltmp.afficher());
    ui->l_refl_m->setModel(ltmp.afficher());
    ui->l_refl_r->setModel(ltmp.afficher());
    ui->consulter_l_2->setModel(ltmp.afficherb());
    int rowcount1=extraire_nb_livre();
    ui->lcdNumber->setText(QString::number(rowcount1));
    int rowcount2=extraire_nb_en_traitement();
    ui->lcdNumber_2->setText(QString::number(rowcount2));
    int rowcount3=extraire_nb_retour();
    ui->lcdNumber_3->setText(QString::number(rowcount3));
    afficher_livreur();
    stats();
}

acceuil::acceuil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acceuil)
{
    resize(1000, 700);
    ui->setupUi(this);

    arduinoLink = new ArduinoDatabaseLink(this);

    init_livraions();

    rafraichir();
}

acceuil::~acceuil()
{
    delete ui;
}

void acceuil::on_b_produits_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void acceuil::on_b_achats_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void acceuil::on_b_clients_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void acceuil::on_b_employes_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void acceuil::on_b_boutiques_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void acceuil::on_b_livraisons_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void acceuil::extraire_client (QLineEdit* numc , QLineEdit* nom , QLineEdit* prenom , QLineEdit* adresse)
{
    long IDC = numc->text().toLong();
    QString NOM,PRENOM,ADRESSE;
    QSqlQuery query;

    query.prepare("SELECT NOM,PRENOM,ADRESSE FROM CLIENTS WHERE IDC = :IDC");
    query.bindValue(":IDC",QString::number(IDC));

    if (query.exec())
    {
        if (query.next())
        {
            NOM=query.value("NOM").toString();
            PRENOM=query.value("PRENOM").toString();
            ADRESSE=query.value("ADRESSE").toString();

            nom->setText(NOM);
            prenom->setText(PRENOM);
            adresse->setText(ADRESSE);
        }
        else
        {
            QMessageBox::warning(nullptr,"CLIENT","CLIENT INTROUVABLE");
        }
    }

}

void acceuil::extraire_produit(QLineEdit* refprod , QLineEdit* nomprod , QComboBox* tailleprod ,QLineEdit* couleur ,  QLineEdit* montant)
{
    long REFPROD = refprod->text().toLong();
    QString NOMPROD;
    QSqlQuery query;

    query.prepare("SELECT NOMP , TAILLEP , COULEUR , PRIX FROM PRODUITS WHERE REFPROD = :REFPROD");
    query.bindValue(":REFPROD",QString::number(REFPROD));

    if (query.exec())
    {
        if (query.next())
        {
            NOMPROD=query.value("NOMP").toString();

            nomprod->setText(NOMPROD);
            tailleprod->setCurrentText(query.value("TAILLEP").toString());
            couleur->setText(query.value("COULEUR").toString());
            montant->setText(query.value("PRIX").toString());
        }
        else
        {
            QMessageBox::warning(nullptr,"PRODUIT","PRODUIT INTROUVABLE");
        }
    }

}

void acceuil::extraire_livreur(QLineEdit* num , QLineEdit* nom)
{
    long IDE = num->text().toLong();
    QString NOM;
    QSqlQuery query;

    query.prepare("SELECT NOM FROM EMPLOYES WHERE IDE = :IDE");
    query.bindValue(":IDE",QString::number(IDE));

    if (query.exec())
    {
        if (query.next())
        {
            NOM=query.value("NOM").toString();

            nom->setText(NOM);
        }
        else
        {
            QMessageBox::warning(nullptr,"LIVREUR","LIVREUR INTROUVABLE");
        }
    }

}

void acceuil::rechercher(QComboBox* num,QLineEdit* numc,QLineEdit* nom,QLineEdit* prenom,QLineEdit* adresse,QLineEdit* refprod,QLineEdit* nomprod,QComboBox* taillep,QLineEdit* couleurp  , QLineEdit* montantc , QComboBox* methodep ,QDateEdit* datec, QLineEdit* nume,QLineEdit* nome)
{
    long REFL = num->currentText().toLong();
    QSqlQuery query;
    query.prepare("SELECT * FROM LIVRAISONS WHERE REFL =:REFL");
    query.bindValue(":REFL",QString::number(REFL));

    if(query.exec())
    {
        if(query.next())
        {
            QString IDC = query.value("IDC").toString();
            QString REFPROD = query.value("REFPROD").toString();
            QString METHODEP = query.value("METHODEP").toString();
            QDate DATECOMMANDE = query.value("DATECOMMANDE").toDate();
            QString IDE = query.value("IDE").toString();



            numc->setText(IDC);
            extraire_client(numc,nom,prenom,adresse);
            refprod->setText(REFPROD);
            extraire_produit(refprod,nomprod,taillep,couleurp,montantc);
            methodep->setCurrentText(METHODEP);
            datec->setDate(DATECOMMANDE);
            nume->setText(IDE);
            extraire_livreur(nume,nome);
        }
        else
        {
            QMessageBox::warning(nullptr,"COMMANDE","COMMANDE INTROUVABLE");
        }
    }
}

void acceuil::rechercherb(QLineEdit* num,QLineEdit* numc,QLineEdit* nom,QLineEdit* prenom,QLineEdit* adresse,QLineEdit* refprod,QLineEdit* nomprod,QComboBox* taillep,QLineEdit* couleurp  , QLineEdit* montantc , QComboBox* methodep ,QDateEdit* datec, QLineEdit* nume,QLineEdit* nome)
{
    long REFL = num->text().toLong();
    QSqlQuery query;
    query.prepare("SELECT * FROM LIVRAISONSB WHERE REFL =:REFL");
    query.bindValue(":REFL",QString::number(REFL));

    if(query.exec())
    {
        if(query.next())
        {
            QString IDC = query.value("IDC").toString();
            QString REFPROD = query.value("REFPROD").toString();
            QString METHODEP = query.value("METHODEP").toString();
            QDate DATECOMMANDE = query.value("DATECOMMANDE").toDate();
            QString IDE = query.value("IDE").toString();



            numc->setText(IDC);
            extraire_client(numc,nom,prenom,adresse);
            refprod->setText(REFPROD);
            extraire_produit(refprod,nomprod,taillep,couleurp,montantc);
            methodep->setCurrentText(METHODEP);
            datec->setDate(DATECOMMANDE);
            nume->setText(IDE);
            extraire_livreur(nume,nome);
        }
        else
        {
            QMessageBox::warning(nullptr,"COMMANDE","COMMANDE INTROUVABLE");
        }
    }
}

void acceuil::nettoyer(QLineEdit* numc, QLineEdit* nomc, QLineEdit* prenomc, QLineEdit* adressec, QLineEdit* refp, QLineEdit* nomp, QLineEdit* couleurp,QLineEdit* montanta, QLineEdit* numl, QLineEdit* noml)
{
    numc->setText("");
    nomc->setText("");
    prenomc->setText("");
    adressec->setText("");
    refp->setText("");
    nomp->setText("");
    couleurp->setText("");
    montanta->setText("");
    numl->setText("");
    noml->setText("");

}

void acceuil::on_b_ajouterl_clicked()
{
    long refl = ui->l_refl_a->text().toLong();
    long idc = ui->l_idcl_a->text().toLong();
    long ide = ui->l_idel_a->text().toLong();
    long refprod= ui->l_refArticlel_a->text().toLong();
    QString tailleprod = ui->l_tailleArticlel_a->currentText();
    QString couleurprod = ui->l_couleurArticlel_a->text();
    QString methodep = ui->l_methodePaiement_a->currentText();
    QString etat = "EN TRAITEMENT";
    QDate datecommande = ui->l_dateCommande_a->date();
    float montantcommande = ui->l_montantAchatsl_a->text().toFloat();

    livraisons l(refl,ide,idc,refprod,tailleprod,methodep,etat,couleurprod,datecommande,montantcommande);

    bool test_a = l.ajouter();
    if(test_a)
    {
        ui->consulter_l->setModel(ltmp.afficher());
        ui->l_refl_m->setModel(ltmp.afficher());
        QMessageBox::information(nullptr,"AJOUT","succès!");
        extraire_derRef();
        nettoyer(ui->l_idcl_a,ui->l_nomClientl_a,ui->l_prenomClientl_a,ui->l_adresseClientl_a,ui->l_refArticlel_a,ui->l_nomArticlel_a,ui->l_couleurArticlel_a,ui->l_montantAchatsl_a,ui->l_idel_a,ui->l_nomLivreurl_a);

    }
    else
    {
        QMessageBox::warning(nullptr,"AJOUT","ERREUR");
    }
}


void acceuil::on_l_idcl_a_returnPressed()
{
    extraire_client(ui->l_idcl_a,ui->l_nomClientl_a,ui->l_prenomClientl_a,ui->l_adresseClientl_a);
}


void acceuil::on_l_refArticlel_a_returnPressed()
{
    extraire_produit(ui->l_refArticlel_a,ui->l_nomArticlel_a,ui->l_tailleArticlel_a,ui->l_couleurArticlel_a,ui->l_montantAchatsl_a);
}


void acceuil::on_l_idel_a_returnPressed()
{
    extraire_livreur(ui->l_idel_a,ui->l_nomLivreurl_a);
}


void acceuil::on_b_supprimer_clicked()
{
    QModelIndex index = ui->consulter_l->currentIndex();  // Récupère l'indice de la cellule sélectionnée
    long val = ui->consulter_l->model()->data(ui->consulter_l->model()->index(index.row(), 0)).toLongLong();  // Récupère la valeur de la première colonne (colonne 0) de la ligne sélectionnée
    bool test_s = ltmp.supprimer(val);
    if(test_s)
    {
        rafraichir();
        QMessageBox::information(nullptr,"SUPPRESSION","succès!");
    }
    else
    {
        QMessageBox::warning(nullptr,"SUPPRESSION","ERREUR");
    }
}



void acceuil::on_b_modifier_clicked()
{
    long refl = ui->l_refl_m->currentText().toLong();
    long idc = ui->l_idcl_m->text().toLong();
    long ide = ui->l_idel_m->text().toLong();
    long refprod= ui->l_refArticlel_m->text().toLong();
    QString tailleprod = ui->l_tailleArticlel_m->currentText();
    QString couleurprod = ui->l_couleurArticlel_m->text();
    QString methodep = ui->l_methodePaiement_m->currentText();
    QString etat = "EN TRAITEMENT";
    QDate datecommande = ui->l_dateCommande_m->date();
    float montantcommande = ui->l_montantAchatsl_m->text().toFloat();

    livraisons l(refl,ide,idc,refprod,tailleprod,methodep,etat,couleurprod,datecommande,montantcommande);

    bool test_m = l.modifier(refl);

    if(test_m)
    {
        rafraichir();
        QMessageBox::information(nullptr,"MODIFICATION","succès!");
        nettoyer(ui->l_idcl_m,ui->l_nomClientl_m,ui->l_prenomClientl_m,ui->l_adresseClientl_m,ui->l_refArticlel_m,ui->l_nomArticlel_m,ui->l_couleurArticlel_m,ui->l_montantAchatsl_m,ui->l_idel_m,ui->l_nomLivreurl_m);

    }
    else
    {
        QMessageBox::warning(nullptr,"MODIFICATION","ERREUR");
    }
}

void acceuil::on_b_rechercher_s_3_clicked()
{
    rechercher(ui->l_refl_m,ui->l_idcl_m,ui->l_nomClientl_m,ui->l_prenomClientl_m,ui->l_adresseClientl_m,ui->l_refArticlel_m,ui->l_nomArticlel_m,ui->l_tailleArticlel_m,ui->l_couleurArticlel_m,ui->l_montantAchatsl_m,ui->l_methodePaiement_m,ui->l_dateCommande_m,ui->l_idel_m,ui->l_nomLivreurl_m);
}


void acceuil::on_b_rech_refl_clicked()
{
    long REFL = ui->l_refl_r->currentText().toInt();
    ui->consulter_l->setModel(ltmp.recherche_aff_refl(REFL));
}

void acceuil::on_l_refl_r_activated()
{
    on_b_rech_refl_clicked();
}


void acceuil::on_b_rech_idc_clicked()
{
    long IDC = ui->l_idcl_r->text().toLong();
    ui->consulter_l->setModel(ltmp.recherche_aff_IDC(IDC));
}

void acceuil::on_l_idcl_r_returnPressed()
{
    on_b_rech_idc_clicked();
}

void acceuil::on_b_rech_date_clicked()
{
    QDate DATECOMMANDE = ui->l_dateCommande_r->date();
    ui->consulter_l->setModel(ltmp.recherche_aff_DATECOMMANDE(DATECOMMANDE));
}


void acceuil::on_l_dateCommande_r_editingFinished()
{
    on_b_rech_date_clicked();
}


void acceuil::on_b_tri_clicked()
{
    ui->consulter_l->setModel(ltmp.trier());
}


void acceuil::on_b_exporter_clicked()
{
    QModelIndex index = ui->consulter_l->currentIndex();  // Récupère l'indice de la cellule sélectionnée
    long REFL = ui->consulter_l->model()->data(ui->consulter_l->model()->index(index.row(), 0)).toLongLong();

    QSqlQuery query;
    query.prepare("SELECT REFL FROM LIVRAISONS WHERE REFL=:REFL");
    query.bindValue(":REFL",QString::number(REFL));
    if(!query.exec())
    {
        QMessageBox::warning(nullptr,"EXPORTATION","REFERENCE INTROUVABLE");
    }

    ltmp.setREFL(REFL);

    if(!ltmp.exporter())
    {
        QMessageBox::warning(nullptr,"EXPORTATION","ECHEC EXPORTATION");
        return;
    }

    QString filepath= QFileDialog::getSaveFileName(this,"Enregistrer Sous",QString("Livraison_%1.pdf").arg(REFL),"Fichiers PDF (*.pdf)");
    if (filepath.isEmpty())
    {
        QMessageBox::warning(nullptr,"EXPORTATION","ECHEC EXPORTATION");
        return;
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filepath);

    QPainter painter (&printer);
    if (!painter.isActive())
    {
        QMessageBox::warning(nullptr,"EXPORTATION","ECHEC EXPORTATION");
        return;
    }

    painter.setFont(QFont("Arial",12));
    painter.drawText (50,50, QString("Fiche de l'employé : %1").arg(REFL));
    painter.drawText (50,70, QString("numéro du client : %1").arg(ltmp.getIDE()));
    painter.drawText (50,90, QString("id employé : %1").arg(ltmp.getIDE()));
    painter.drawText (50,110, QString("référence produit : %1").arg(ltmp.getREFPROD()));
    painter.drawText (50,130, QString("taille du produit : %1").arg(ltmp.getTAILLEPROD()));
    painter.drawText (50,150, QString("couleur du produit : %1").arg(ltmp.getCOULEURPROD()));
    painter.drawText (50,170, QString("montant de la commande : %1").arg(ltmp.getMONTANTCOMMANDE()));
    painter.drawText (50,190, QString("méthode de paiement de la commande : %1").arg(ltmp.getMETHODEP()));
    painter.drawText (50,210, QString("date de la commande : %1").arg(ltmp.getDATECOMMANDE().toString("dd/MM/yyyy")));
    painter.drawText (50,230, QString("date d'arrivée : %1").arg(ltmp.getDATEARRIVEE().toString("dd/MM/yyyy")));
    painter.drawText (50,250, QString("état de la commande : %1").arg(ltmp.getETAT()));

    painter.end();

    QMessageBox::information(nullptr,"EXPORTATION","succès !");
}


void acceuil::on_b_rechercher_s_2_clicked()
{
    rechercherb(ui->l_refl_s_2,ui->l_idcl_s_2,ui->l_nomClientl_s_2,ui->l_prenomClientl_s_2,ui->l_adresseClientl_s_2,ui->l_refArticlel_s_2,ui->l_nomArticlel_s_2,ui->l_tailleArticlel_s_2,ui->l_couleurArticlel_s_2,ui->l_montantAchatsl_s_2,ui->l_methodePaiement_s_2,ui->l_dateCommande_s_2,ui->l_idel_s_2,ui->l_nomLivreurl_s_2);
}


void acceuil::on_b_supprimer_2_clicked()
{
    long REFL = ui->l_refl_s_2->text().toLong();

    bool test_s = ltmp.supprimerb(REFL);
    if(test_s)
    {
        rafraichir();
        QMessageBox::information(nullptr,"SUPPRESSION BACKUP","succès!");
        nettoyer(ui->l_idcl_s_2,ui->l_nomClientl_s_2,ui->l_prenomClientl_s_2,ui->l_adresseClientl_s_2,ui->l_refArticlel_s_2,ui->l_nomArticlel_s_2,ui->l_couleurArticlel_s_2,ui->l_montantAchatsl_s_2,ui->l_idel_s_2,ui->l_nomLivreurl_s_2);
    }
    else
    {
        QMessageBox::warning(nullptr,"SUPPRESSION BACKUP","ERREUR");
    }
}


void acceuil::on_b_restaurer_clicked()
{
    long refl = ui->l_refl_s_2->text().toLong();
    long idc = ui->l_idcl_s_2->text().toLong();
    long ide = ui->l_idel_s_2->text().toLong();
    long refprod= ui->l_refArticlel_s_2->text().toLong();
    QString tailleprod = ui->l_tailleArticlel_s_2->currentText();
    QString couleurprod = ui->l_couleurArticlel_s_2->text();
    QString methodep = ui->l_methodePaiement_s_2->currentText();
    QString etat = "EN TRAITEMENT";
    QDate datecommande = ui->l_dateCommande_s_2->date();
    float montantcommande = ui->l_montantAchatsl_s_2->text().toFloat();

    livraisons l(refl,ide,idc,refprod,tailleprod,methodep,etat,couleurprod,datecommande,montantcommande);

    bool test_a = l.ajouter();
    if(test_a)
    {
        on_b_supprimer_2_clicked();
        rafraichir();
        QMessageBox::information(nullptr,"AJOUT BACKUP","succès!");
        extraire_derRef();
        nettoyer(ui->l_idcl_s_2,ui->l_nomClientl_s_2,ui->l_prenomClientl_s_2,ui->l_adresseClientl_s_2,ui->l_refArticlel_s_2,ui->l_nomArticlel_s_2,ui->l_couleurArticlel_s_2,ui->l_montantAchatsl_s_2,ui->l_idel_s_2,ui->l_nomLivreurl_s_2);
    }
    else
    {
        QMessageBox::warning(nullptr,"AJOUT BACKUP","ERREUR");
    }

}


void acceuil::on_consulter_l_clicked(const QModelIndex &index)
{
    long val = ui->consulter_l->model()->data(index.sibling(index.row(),0)).toLongLong();  // On utilise `sibling` pour prendre la valeur de la 1ère colonne
    QSqlQuery query , qry;
    query.prepare("SELECT IDC FROM LIVRAISONS WHERE REFL = :val");
    query.bindValue(":val",QString::number(val));
    if (!query.exec())
    {
        QMessageBox::warning(nullptr,"RECHERCHE CLIENT 1","ERREUR 1");
    }
    else
    {
        if (query.next())
        {
            long IDC = query.value("IDC").toLongLong();

            qry.prepare("SELECT * FROM CLIENTS WHERE IDC =:IDC");
            qry.bindValue(":IDC",QString::number(IDC));
            if(qry.exec())
            {
                if(qry.next())
                {
                    ui->l_numc_consulter->setText(qry.value("IDC").toString());
                    ui->l_nomc_consulter->setText(qry.value("NOM").toString());
                    ui->l_prenomc_consulter->setText(qry.value("PRENOM").toString());
                    ui->l_adrc_consulter->setText(qry.value("ADRESSE").toString());
                }
                else
                {
                    QMessageBox::warning(nullptr,"RECHERCHE CLIENT 2","ERREUR 2");
                }
            }
        }
    }
}


void acceuil::on_consulter_l_2_clicked(const QModelIndex &index)
{
    long val = ui->consulter_l_2->model()->data(index.sibling(index.row(),0)).toLongLong();
    ui->l_refl_s_2->setText(QString::number(val));
}


void acceuil::on_consulter_l_doubleClicked(const QModelIndex &index)
{
    long val = ui->consulter_l->model()->data(index.sibling(index.row(),0)).toLongLong();  // On utilise `sibling` pour prendre la valeur de la 1ère colonne
    ui->tabWidget_2->setCurrentIndex(5);

    QSqlQuery query,qry,qry2;

    query.prepare("SELECT IDC, IDE, DATECOMMANDE, MONTANTCOMMANDE,ETAT FROM LIVRAISONS WHERE REFL =:REFL");
    query.bindValue(":REFL",QString::number(val));
    if(query.exec() && query.next())
    {
        QString IDC = query.value("IDC").toString();
        QString IDE = query.value("IDE").toString();
        QString DATECOMMANDE = query.value("DATECOMMANDE").toDate().toString("dd/MM/yyyy");
        QString MONTANTCOMMANDE =query.value("MONTANTCOMMANDE").toString();
        QString ETAT = query.value("ETAT").toString();

        ui->l_refl_t->setText(QString::number(val));
        ui->l_datecommande_t->setText(DATECOMMANDE);
        ui->l_montantc_t->setText(MONTANTCOMMANDE);

        qry.prepare("SELECT * FROM CLIENTS WHERE IDC =:IDC");
        qry.bindValue(":IDC",IDC);
        if(qry.exec())
        {
            if(qry.next())
            {
                ui->l_idc_t->setText(IDC);
                ui->l_nomc_t->setText(qry.value("NOM").toString());
                ui->l_prenomc_t->setText(qry.value("PRENOM").toString());
                ui->l_adrc_t->setText(qry.value("ADRESSE").toString());
            }
            else
            {
                QMessageBox::warning(nullptr,"RECHERCHE CLIENT 2","ERREUR 2");
            }
        }
        qry2.prepare("SELECT * FROM EMPLOYES WHERE IDE =:IDE");
        qry.bindValue(":IDE",IDE);
        if(qry.exec())
        {
            if(qry.next())
            {
                ui->l_ide_t->setText(IDE);
                ui->l_nome_t->setText(qry.value("NOM").toString());
                ui->l_prenome_t->setText(qry.value("PRENOM").toString());
            }
            else
            {
                QMessageBox::warning(nullptr,"RECHERCHE CLIENT 2","ERREUR 2");
            }
        }
        if((ETAT=="EN TRAITEMENT"))
        {
            ui->checkBox_trait->setEnabled(true);

            ui->checkBox_trait->setChecked(true);
        }
        else if (ETAT == "EN COURS")
        {
            ui->checkBox_trait->setEnabled(true);
            ui->checkBox_cours->setEnabled(true);

            ui->checkBox_trait->setChecked(true);
            ui->checkBox_cours->setChecked(true);
        }
        else
        {
            ui->checkBox_trait->setEnabled(true);
            ui->checkBox_cours->setEnabled(true);
            ui->checkBox_arr->setEnabled(true);

            ui->checkBox_trait->setChecked(true);
            ui->checkBox_cours->setChecked(true);
            ui->checkBox_arr->setChecked(true);
        }
    }
}





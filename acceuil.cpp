#include "acceuil.h"
#include "ui_acceuil.h"
#include <QMessageBox>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include <QRegularExpression>
#include <QPrinter>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QSqlError>
#include <QSqlQuery>
#include <QtCharts>
#include <QChartView>
QString ref1,ref2;

acceuil::acceuil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acceuil)
{
    ui->setupUi(this);

    int ret = A.connect_arduino();  // Connexion à Arduino
    switch(ret) {
    case(0):
        qDebug() << "Arduino is available and connected to : " << A.getarduino_port_name();
        break;
    case(1):
        qDebug() << "Arduino is available but not connected to :" << A.getarduino_port_name();
        break;
    case(-1):
        qDebug() << "Arduino is not available";
        break;
    }

    QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(input()));  // Connexion signal/slot

    ui->tableView->setModel(btq.afficher());

    ui->nommodifier->setVisible(false);
    ui->adrmodifier->setVisible(false);
    ui->nummodifier->setVisible(false);
    ui->nom1->setVisible(false);
    ui->adr2->setVisible(false);
    ui->num3->setVisible(false);

    this->listeBoutiques = btq.recupererBoutique();
    ui->boutiques->addItems(btq.recupererBoutiqueNom(this->listeBoutiques));

    /*//init date
    ui->dateDebut->setDate(QDate::currentDate());
    ui->dateFin->setDate(QDate::currentDate());*/

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

void acceuil::on_ajouter_clicked()
{

    QString id_str = ui->lineEdit_id->text();
    int id = id_str.toInt();
    QString nom = ui->lineEdit_nom->text();
    QString adr = ui->lineEdit_adr->text();
    QString num_str = ui->lineEdit_num->text();

    // Contrôle de saisie pour l'ID
    if (id_str.length() > 10) {
        QMessageBox::warning(this, "Erreur de saisie", "L'ID ne doit pas dépasser 10 chiffres.");
        return;
    }

    // Contrôle de saisie pour le nom (ne doit pas contenir de chiffres)
    static const QRegularExpression regexNom("^[a-zA-ZÀ-ÿ\\s]+$"); // Accepte uniquement des lettres et des espaces
    if (nom.isEmpty() || !regexNom.match(nom).hasMatch()) {
        QMessageBox::warning(this, "Erreur de saisie", "Le nom ne doit contenir que des lettres et des espaces, sans chiffres.");
        return;
    }

    // Contrôle de saisie pour l'adresse
    if (adr.length() > 20) {
        QMessageBox::warning(this, "Erreur de saisie", "L'adresse ne doit pas dépasser 20 caractères.");
        return;
    }

    // Contrôle de saisie pour le numéro
    if (num_str.length() != 8 || !num_str.toInt()) {
        QMessageBox::warning(this, "Erreur de saisie", "Le numéro doit être composé exactement de 8 chiffres.");
        return;
    }

    // Création de l'objet boutique avec les données saisies
    boutique b(id, nom, adr, num_str.toInt());
    bool test = b.ajouter();

    if (test) {
        ui->tableView->setModel(btq.afficher());
        notification.notif_ajoutboutique();
    }
    else {
        notification.notif_failed();
    }
}


void acceuil::on_modifier_clicked()
{
    ui->nommodifier->setVisible(true);
    ui->adrmodifier->setVisible(true);
    ui->nummodifier->setVisible(true);
    ui->nom1->setVisible(true);
    ui->adr2->setVisible(true);
    ui->num3->setVisible(true);
}


void acceuil::on_annuler_clicked()
{
    ui->nommodifier->setVisible(false);
    ui->adrmodifier->setVisible(false);
    ui->nummodifier->setVisible(false);
    ui->nom1->setVisible(false);
    ui->adr2->setVisible(false);
    ui->num3->setVisible(false);

}

void acceuil::on_enregistrer_clicked()
{
    int id = ui->lineEdit_IDS->text().toInt(); // Récupère l'ID
    if (id == 0) {
        QMessageBox::warning(nullptr, QObject::tr("Attention"),
                             QObject::tr("Veuillez entrer un ID valide."), QMessageBox::Ok);
        return;
    }

    // Déclaration des expressions régulières comme variables statiques
    static const QRegularExpression regexNom("^[a-zA-ZÀ-ÿ\\s]+$"); // Permet les lettres et espaces
    static const QRegularExpression regexAdr("^[a-zA-ZÀ-ÿ0-9\\s,.-]+$"); // Permet lettres, chiffres, espaces, virgules, points et tirets
    static const QRegularExpression regexNum("^\\d{8}$"); // Permet exactement 8 chiffres

    // Récupérer les valeurs des champs de l'interface utilisateur
    QString nom = ui->nommodifier->text();
    QString adr = ui->adrmodifier->text();
    QString numStr = ui->nummodifier->text();

    // Valider le champ nom (seulement des lettres et des espaces)
    if (!nom.isEmpty() && !regexNom.match(nom).hasMatch()) {
        QMessageBox::warning(nullptr, QObject::tr("Attention"),
                             QObject::tr("Le nom doit contenir uniquement des lettres et des espaces."), QMessageBox::Ok);
        return;
    }

    // Valider le champ adresse (seulement des lettres, chiffres, espaces et quelques symboles)
    if (!adr.isEmpty() && !regexAdr.match(adr).hasMatch()) {
        QMessageBox::warning(nullptr, QObject::tr("Attention"),
                             QObject::tr("L'adresse contient des caractères non valides."), QMessageBox::Ok);
        return;
    }

    // Valider le champ numero (doit être exactement 8 chiffres)
    if (!numStr.isEmpty() && !regexNum.match(numStr).hasMatch()) {
        QMessageBox::warning(nullptr, QObject::tr("Attention"),
                             QObject::tr("Le numéro doit contenir exactement 8 chiffres."), QMessageBox::Ok);
        return;
    }

    // Vérifier si au moins un champ est modifié
    if (nom.isEmpty() && adr.isEmpty() && numStr.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Aucune modification"),
                             QObject::tr("Aucune modification n'a été apportée."), QMessageBox::Ok);
        return;
    }

    // Créer un objet boutique avec l'ID
    boutique b(id);

    // Charger les informations existantes de la base de données
    if (!b.chargerDepuisBD()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Impossible de charger les informations actuelles."),
                              QMessageBox::Ok);
        return;
    }

    // Mettre à jour uniquement les champs remplis
    if (!nom.isEmpty()) {
        b.setnom(nom);
    }
    if (!adr.isEmpty()) {
        b.setadr(adr);
    }
    if (!numStr.isEmpty()) {
        b.setnum(numStr.toInt()); // Convertir en entier
    }

    // Appliquer les modifications à la base de données
    bool test = b.modifier();
    if (test) {
        ui->tableView->setModel(btq.afficher());
        notification.notif_modifierboutique();
    } else {
        notification.notif_failed();
    }
}


void acceuil::on_supprimer_clicked()
{
    int id=ui->lineEdit_IDS->text().toInt();
    bool test=btq.supprimer(id);
    if (test)
    {
        ui->tableView->setModel(btq.afficher());
        notification.notif_supprimerboutique();
    }
    else
        notification.notif_failed();
}
void acceuil::on_rechercher_clicked()
{
    // Get the ID from the input field
    QString text = ui->lineEdit_recherche->text();
    if (!text.isEmpty()) {
        int id = text.toInt();
        QSqlQueryModel* model = btq.rechercher(id);
        ui->tableView->setModel(model);
    } else {
        // If the input is empty, show all records
        ui->tableView->setModel(btq.afficher());
    }
}
void acceuil::on_lineEdit_recherche_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        // If the text is empty, show all records
        ui->tableView->setModel(btq.afficher());
    }
}


void acceuil::on_trier_clicked()
{
    // Créer un modèle temporaire pour afficher les données triées par nom
    QSqlQueryModel* model = new QSqlQueryModel();

    // Exécuter la requête pour récupérer et trier les données par nom dans l'ordre alphabétique
    model->setQuery("SELECT IDB, NOM, ADRESSE, NUMB FROM BOUTIQUES ORDER BY IDB ASC");
    // Appliquer le modèle trié au QTableView
    ui->tableView->setModel(model);
}

void acceuil::on_exporter_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), QString(), "*.pdf");
    if (fileName.isEmpty()) {
        return;
    }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    if (!printer.isValid()) {
        QMessageBox::warning(this, tr("Export Failed"), tr("Failed to create the PDF file."));
        return;
    }

    QPainter painter(&printer);
    ui->tableView->render(&painter);
    painter.end();

    QMessageBox::information(this, tr("Export Completed"), tr("PDF export completed successfully."));
}


void acceuil::eventSms(QString event){
    QDate date_debut = ui->dateDebut->date();
    QDate date_fin = ui->dateFin->date();
    int index = ui->boutiques->currentIndex();
    if(date_debut > date_fin){
        QMessageBox::critical(nullptr, QObject::tr("Erreur"),
                              QObject::tr("Date début doit etre avant la date du fin."), QMessageBox::Ok);
    } else {
        QVector<employe> employes = emp.recupererEmployeParBoutique(this->listeBoutiques[index].getid());
        for(int i = 0; i < employes.size(); i++){
            sendSms(date_debut, date_fin, event, employes[i].getNom(), employes[i].getPrenom());
        }
    }
}
void acceuil::on_envoyerBlackFriday_clicked() {
    this->eventSms("Black Friday");
}

void acceuil::on_envoyerNoel_clicked() {
    this->eventSms("Noel");
}

void acceuil::on_envoyerFinAnnee_clicked() {
    this->eventSms("Fin Annee");
}

void acceuil::on_statButton_clicked()
{
    // Clear existing data in case of repeated clicks
    QList<int> boutiqueIds;
    QList<QString> boutiqueAddresses;
    QMap<int, double> montantAchatsParBoutique;

    // Load boutique data (IDs and addresses)
    QSqlQuery queryBoutiques("SELECT IDB, ADRESSE FROM BOUTIQUES");
    while (queryBoutiques.next()) {
        int id = queryBoutiques.value(0).toInt();
        QString address = queryBoutiques.value(1).toString();
        boutiqueIds.append(id);
        boutiqueAddresses.append(address);
    }

    // Load purchase amounts associated with each boutique
    QSqlQuery queryAchats("SELECT IDB, SUM(MONTANTACHAT) FROM ACHATS GROUP BY IDB");
    while (queryAchats.next()) {
        int boutiqueId = queryAchats.value(0).toInt();
        double montantTotal = queryAchats.value(1).toDouble();
        montantAchatsParBoutique[boutiqueId] = montantTotal;
    }

    // Check if data is available to display
    if (boutiqueIds.isEmpty() || montantAchatsParBoutique.isEmpty()) {
        QMessageBox::information(this, "Aucune donnée", "Aucune boutique ou aucun montant d'achat trouvé dans la base de données.");
        return;
    }

    // Create a new pie series
    QPieSeries *pieSeries = new QPieSeries();

    for (int i = 0; i < boutiqueIds.size(); ++i) {
        int boutiqueId = boutiqueIds[i];
        QString boutiqueAddress = boutiqueAddresses[i];
        double montant = montantAchatsParBoutique.value(boutiqueId, 0.0);

        // Append each boutique address and purchase amount as a slice in the pie chart
        QPieSlice *slice = pieSeries->append(boutiqueAddress, montant);

        // Set the label to include both the address and the amount
        slice->setLabel(QString("%1: %2 D").arg(boutiqueAddress).arg(montant, 0, 'f', 2));
        slice->setLabelVisible(true);  // Make label visible
    }

    // Create the chart and add the series
    QChart *chart = new QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Montant d'achat par boutique");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(500, 450);

    // Clear old layout and add new chart view
    QLayout *oldLayout = ui->widget->layout();
    if (oldLayout) {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }

    // Set the new layout with the chart view
    QVBoxLayout *layout = new QVBoxLayout(ui->widget);
    layout->addWidget(chartView);
    ui->widget->setLayout(layout);
}

// send sms
void acceuil::sendSms(QDate date_debut, QDate date_fin, QString event, QString nom, QString prenom){
    QString apiKey = "0916518e7020e7ffc9ecacc0d60d9498-9ec2f2c7-5fdc-475d-89f9-c94d59c68666";
    QString message;
    if(event == "Black Friday")
        message =  "Bonjour monsieur "+nom+" "+prenom+ ", profiter bien de "+event+ " ,  Date Debut: " + date_debut.toString() +" Date fin : "+date_fin.toString();
    else if(event == "Noel")
        message =  "Bonjour monsieur "+nom+" "+prenom+ ", Joyeux "+event+ " ,  Date Debut: " + date_debut.toString() +" Date fin : "+date_fin.toString();
    if(event == "Fin Annee")
        message =  "Bonjour monsieur "+nom+" "+prenom+ ", bonne année à vous et à vos proches , Date Debut: " + date_debut.toString() +" Date fin : "+date_fin.toString();

    QJsonObject json;
    QJsonObject messageObject;
    QJsonArray destinationsArray;
    QJsonObject destination;
    destination["to"] = "21621819816";
    destinationsArray.append(destination);

    messageObject["destinations"] = destinationsArray;
    messageObject["from"] = "ServiceSMS";
    messageObject["text"] = message;

    QJsonArray messagesArray;
    messagesArray.append(messageObject);

    json["messages"] = messagesArray;

    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl("https://3g33gw.api.infobip.com/sms/2/text/advanced"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", "App " + apiKey.toUtf8());
    QNetworkReply *reply = manager.post(request, QJsonDocument(json).toJson());
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << "SMS envoyé avec succès !";
        qDebug() << reply->readAll();
    } else {
        qDebug() << "Échec de l'envoi du SMS:" << reply->errorString();
    }

    delete reply;
}

void acceuil::on_tableView_clicked(const QModelIndex &index)
{

    //generer code QR
    QString text ="boutique details :"+ ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toString()
                   +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),2)).toString()
                   +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3)).toString()
                   +" "+ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),4)).toString();

    using namespace qrcodegen;
    // Create the QR Code object
    QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
    qint32 sz = qr.getSize();
    QImage im(sz,sz, QImage::Format_RGB32);
    QRgb black = qRgb(  0,  0,  0);
    QRgb white = qRgb(255,255,255);
    for (int y = 0; y < sz; y++)
        for (int x = 0; x < sz; x++)
            im.setPixel(x,y,qr.getModule(x, y) ? black : white );
    ui->qrCodeLabel->setPixmap( QPixmap::fromImage(im.scaled(ui->qrCodeLabel->width(),ui->qrCodeLabel->height(),Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}
/*void acceuil::input(){
    data=A.read_from_arduino(); // problem
    ref1= data;
    qDebug()<<ref1.left(ref1.length()-2);
    ref2=ref1.left(ref1.length()-2);
    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE  UIDC  = :UDC");
    query.bindValue(":UDC", ref2);
    query.exec();
    if (query.next()) {
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE employes SET presence = :presence WHERE UIDC = :UDC");
        updateQuery.bindValue(":presence", "in");
        updateQuery.bindValue(":UDC",ref2);

        updateQuery.exec();
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("Bonjour"));
        msgBox.setText(
            QObject::tr("<h3>Bienvenue à Vibe,</h3><p><b>Mr %1 %2</b></p><p>Votre identification a été réussie.</p>")
                .arg(query.value(1).toString())
                .arg(query.value(2).toString())
            );
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setStyleSheet("QMessageBox { font-size: 14px; }"); // Optional styling for a cleaner design
        msgBox.exec();


    }
}*/

/*#include <QMap>
#include <QTimer>
#include <QDateTime>

QMap<QString, QDateTime> scannedUIDsMap;  // Maps UID to the time it was scanned

void acceuil::input() {
    // Lire les données depuis Arduino
    data = A.read_from_arduino();
    ref1 = data;
    qDebug() << ref1.left(ref1.length() - 2);  // Pour afficher la chaîne après avoir enlevé les 2 derniers caractères
    ref2 = ref1.left(ref1.length() - 2);  // UID à scanner, supprimant les caractères indésirables

    // Vérifier si cet UID a déjà été scanné récemment (moins de 10 ms)
    if (scannedUIDsMap.contains(ref2)) {
        qDebug() << "UID déjà scanné : " << ref2;

        // Vérifier si le délai est inférieur à 10 ms
        if (scannedUIDsMap.value(ref2).secsTo(QDateTime::currentDateTime()) < 0.01) { // 0.01 second = 10 milliseconds
            return;  // Si moins de 10 ms se sont écoulées, ne rien faire
        }
    }

    // Marquer cet UID comme scanné avec l'heure actuelle
    scannedUIDsMap.insert(ref2, QDateTime::currentDateTime());

    // Vérifier dans la base de données si l'UID existe
    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE UIDC = :UDC");
    query.bindValue(":UDC", ref2);
    query.exec();

    if (query.next()) {
        // Si l'UID est trouvé, mettre à jour la présence
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE employes SET presence = :presence WHERE UIDC = :UDC");
        updateQuery.bindValue(":presence", "in");
        updateQuery.bindValue(":UDC", ref2);

        if (updateQuery.exec()) {
            // Affichage du message de succès
            QMessageBox msgBox;
            msgBox.setWindowTitle(QObject::tr("Bonjour"));
            msgBox.setText(
                QObject::tr("<h3>Bienvenue à Vibe,</h3><p><b>Mr %1 %2</b></p><p>Votre identification a été réussie.</p>")
                    .arg(query.value(1).toString())  // Prenez le prénom de l'utilisateur
                    .arg(query.value(2).toString())  // Prenez le nom de l'utilisateur
                );
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setStyleSheet("QMessageBox { font-size: 14px; }"); // Optionnel : personnalisation du message
            msgBox.exec();
        } else {
            qDebug() << "Erreur lors de la mise à jour de la présence :" << updateQuery.lastError().text();
        }
    }
    // Utiliser QTimer pour retirer l'UID de la carte après un délai (par exemple, 10 ms)
    QTimer::singleShot(10, this, [&]() {
        scannedUIDsMap.remove(ref2);  // Retirer l'UID après 10 ms pour permettre un nouveau scan
    });
}

*/
#include <QMap>
#include <QTimer>
#include <QDateTime>
QMap<QString, QDateTime> scannedUIDsMap;  // Maps UID to the time it was scanned
void acceuil::input() {
    // Lire les données depuis Arduino
    data = A.read_from_arduino();
    ref1 = data;
    qDebug() << ref1.left(ref1.length() - 2);  // Pour afficher la chaîne après avoir enlevé les 2 derniers caractères
    ref2 = ref1.left(ref1.length() - 2);  // UID à scanner, supprimant les caractères indésirables

    // Vérifier si cet UID a déjà été scanné récemment (moins de 10 ms)
    if (scannedUIDsMap.contains(ref2)) {
        qDebug() << "UID déjà scanné : " << ref2;

        // Vérifier si le délai est inférieur à 10 ms
        if (scannedUIDsMap.value(ref2).secsTo(QDateTime::currentDateTime()) < 0.01) { // 0.01 second = 10 milliseconds
            return;  // Si moins de 10 ms se sont écoulées, ne rien faire
        }
    }

    // Marquer cet UID comme scanné avec l'heure actuelle
    scannedUIDsMap.insert(ref2, QDateTime::currentDateTime());

    // Vérifier dans la base de données si l'UID existe
    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE UIDC = :UDC");
    query.bindValue(":UDC", ref2);
    query.exec();

    if (query.next()) {
        QString currentPresence = query.value("presence").toString();  // Récupérer l'état actuel ("in" ou "out")
        QString newPresence = (currentPresence == "in") ? "out" : "in";  // Calculer le nouvel état

        // Mettre à jour la présence dans la base de données
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE employes SET presence = :presence WHERE UIDC = :UDC");
        updateQuery.bindValue(":presence", newPresence);
        updateQuery.bindValue(":UDC", ref2);

        if (updateQuery.exec()) {
            // Afficher un message approprié en fonction du nouvel état
            QMessageBox msgBox;
            msgBox.setWindowTitle(QObject::tr("Changement d'état"));
            msgBox.setText(
                QObject::tr("<h3>Bienvenue à Vibe,</h3><p><b>Mr %1 %2</b></p><p>Votre état est maintenant : <b>%3</b>.</p>")
                    .arg(query.value("prenom").toString())  // Prenez le prénom de l'utilisateur
                    .arg(query.value("nom").toString())    // Prenez le nom de l'utilisateur
                    .arg(newPresence)                     // Nouvel état
                );
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setStyleSheet("QMessageBox { font-size: 14px; }"); // Optionnel : personnalisation du message
            msgBox.exec();
        } else {
            qDebug() << "Erreur lors de la mise à jour de la présence :" << updateQuery.lastError().text();
        }
    }

    // Utiliser QTimer pour retirer l'UID de la carte après un délai (par exemple, 10 ms)
    QTimer::singleShot(10, this, [&]() {
        scannedUIDsMap.remove(ref2);  // Retirer l'UID après 10 ms pour permettre un nouveau scan
    });
}




/*void acceuil::on_pushButton_7_clicked()
{
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE employes SET presence = :presence WHERE UIDC = :UDC");  // il ya un probleme
    updateQuery.bindValue(":presence", "out");
    updateQuery.bindValue(":UDC",ref2);
    updateQuery.exec();
}
*/
void acceuil::on_pushButton_7_clicked() {
    // Préparation de la requête pour mettre à jour tous les utilisateurs présents ("in") vers "out"
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE employes SET presence = :presence WHERE presence = :currentPresence"); // probleme fixe
    updateQuery.bindValue(":presence", "out");
    updateQuery.bindValue(":currentPresence", "in");

    // Exécution de la requête
    if (updateQuery.exec()) {
        // Message de confirmation avec le design demandé
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("Déconnexion"));
        msgBox.setText(
            QObject::tr("<h3>Déconnexion réussie</h3>"
                        "<p>Tous les utilisateurs actuellement connectés ont été déconnectés.</p>")
            );
        msgBox.setIcon(QMessageBox::Information);  // Icône standard
        msgBox.setStandardButtons(QMessageBox::Ok); // Bouton standard
        msgBox.setStyleSheet("QMessageBox { font-size: 14px; }"); // Style similaire
        msgBox.exec();
    } else {
        // Message d'erreur si la requête échoue
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("Erreur"));
        msgBox.setText(QObject::tr("Une erreur s'est produite lors de la déconnexion des utilisateurs."));
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setStyleSheet("QMessageBox { font-size: 14px; }");
        msgBox.exec();
        qDebug() << "Erreur lors de la mise à jour des présences :" << updateQuery.lastError().text();
    }
}




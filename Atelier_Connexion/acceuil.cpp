#include "acceuil.h"
#include "ui_acceuil.h"
#include "produit.h"
#include <QtDebug>
#include <QTabWidget>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>


acceuil::acceuil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::acceuil)
{
    ui->setupUi(this);

    // Connect the combobox to the sorting function
    connect(ui->comboBox_3, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_3_currentIndexChanged(int)));
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

void acceuil::on_pushButton_16_clicked()
{
    int REFPROD = ui->le_ref->text().toInt();
    QString TYPEP = ui->cb_type->currentText(); // Fixed
    QString NOMP = ui->le_nomp->text();
    int QUANTITE = ui->le_qte->text().toInt();
    QString TAILLEPROD = ui->le_taille->text();
    QString COULEUR = ui->le_col->text();

    // Create a produit object with the data
    PRODUIT P(REFPROD, TYPEP, NOMP, TAILLEPROD, QUANTITE, COULEUR); // Adjusted parameter order

    // Attempt to add the data to the database
    bool insertionSuccess = P.ajouter();

    // Display a message based on the insertion result
    QMessageBox messageBox;
    if (insertionSuccess) {
        messageBox.setText("Data added to the database successfully!");
        // Clear the line edits
        ui->le_ref->clear();
        ui->le_nomp->clear();
        ui->le_qte->clear();
        ui->le_taille->clear();
        ui->le_col->clear();
    } else {
        messageBox.setText("Failed to add data to the database.");
    }
    messageBox.exec();
}

void acceuil::on_pushButton_24_clicked()
{
    int REFToDelete = ui->lineEdit_2->text().toInt(); // Assuming the QLineEdit is named "lineEdit"
    PRODUIT P1;
    bool test = P1.supprimer(REFToDelete);

    if (test)
    {
        //ui->tab_stocks->setModel(P1.afficher());
        QMessageBox::information(this, QObject::tr("OK"),
            QObject::tr("Suppression effectuée\nClick OK to exit."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(this, QObject::tr("Not OK"),
            QObject::tr("Suppression non effectuée\nClick OK to exit."), QMessageBox::Ok);
    }
}


void acceuil::on_pushButton_17_clicked() //afficher
{
    PRODUIT P1;
    QSqlQueryModel* model = P1.afficher();

    ui->tab_produits->setRowCount(model->rowCount());
    ui->tab_produits->setColumnCount(model->columnCount());

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tab_produits->setItem(row, col, new QTableWidgetItem(data));
        }
    }
}



void acceuil::on_pushButton_18_clicked()
{
    int REFPROD = ui->le_ref_3->text().toInt(); // Get the name of the record to modify
    QString newNOMP = ui->le_nomp_2->text();
    QString newTYPEP = ui->cb_type_2->currentText();
    QString newTAILLEPROD = ui->le_taille_2->text();
    int newQUANTITE = ui->le_qte_2->text().toInt();
    QString newCOULEUR = ui->le_col_2->text();

    PRODUIT P1;
    bool success = P1.modifier(REFPROD, newNOMP, newTYPEP, newTAILLEPROD, newQUANTITE, newCOULEUR);

    if (success) {
        // Clear existing items in the QTableWidget
        ui->tab_produits->clearContents();
        ui->tab_produits->setRowCount(0); // Reset row count to avoid overflow

        // Populate the QTableWidget with the new data
        QSqlQueryModel* model = P1.afficher();
        ui->tab_produits->setRowCount(model->rowCount());
        ui->tab_produits->setColumnCount(model->columnCount());

        for (int row = 0; row < model->rowCount(); ++row) {
            for (int col = 0; col < model->columnCount(); ++col) {
                QString data = model->data(model->index(row, col)).toString();
                ui->tab_produits->setItem(row, col, new QTableWidgetItem(data));
            }
        }

        QMessageBox::information(this, QObject::tr("OK"),
            QObject::tr("Modification effectuée\nClick OK to exit."), QMessageBox::Ok);
    } else {
        QMessageBox::information(this, QObject::tr("Not OK"),
            QObject::tr("Modification non effectuée\nClick OK to exit."), QMessageBox::Ok);
    }
}



void acceuil::on_pushButton_19_clicked()
{
    int REFPROD = ui->le_ref_3->text().toInt(); // Assuming REFPROD is in a line edit
        qDebug() << "Fetching data for REFPROD:" << REFPROD; // Debug output

        // Create a new PRODUIT object to fetch the data
        QSqlQuery query;
        query.prepare("SELECT * FROM produits WHERE REFPROD = :ref");
        query.bindValue(":ref", REFPROD);

        if (query.exec()) {
            if (query.next()) {
                // Populate the QLineEdits with the retrieved data
                ui->le_nomp_2->setText(query.value("NOMP").toString());
                ui->cb_type_2->setCurrentText(query.value("TYPEP").toString());
                ui->le_taille_2->setText(query.value("TAILLEPROD").toString());
                ui->le_qte_2->setText(query.value("QUANTITE").toString());
                ui->le_col_2->setText(query.value("COULEUR").toString());
            } else {
                QMessageBox::warning(this, "Fetch Data", "No data found for the given reference.");
            }
        } else {
            QMessageBox::warning(this, "Fetch Data", "Query execution failed: " + query.lastError().text());
        }
}


void acceuil::on_pushButton_11_clicked()
{
    PRODUIT P1;
    QSqlQueryModel* model = P1.afficher2();

    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(3);

    for (int row = 0; row < 3 /*model->rowCount()*/; ++row) {
        for (int col = 0; col < 3/*model->columnCount()*/; ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(data));
        }
    }
}


void acceuil::on_pushButton_12_clicked() //repture stock
{
    PRODUIT P1;
    QSqlQueryModel* model = P1.afficher3();  // Use afficher2 instead of afficher3 to get filtered data.

    if (!model) {
        qDebug() << "Failed to load data.";
        return;
    }

    // Set the number of rows and columns based on the model data
    ui->tableWidget_2->setRowCount(model->rowCount());
    ui->tableWidget_2->setColumnCount(model->columnCount());  // Adjust column count according to the model

    // Loop through the model data and insert it into the table widget
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidget_2->setItem(row, col, new QTableWidgetItem(data));
        }
    }
}



void acceuil::on_pushButton_13_clicked() //alert
{
    PRODUIT P1;
    QSqlQueryModel* model = P1.afficher4();  // Use afficher2 instead of afficher3 to get filtered data.

    /*if (!model) {
        qDebug() << "Failed to load data.";
        return;
    }

    // Set the number of rows and columns based on the model data
    ui->tableWidget_2->setRowCount(model->rowCount());
    ui->tableWidget_2->setColumnCount(model->columnCount());  // Adjust column count according to the model

    // Loop through the model data and insert it into the table widget
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidget_2->setItem(row, col, new QTableWidgetItem(data));
        }
    }*/

    if (!model) {
            qDebug() << "Failed to load data.";
            return;
        }

        // If no rows match the query, show a message box
        if (model->rowCount() == 0) {
            QMessageBox::information(this, "No Data", "No products found with QUANTITE between 1 and 5.");
            return;
        }

        // Create a string to hold the formatted data
        QString message = "ALERT STOCK BAS:\n\n";

        // Loop through the model data and append it to the message string
        for (int row = 0; row < model->rowCount(); ++row) {
            QString refProd = model->data(model->index(row, 0)).toString();  // Assuming REFPROD is the first column
            QString nomP = model->data(model->index(row, 1)).toString();     // Assuming NOMP is the third column
            QString quantite = model->data(model->index(row, 2)).toString(); // Assuming QUANTITE is the fourth column

            // Format the data into a string
            message += QString("REFPROD: %1 | NOMP: %2 | QUANTITE: %3\n").arg(refProd).arg(nomP).arg(quantite);
        }

        // Show the message in a QMessageBox
        QMessageBox msgBox;
        msgBox.setText(message);
        msgBox.exec();
}


void acceuil::on_comboBox_3_currentIndexChanged(int index)
{
    PRODUIT P1;
    QSqlQueryModel* model = P1.afficher2();

    // Check which sort option is selected and apply the appropriate query modification
    if (!model) {
        qDebug() << "Failed to load data.";
        return;
    }

    QString queryStr = "SELECT * FROM PRODUITS";

    // Sorting logic based on combobox selection
    switch (index) {
        case 0:  // A-Z sorting by NOMP
            queryStr += " ORDER BY NOMP ASC";
            break;
        case 1:  // Z-A sorting by NOMP
            queryStr += " ORDER BY NOMP DESC";
            break;
        case 2:  // Ascending order by QUANTITE
            queryStr += " ORDER BY QUANTITE ASC";
            break;
        case 3:  // Descending order by QUANTITE
            queryStr += " ORDER BY QUANTITE DESC";
            break;
        default:
            break;
    }

    // Set the query to the model
    model->setQuery(queryStr);

    // Handle potential errors in the query
    if (model->lastError().isValid()) {
        qDebug() << "Error in SQL query: " << model->lastError().text();
        return;
    }

    // Set headers for the columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));

    // Display the sorted data in the tableWidget
    ui->tableWidget->setRowCount(model->rowCount());
    ui->tableWidget->setColumnCount(model->columnCount());

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(data));
        }
    }
}



void acceuil::on_pushButton_14_clicked()
{
    PRODUIT P1;
    QSqlQueryModel* model = P1.afficher5();

    ui->tableWidget_3->setRowCount(model->rowCount());
    ui->tableWidget_3->setColumnCount(model->columnCount());

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tableWidget_3->setItem(row, col, new QTableWidgetItem(data));
        }
    }
}


void acceuil::on_comboBox_4_currentIndexChanged(int index)
{
    PRODUIT P1;
    QSqlQueryModel* model = P1.afficher();

    // Check which sort option is selected and apply the appropriate query modification
    if (!model) {
        qDebug() << "Failed to load data.";
        return;
    }

    QString queryStr = "SELECT * FROM PRODUITS";

    // Sorting logic based on combobox selection
    switch (index) {
        case 0:  // A-Z sorting by NOMP
            queryStr += " ORDER BY NOMP ASC";
            break;
        case 1:  // Z-A sorting by NOMP
            queryStr += " ORDER BY NOMP DESC";
            break;
        case 2:  // Ascending order by QUANTITE
            queryStr += " ORDER BY QUANTITE ASC";
            break;
        case 3:  // Descending order by QUANTITE
            queryStr += " ORDER BY QUANTITE DESC";
            break;
        default:
            break;
    }

    // Set the query to the model
    model->setQuery(queryStr);

    // Handle potential errors in the query
    if (model->lastError().isValid()) {
        qDebug() << "Error in SQL query: " << model->lastError().text();
        return;
    }

    // Set headers for the columns
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFPROD"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPEP"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMP"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TAILLEPROD"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("COULEUR"));

    // Display the sorted data in the tableWidget
    ui->tab_produits->setRowCount(model->rowCount());
    ui->tab_produits->setColumnCount(model->columnCount());

    for (int row = 0; row < model->rowCount(); ++row) {
        for (int col = 0; col < model->columnCount(); ++col) {
            QString data = model->data(model->index(row, col)).toString();
            ui->tab_produits->setItem(row, col, new QTableWidgetItem(data));
        }
    }
}





void acceuil::on_pushButton_15_clicked() //alert
{
    // Get the product name entered in the line edit
    QString productName = ui->lineEdit_3->text();  // Replace 'lineEdit' with your actual QLineEdit object name

    PRODUIT P1;
    QSqlQueryModel* model = P1.afficher4();  // Use afficher4 to get the data, but we'll filter by name

    if (!model) {
        qDebug() << "Failed to load data.";
        return;
    }

    // If no rows match the query, show a message box
    if (model->rowCount() == 0) {
        QMessageBox::information(this, "No Data", "No products found ");
        return;
    }

    // Create a string to hold the formatted data
    QString message = "produit recherche\n\n";
    bool found = false; // Flag to track if any product with the entered name is found

    // Loop through the model data and check if nomP matches the entered value
    for (int row = 0; row < model->rowCount(); ++row) {
        QString nomP = model->data(model->index(row, 1)).toString();  // Assuming NOMP is the second column

        // If nomP matches the product name from the line edit, add it to the message
        if (nomP.contains(productName, Qt::CaseInsensitive)) {
            QString refProd = model->data(model->index(row, 0)).toString();  // REFPROD is the first column
            QString quantite = model->data(model->index(row, 2)).toString(); // QUANTITE is the third column

            // Format the data into a string and append it to the message
            message += QString("REFPROD: %1 | NOMP: %2 | QUANTITE: %3\n").arg(refProd).arg(nomP).arg(quantite);
            found = true;
        }
    }

    // If no product with the matching name was found
    if (!found) {
        QMessageBox::information(this, "No Matching Products", "No products found with the name: " + productName);
        return;
    }

    // Show the message in a QMessageBox
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}


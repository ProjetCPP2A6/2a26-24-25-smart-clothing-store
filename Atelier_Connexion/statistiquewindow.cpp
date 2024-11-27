#include "statistiquewindow.h"

StatistiqueWindow::StatistiqueWindow(QWidget* parent)
    : QMainWindow(parent) {
    // Configuration principale
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    // Table pour afficher les statistiques
    tableWidget = new QTableWidget(5, 2, this);  // 5 lignes, 2 colonnes
    tableWidget->setHorizontalHeaderLabels({"Produit", "Ventes"});
    layout->addWidget(tableWidget);

    // Bouton pour charger les données
    loadButton = new QPushButton("Charger les données", this);
    layout->addWidget(loadButton);

    // Création et ajout du graphique
    chartView = new QChartView(this);
    layout->addWidget(chartView);

    setCentralWidget(centralWidget);

    // Connexion du bouton
    connect(loadButton, &QPushButton::clicked, this, &StatistiqueWindow::loadData);
}

void StatistiqueWindow::loadData() {
    // Exemple de données
    QStringList produits = {"T-shirt", "Jeans", "Chaussures", "Vestes", "Accessoires"};
    QList<int> ventes = {150, 200, 120, 80, 50};

    // Remplissage du tableau
    for (int i = 0; i < produits.size(); ++i) {
        tableWidget->setItem(i, 0, new QTableWidgetItem(produits[i]));
        tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(ventes[i])));
    }

    // Création du graphique
    QBarSet* set = new QBarSet("Ventes");
    for (int vente : ventes) {
        *set << vente;
    }

    QBarSeries* series = new QBarSeries();
    series->append(set);

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des ventes");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Axe X
    QBarCategoryAxis* axisX = new QBarCategoryAxis();
    axisX->append(produits);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Axe Y
    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, 250);  // Modifier selon vos besoins
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartView->setChart(chart);
}

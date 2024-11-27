#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include "stockmodel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    StockModel *model;
    QTableView *tableView;

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Initialisation du modèle
        model = new StockModel(this);

        // Vue de la table
        tableView = new QTableView(this);
        tableView->setModel(model);
        tableView->setAlternatingRowColors(true); // Meilleure lisibilité
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        // Boutons pour tester la mise à jour des stocks
        QPushButton *updateStockButton = new QPushButton("Update Stock for P001");
        connect(updateStockButton, &QPushButton::clicked, this, [this]() {
            model->updateStock("P001", 2); // Exemple : Mise à jour du stock pour "P001"
        });

        QPushButton *replenishStockButton = new QPushButton("Replenish Stock for P002");
        connect(replenishStockButton, &QPushButton::clicked, this, [this]() {
            model->updateStock("P002", 15); // Exemple : Remise en stock pour "P002"
        });

        // Layout principal
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(tableView);
        layout->addWidget(updateStockButton);
        layout->addWidget(replenishStockButton);

        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        setWindowTitle("Stock Management");
        resize(600, 400);
    }
};

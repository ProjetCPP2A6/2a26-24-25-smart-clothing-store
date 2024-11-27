#include <QAbstractTableModel>
#include <QString>
#include <QVector>
#include "stockmodel.h"

StockModel::StockModel(QObject *parent) : QAbstractTableModel(parent) {
    // Données initiales
    products.append({"P001", "Product A", 5, 10});   // Stock bas
    products.append({"P002", "Product B", 0, 10});  // Stock épuisé
    products.append({"P003", "Product C", 20, 10}); // Stock suffisant
}

int StockModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return products.size();
}

int StockModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 3; // Colonnes : Référence, Nom, Quantité disponible
}

QVariant StockModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= products.size() || index.column() >= 3)
        return QVariant();

    const Product &product = products[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0: return product.REFPROD;        // Référence
            case 1: return product.NOMP;     // Nom
            case 2: return product.QUANTITE;       // Quantité
        }
    }

    if (role == Qt::BackgroundRole) {
        if (product.QUANTITE == 0)
            return QBrush(Qt::red); // Stock épuisé
        else if (product.QUANTITE < product.seuil)
            return QBrush(Qt::yellow); // Stock bas
    }

    return QVariant();
}

QVariant StockModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "Ref. Produit";
            case 1: return "Nom Produit";
            case 2: return "Quantité Disponible";
        }
    }
    return QVariant();
}

void StockModel::updateStock(const QString &refProd, int newQuantity) {
    for (int i = 0; i < products.size(); ++i) {
        if (products[i].REFPROD == refProd) {
            products[i].QUANTITE = newQuantity;
            emit dataChanged(index(i, 0), index(i, 2)); // Mise à jour de la ligne
            return;
        }
    }
}

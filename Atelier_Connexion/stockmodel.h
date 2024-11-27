#ifndef STOCKMODEL_H
#define STOCKMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QVector>
#include <QBrush>

struct Product {
    QString REFPROD;       // Référence du produit
    QString NOMP;    // Nom du produit
    int QUANTITE;          // Quantité disponible
    int seuil;             // Seuil interne pour les alertes
};

class StockModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QVector<Product> products;

public:
    StockModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void updateStock(const QString &refProd, int newQuantity);
};

#endif // STOCKMODEL_H

#include "ArduinoDatabaseLink.h"
#include <QSerialPort>

ArduinoDatabaseLink::ArduinoDatabaseLink(QObject *parent) : QObject(parent) {
    // Configuration du port série
    serial = new QSerialPort(this);
    serial->setPortName("COM5"); // Remplace par le port série de ton Arduino
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Impossible d'ouvrir le port série";
        return;
    }

    connect(serial, &QSerialPort::readyRead, this, &ArduinoDatabaseLink::readFromArduino);


    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_cpp");
    db.setUserName("projetcpp2a26");
    db.setPassword("mp2a26");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
    }
}

ArduinoDatabaseLink::~ArduinoDatabaseLink() {
    if (serial->isOpen())
        serial->close();
    db.close();
}

void ArduinoDatabaseLink::readFromArduino() {
    static QByteArray buffer;

    buffer.append(serial->readAll());

    // Rechercher le caractère '\n' qui marque la fin de la commande
    int newlineIndex = buffer.indexOf('\n');

    while (newlineIndex != -1) {
        QByteArray line = buffer.left(newlineIndex).trimmed();
        buffer.remove(0, newlineIndex + 1); // Supprimer la ligne traitée du buffer

        QString command = QString::fromUtf8(line);
        qDebug() << "Commande reçue de l'Arduino :" << command;

        QStringList parts = command.split(',');
        if (parts.size() == 2) {
            QString reference = parts[0];
            QString statusCode = parts[1];

            QString status;
            if (statusCode == "0") {
                status = "TRAITEMENT";
            } else if (statusCode == "1") {
                status = "EN COURS";
            } else if (statusCode == "2") {
                status = "ARRIVER";
            } else {
                serial->write("FAIL\n");
                qDebug() << "Code d'état invalide :" << statusCode;
                continue;
            }

            // Vérifier la référence dans la base de données
            QSqlQuery query;
            query.prepare("SELECT COUNT(*) FROM LIVRAISONS WHERE REFL = :ref");
            query.bindValue(":ref", reference);
            if (query.exec() && query.next() && query.value(0).toInt() > 0) {
                // Si la référence existe, mettre à jour l'état
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE LIVRAISONS SET ETAT = :status WHERE REFL = :ref");
                updateQuery.bindValue(":status", status);
                updateQuery.bindValue(":ref", reference);
                if (updateQuery.exec()) {
                    serial->write("SUCCESS\n");
                    qDebug() << "Commande mise à jour avec succès.";
                } else {
                    serial->write("FAIL\n");
                    qDebug() << "Erreur lors de la mise à jour :" << updateQuery.lastError().text();
                }
            } else {
                serial->write("FAIL\n");
                qDebug() << "Référence introuvable dans la base de données.";
            }
        } else {
            serial->write("FAIL\n");
            qDebug() << "Format de commande invalide :" << command;
        }

        newlineIndex = buffer.indexOf('\n');
    }
}




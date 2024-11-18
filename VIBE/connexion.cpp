#include "connexion.h"
#include <QSqlError>
#include <QDebug>

Connection::Connection() {}

bool Connection::createConnection() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projet_cpp");
    db.setUserName("projetcpp2a26");
    db.setPassword("mp2a26");

    if (!db.open()) {
        qDebug() << "Erreur ODBC : " << db.lastError().text();
        return false;
    } else {
        return true;
    }
}
void Connection::closeConnection(){db.close();}


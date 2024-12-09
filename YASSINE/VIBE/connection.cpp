#include "connection.h"

connection::connection() {}

bool connection::createConnection()
{
    db = QSqlDatabase::addDatabase("QODBC");

    bool test=false;

    db.setDatabaseName("projet_cpp");
    db.setUserName("projetcpp2a26");
    db.setPassword("mp2a26");

    if (db.open())
    {
        test=true;
    }

    return test;
}

void connection::closeConnection() {db.close();}

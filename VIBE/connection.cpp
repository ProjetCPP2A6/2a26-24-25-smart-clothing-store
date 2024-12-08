#include "connection.h"

Connection::Connection() {}

bool Connection::createConnection()
{
    db = QSqlDatabase::addDatabase("QODBC");

    bool test=false;

    db.setDatabaseName("CPP_Project");
    db.setUserName("projetcpp2a26");
    db.setPassword("mp2a26");

    if (db.open())
    {
        test=true;
    }

    return test;

}
void Connection::closeConnection(){db.close();}

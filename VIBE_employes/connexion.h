#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>

class Connection
{
    QSqlDatabase db;
public:
    Connection();
    bool createConnection();
    void closeConnection();
};
#endif // CONNEXION_H

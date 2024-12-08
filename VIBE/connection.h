#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>


class connection
{
public:
    QSqlDatabase db;
    connection();
    bool createconnection();
    void closeconnection();
};

#endif // CONNECTION_H

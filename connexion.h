#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>

class connection
{
    QSqlDatabase db;
public:
    connection();
    bool createconnection();
    void closeConnection();
};

#endif // CONNEXION_H



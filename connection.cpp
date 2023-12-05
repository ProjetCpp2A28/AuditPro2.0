#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("projet_2A");
    db.setUserName("Fares");
    db.setPassword("faresfares");

    if(db.open())
        test=true;

        return test;
}

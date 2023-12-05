#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Project_C++");
    db.setUserName("ZAHRA");
    db.setPassword("123456");

    if(db.open())
        test=true;

    return test;
}

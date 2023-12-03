#include "connection.h"
#include <QDebug>
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Project_C++");
db.setUserName("zahra");
db.setPassword("123456");

if (db.open())
test=true;
else {
    qDebug() << "Error opening database:" << db.lastError().text();
}


    return  test;
}

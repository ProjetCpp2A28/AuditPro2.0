#include "mainwindow_entreprises.h"
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;
    bool test=c.createconnection();
    MainWindow_Entreprises w;
    if(test)
    {
        w.show();

        QMessageBox::information(nullptr, QObject::tr("database is open"), QObject::tr("Connection successful.n" "Click cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"), QObject::tr("Connection failed.\n" "Click cancel to exit."), QMessageBox::Cancel);

    return a.exec();
}

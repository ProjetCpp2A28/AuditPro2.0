#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <iostream>
#include <string>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QPrinter>
#include <QPainter>
using namespace std;
employe::employe() : loginAttempts(0)
{
    ID = ""; NUM = ""; MDP = "";
    NOM = ""; ADR = ""; DEP = "";

}


employe::employe(QString id,QString num,QString mdp,QString nom,QString adr ,QString dep)
{this->ID=id;this->NUM=num;this->MDP=mdp;this->NOM=nom;this->ADR=adr;this->DEP=dep;}
QString employe::getID(){return ID;}
QString employe::getNUM(){return NUM;}
QString employe::getMDP(){return MDP;}
QString employe::getNOM(){return NOM;}
QString employe::getADR(){return ADR;}
QString employe::getDEP(){return DEP;}
void employe::setid(QString id){this->ID=id;}
void employe::setnum(QString num){this->NUM=num;}
void employe::setmdp(QString mdp){this->MDP=mdp;}
void employe::setnom(QString nom){this->NOM=nom;}
void employe::setadr(QString adr){this->ADR=adr;}
void employe::setdep(QString dep){this->DEP=dep;}
bool employe::ajouter()
{

    QSqlQuery query;
                query.prepare("INSERT INTO EMPLOYE (ID, NUM, MDP, NOM, ADR, DEP) "
                              "VALUES (:ID, :NUM, :MDP, :NOM, :ADR, :DEP)");
                query.bindValue(0,ID);
                query.bindValue(1,NUM);
                query.bindValue(2,MDP);
                query.bindValue(3,NOM);
                query.bindValue(4,ADR);
                query.bindValue(5,DEP);
                return  query.exec();

}
bool employe::supprimer(QString ID)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM REGLEMENT WHERE ID = :ID");
          query.bindValue(":ID", ID);
          query.exec();
          query.next();



                query.prepare("DELETE FROM EMPLOYE WHERE ID=:ID");
                query.bindValue(":ID",ID);

                return  query.exec();

}


QSqlQueryModel* employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("MDP"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADR"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("DEP"));


    return model;


}
bool employe::update(QString  ID,QString NUM,QString  MDP, QString NOM, QString ADR, QString  DEP){


    QSqlQuery query;


       QString queryString = "UPDATE EMPLOYE SET ";
       QStringList updateFields;

       if (!NUM.isEmpty()) updateFields.append("NUM = :NUM");
       if (!MDP.isEmpty()) updateFields.append("MDP = :MDP");
       if (!NOM.isEmpty()) updateFields.append("NOM = :NOM");
       if (!ADR.isEmpty()) updateFields.append("ADR = :ADR");
       if (!DEP.isEmpty()) updateFields.append("DEP = :DEP");


       if (updateFields.isEmpty()) return false;

       queryString += updateFields.join(", ");
       queryString += " WHERE ID = :ID";

       query.prepare(queryString);


       if (!NUM.isEmpty()) query.bindValue(":NUM", NUM);
       if (!MDP.isEmpty()) query.bindValue(":MDP", MDP);
       if (!NOM.isEmpty()) query.bindValue(":NOM", NOM);
       if (!ADR.isEmpty()) query.bindValue(":ADR", ADR);
       if (!DEP.isEmpty()) query.bindValue(":DEP", DEP);

       query.bindValue(":ID", ID);

       return query.exec();


}
int employe::getLoginAttempts() const
{
    return loginAttempts;
}
void employe::resetLoginAttempts()
{
    loginAttempts = 0;
}

bool employe::authenticate(QString enteredID, QString enteredMDP)
{
    QSqlQuery query;
       query.prepare("SELECT * FROM EMPLOYE WHERE ID=:ID AND MDP=:MDP");
       query.bindValue(":ID", enteredID);
       query.bindValue(":MDP", enteredMDP);

       if (query.exec() && query.next()) {

           loginAttempts = 0;
           return true;
       } else {

           loginAttempts++;


           if (loginAttempts == 3) {

               qDebug() << "Sending message to supervisor: Three consecutive failed login attempts.";
               QMessageBox::critical(nullptr, QObject::tr("Login Failed"),
                                     QObject::tr("Failed login attempts."), QMessageBox::Ok);
           }

           return false;
       }
   }

QString employe::getDetailsByID(QString id)
{
    QString details;

    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE ID = :ID");
    query.bindValue(":ID", id);

    if (query.exec() && query.next()) {
        details += "ID: " + query.value(0).toString() + "\n";
        details += "NUM: " + query.value(1).toString() + "\n";
        details += "MDP: " + query.value(2).toString() + "\n";
        details += "NOM: " + query.value(3).toString() + "\n";
        details += "ADR: " + query.value(4).toString() + "\n";
        details += "DEP: " + query.value(5).toString() + "\n";
    }

    return details;
}

void employe::exportToPDF(QString id)
{
    QString employeeInfo = getDetailsByID(id);

        if (!employeeInfo.isEmpty()) {
            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            QString fileName = "employee_info.pdf";
            printer.setOutputFileName(fileName);

            QPainter painter;
            painter.begin(&printer);

            painter.drawText(100, 100, employeeInfo);

            painter.end();

            printer.setOutputFileName("");

            QMessageBox::information(nullptr, QObject::tr("Export Successful"),
                                     QObject::tr("Details exported to %1").arg(fileName),
                                     QMessageBox::Ok);
        } else {
            qDebug() << "Error: Employee not found or an error occurred.";
            QMessageBox::critical(nullptr, QObject::tr("Export Error"),
                                  QObject::tr("Employee not found or an error occurred."),
                                  QMessageBox::Ok);
        }
}



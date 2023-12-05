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
//using namespace std;
employe::employe() : loginAttempts(0)
{
    ID = ""; NUMERO_TELEPHONE = ""; MDP = "";
    NOM = ""; ADRESSE_MAIL = ""; DEPARTEMENT = "";

}


employe::employe(QString id,QString num,QString mdp,QString nom,QString adr ,QString dep)
{this->ID=id;this->NUMERO_TELEPHONE=num;this->MDP=mdp;this->NOM=nom;this->ADRESSE_MAIL=adr;this->DEPARTEMENT=dep;}
QString employe::getID(){return ID;}
QString employe::getNUM(){return NUMERO_TELEPHONE;}
QString employe::getMDP(){return MDP;}
QString employe::getNOM(){return NOM;}
QString employe::getADR(){return ADRESSE_MAIL;}
QString employe::getDEP(){return DEPARTEMENT;}
void employe::setid(QString id){this->ID=id;}
void employe::setnum(QString num){this->NUMERO_TELEPHONE=num;}
void employe::setmdp(QString mdp){this->MDP=mdp;}
void employe::setnom(QString nom){this->NOM=nom;}
void employe::setadr(QString adr){this->ADRESSE_MAIL=adr;}
void employe::setdep(QString dep){this->DEPARTEMENT=dep;}
bool employe::ajouter()
{

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYES (ID, NOM, ADRESSE_MAIL, MDP , DEPARTEMENT ,NUMERO_TELEPHONE) "
                  "VALUES (:ID, :NOM, :ADRESSE_MAIL, :MDP, :DEPARTEMENT, :NUMERO_TELEPHONE)");
    query.bindValue(0,ID);
    query.bindValue(5,NUMERO_TELEPHONE);
    query.bindValue(3,MDP);
    query.bindValue(1,NOM);
    query.bindValue(2,ADRESSE_MAIL);
    query.bindValue(4,DEPARTEMENT);
    return  query.exec();

}
bool employe::supprimer(QString ID)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE ID = :ID");
    query.bindValue(":ID", ID);
    query.exec();
    query.next();



    query.prepare("DELETE FROM EMPLOYES WHERE ID=:ID");
    query.bindValue(":ID",ID);

    return  query.exec();

}


QSqlQueryModel* employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NUMERO_TELEPHONE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("MDP"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESSE_MAIL"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DEPARTEMENT"));


    return model;


}
bool employe::update(QString  ID,QString NUMERO_TELEPHONE,QString  MDP, QString NOM, QString ADRESSE_MAIL, QString  DEPARTEMENT){


    QSqlQuery query;


    QString queryString = "UPDATE EMPLOYES SET  ";
    QStringList updateFields;

    if (!NUMERO_TELEPHONE.isEmpty()) updateFields.append("NUMERO_TELEPHONE = :NUMERO_TELEPHONE");
    if (!MDP.isEmpty()) updateFields.append("MDP = :MDP");
    if (!NOM.isEmpty()) updateFields.append("NOM = :NOM");
    if (!ADRESSE_MAIL.isEmpty()) updateFields.append("ADRESSE_MAIL = :ADRESSE_MAIL");
    if (!DEPARTEMENT.isEmpty()) updateFields.append("DEPARTEMENT = :DEPARTEMENT");


    if (updateFields.isEmpty()) return false;

    queryString += updateFields.join(", ");
    queryString += " WHERE ID = :ID";

    query.prepare(queryString);


    if (!NUMERO_TELEPHONE.isEmpty()) query.bindValue(":NUMERO_TELEPHONE", NUMERO_TELEPHONE);
    if (!MDP.isEmpty()) query.bindValue(":MDP", MDP);
    if (!NOM.isEmpty()) query.bindValue(":NOM", NOM);
    if (!ADRESSE_MAIL.isEmpty()) query.bindValue(":ADRESSE_MAIL", ADRESSE_MAIL);
    if (!DEPARTEMENT.isEmpty()) query.bindValue(":DEPARTEMENT", DEPARTEMENT);

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
    query.prepare("SELECT * FROM EMPLOYES WHERE ID=:ID AND MDP=:MDP");
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
    query.prepare("SELECT * FROM EMPLOYES WHERE ID = :ID");
    query.bindValue(":ID", id);

    if (query.exec() && query.next()) {
        details += "ID: " + query.value(0).toString() + "\n";
        details += "NUMERO_TELEPHONE: " + query.value(1).toString() + "\n";
        details += "MDP: " + query.value(2).toString() + "\n";
        details += "NOM: " + query.value(3).toString() + "\n";
        details += "ADRESSE_MAIL: " + query.value(4).toString() + "\n";
        details += "DEPARTEMENT: " + query.value(5).toString() + "\n";
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



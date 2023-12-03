#include "reclamation.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QMessageBox>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QPrinter>
#include <QPainter>



Reclamation::Reclamation()
{
    id_reclamation=""; type_reclamation=" ";expediteur=" ";
    destinateur=" ";nbr_reclamation="";

}

Reclamation::Reclamation(QString id_reclamation,QString type_reclamation,QString expediteur,QString destinateur,QString nbr_reclamation)
{this->id_reclamation=id_reclamation ;this->type_reclamation=type_reclamation ;this->expediteur=expediteur ;
    this->destinateur=destinateur ;this->nbr_reclamation=nbr_reclamation;}
QString Reclamation:: getid_reclamation(){return id_reclamation;}
QString Reclamation:: gettype_reclamation(){return type_reclamation;}
QString Reclamation:: getexpediteur(){return expediteur;}
QString Reclamation:: getdestinateur(){return destinateur;}
QString Reclamation:: getnbr_reclamation(){return nbr_reclamation;}
void Reclamation:: setid_reclamation(QString id_reclamation){this->id_reclamation=id_reclamation;}
void Reclamation:: settype_reclamation(QString type_reclamation){this->type_reclamation=type_reclamation ;}
void Reclamation:: setexpediteur(QString expediteur){this->expediteur=expediteur ;}
void Reclamation:: setdestinateur(QString destinateur){this->destinateur=destinateur ;}
void Reclamation:: setnbr_reclamation(QString nbr_reclamation){this->nbr_reclamation=nbr_reclamation ;}

bool Reclamation::ajouter(){


    QSqlQuery query;

    query.prepare("INSERT INTO RECLAMATION (ID_RECLAMATION, TYPE_RECLAMATION,EXPEDITEUR,DESTINATEUR,NBR_RECLAMATIONS) "
                  "VALUES (:id_reclamation,:type_reclamation,:expediteur,:destinateur,:nbr_reclamation)");
    query.bindValue(":id_reclamation", id_reclamation);
    query.bindValue(":type_reclamation", type_reclamation);
    query.bindValue(":expediteur", expediteur);
    query.bindValue(":destinateur", destinateur);
    query.bindValue(":nbr_reclamation", nbr_reclamation);



    return query.exec();

}
QSqlQueryModel* Reclamation::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();




    model->setQuery("SELECT* FROM reclamation");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("identifiant"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("type_reclamation"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("expediteur"));
    model->setHeaderData(3, Qt::Horizontal,QObject:: tr("destinateur"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("nombre_de_reclamation"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("message"));
    return model;


}




bool Reclamation::suprimer(QString id_reclamation)
{
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM RECLAMATION WHERE ID_RECLAMATION = :ID_R");
    query.bindValue(":ID_R", id_reclamation);
    query.exec();
    query.next();
    int count = query.value(0).toInt();
    if (count == 0) {
        // ID_R does not exist in the database, return false
        QMessageBox::critical(nullptr,QObject::tr("Erreur"),
                              QObject::tr("cet id n'existe pas\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
        return false;
    }
    else{

        query.prepare("Delete from RECLAMATION WHERE ID_RECLAMATION= :id_reclamation");
        query.bindValue(":id_reclamation",id_reclamation);

        return query.exec();
    }
}

bool Reclamation::update(QString id_reclamation,QString type_reclamation,QString expediteur ,QString destinateur,QString nbr_reclamation){
    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM RECLAMATION WHERE ID_RECLAMATION = :ID_R");
    query.bindValue(":ID_R", id_reclamation);
    query.exec();
    query.next();

    if (query.exec() && query.next()) {
        query.prepare("UPDATE RECLAMATION SET ID_RECLAMATION = :id_reclamation, TYPE_RECLAMATION = :type_reclamation, EXPEDITEUR = :expediteur, DESTINATEUR =:destinateur, NBR_RECLAMATIONS = :nbr_reclamation WHERE ID_RECLAMATION = :id_reclamation");

        query.prepare("UPDATE RECLAMATION SET ID_RECLAMATION = :id_reclamation, TYPE_RECLAMATION = :type_reclamation, EXPEDITEUR = :expediteur, DESTINATEUR =:destinateur, NBR_RECLAMATIONS = :nbr_reclamation WHERE ID_RECLAMATION = :id_reclamation");
        query.bindValue(":id_reclamation", id_reclamation);
        query.bindValue(":type_reclamation", type_reclamation);
        query.bindValue(":expediteur", expediteur);
        query.bindValue(":destinateur", destinateur);
        query.bindValue(":nbr_reclamation", nbr_reclamation);
    }else
    {          QMessageBox::critical(nullptr,QObject::tr("Erreur"),
                              QObject::tr("cet id n'existe pas\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
    }

    return query.exec();
        //}


}

bool Reclamation::addMessage(QString id_reclamation, QString message)
{
    QSqlQuery query;
    query.prepare("UPDATE RECLAMATION SET MESSAGE = :message WHERE ID_RECLAMATION = :id_reclamation");
    query.bindValue(":id_reclamation", id_reclamation);
    query.bindValue(":message", message);

    return query.exec();
}
QString Reclamation::getDetailsByID(QString ID_RECLAMATION)
{
    QString details;

    QSqlQuery query;
    query.prepare("SELECT * FROM RECLAMATION WHERE ID_RECLAMATION = :ID_RECLAMATION");
    query.bindValue(":ID_RECLAMATION", ID_RECLAMATION);

    if (query.exec() && query.next()) {
        details += "ID_RECLAMATION: " + query.value(0).toString() + "\n";
        details += "TYPE_RECLAMATION: " + query.value(1).toString() + "\n";
        details += "EXPEDITEUR: " + query.value(2).toString() + "\n";
        details += "DESTINATEUR: " + query.value(3).toString() + "\n";
        details += "NBR_RECLAMATIONS: " + query.value(4).toString() + "\n";
        details += "MESSAGE: " + query.value(5).toString() + "\n";
    }

    return details;
}

void Reclamation::exportToPDF(QString id_reclamation)
{
    QString reclamationInfo = getDetailsByID(id_reclamation);

    if (!reclamationInfo.isEmpty()) {
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        QString fileName = "employee_info.pdf";
        printer.setOutputFileName(fileName);

        QPainter painter;
        painter.begin(&printer);

        painter.drawText(100, 100, reclamationInfo);

        painter.end();
        // Close the printer after use
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


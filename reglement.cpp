#include "reglement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QDate>

Reglement::Reglement()
{
    ID_REGLEMENT=0;
    Type=" ";
    validation=" ";
    date =QDate::currentDate();
    description=" ";

}
//constrcuteur parametré
Reglement::Reglement(int ID_REGLEMENT ,QString Type ,QString validation,QDate date,QString description)
{this->ID_REGLEMENT=ID_REGLEMENT;this->date=date;this->validation=validation;this->Type=Type;this->description=description;}

int Reglement:: getid(){return ID_REGLEMENT;}
QDate Reglement::getdate(){return date;}
QString Reglement:: getType(){return Type;}
QString Reglement:: getdescription(){return description;}
QString Reglement:: getvalidation(){return validation;}
void Reglement:: setid(int ID_REGLEMENT){this->ID_REGLEMENT=ID_REGLEMENT;}
void Reglement:: setdate(QDate date){this->date=date;}
void Reglement:: setType(QString Type){this->Type=Type;}
void Reglement:: setdescription(QString description){this->description=description;}
void Reglement:: setvalidation(QString validation) {this->validation=validation;}

// requete sql pour inserer les data dans mon tableau
//QSqlQuery: on l'utilise pour communiquer entre le programme et le base de donnes
bool Reglement::ajouter()
{
    QSqlQuery query,query1;
    QString id_r_string=QString::number(ID_REGLEMENT);

    query1.prepare("insert into HISTORIQUE (CODE_HISTORIQUE,ACTION,USER_HISTORIQUE)""values (:code_hist,'AJOUTER','ADMIN')");


    query.prepare("INSERT INTO REGLEMENT (ID_REGLEMENT, TYPE, VALIDATION,DATE_REGLEMENT,DESCRIPTION) "
                  "VALUES (:ID_REGLEMENT,:TYPE,:VALIDATION,:DATE_REGLEMENT,:DESCRIPTION)");


    query.bindValue(":ID_REGLEMENT",id_r_string);
    query.bindValue(":TYPE",Type);
    query.bindValue(":VALIDATION",validation);
    query.bindValue(":DATE_REGLEMENT",date);
    query.bindValue(":DESCRIPTION",description);
    query1.bindValue(":code_hist",id_r_string);


    query1.exec();
    return query.exec();

}


QSqlQueryModel* Reglement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    // select* == select all cad afficher tous qui exsiste en base de donnes

    model->setQuery("SELECT* FROM REGLEMENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_REGLEMENT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("VALIDATION"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_REGLEMENT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DESCRIPTION"));





    return model;

}

//supprimer  du mon tableau  ligne Y hassb id_r
bool Reglement::supprimer(int ID_REGLEMENT){

    QSqlQuery query,query1;
    QString res = QString::number(ID_REGLEMENT);
    query1.prepare("insert into HISTORIQUE (CODE_HISTORIQUE,ACTION,USER_HISTORIQUE)""values (:code_hist,'DELETE','ADMIN')");
    query.prepare("DELETE FROM REGLEMENT WHERE ID_REGLEMENT=:ID_REGLEMENT");

    query.bindValue(":ID_REGLEMENT", res);

    query1.bindValue(":code_hist",res);

    query.exec();


    return query1.exec();

    if (!query.exec()) {
        return false;  // Failed to execute the query
    }
    if (query.numRowsAffected() == 0) {
        return false;  // No rows were affected
    }
    return true;

}
bool Reglement::modifier(int ID_REGLEMENT,QString type,QString validation,QDate date,QString description){

    QSqlQuery query ,query1;
    query.prepare("SELECT COUNT(*) FROM REGLEMENT WHERE ID_REGLEMENT = :ID_REGLEMENT");
    query.bindValue(":ID_REGLEMENT", ID_REGLEMENT);
    query.exec();
    query.next();
    int count = query.value(0).toInt();
    if (count == 0) {
        // ID_R does not exist in the database, return false
        return false;
    }

    QString id_r_string = QString::number(ID_REGLEMENT);
    query1.prepare("insert into HISTORIQUE (CODE_HISTORIQUE,ACTION,USER_HISTORIQUE)""values (:CODE_HISTORIQUE,'UPDATE','ADMIN')");
    query.prepare("UPDATE REGLEMENT SET TYPE = COALESCE(:TYPE, TYPE), VALIDATION = COALESCE(:VALIDATION, VALIDATION), DATE_REGLEMENT = COALESCE(:DATE_REGLEMENT, DATE_REGLEMENT), DESCRIPTION = COALESCE(:DESCRIPTION, DESCRIPTION) WHERE ID_REGLEMENT = :ID_REGLEMENT");
    query.bindValue(":TYPE", type.isEmpty() ? QVariant::fromValue(QString()) : type);
    query.bindValue(":VALIDATION", validation.isEmpty() ? QVariant::fromValue(QString()) : validation);
    query.bindValue(":DATE_REGLEMENT", !date.isValid() ? QVariant::fromValue(QDate()) : date);
    query.bindValue(":DESCRIPTION", description.isEmpty() ? QVariant::fromValue(QString()) : description);

    query1.bindValue(":CODE_HISTORIQUE",id_r_string);
    query1.exec();

    return query.exec();
}


/*QSqlQueryModel * Reglement::trierReglement(QString test)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    if(test == "default"){
        model->setQuery("SELECT * from REGLEMENT");
    }
    else if(test =="id")
    {
        model->setQuery("SELECT * from REGLEMENT order by ID_REGLEMENT asc ");
    }
    else if(test =="type")
    {
        model->setQuery("SELECT * from REGLEMENT order by TYPE asc ");
    }
    else if(test =="description")
    {
        model->setQuery("SELECT * from REGLEMENT order by VALIDATION asc ");
    }
    else if(test =="date")
    {
        model->setQuery("SELECT * from REGLEMENT order by DATE_REGLEMENT asc ");
    }
    else if(test =="validation")
    {
        model->setQuery("SELECT * from REGLEMENT order by DESCRIPTION asc ");
    }

    return model;
}*/
QSqlQueryModel * Reglement::trierReglement(QString test)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    if (test == "default") {
        model->setQuery("SELECT * from REGLEMENT");
    }
    else if (test == "id") {
        model->setQuery("SELECT * from REGLEMENT order by ID_REGLEMENT asc");
    }
    else if (test == "type") {
        // Tri alphabétique pour la colonne TYPE
        model->setQuery("SELECT * from REGLEMENT order by TYPE asc");
    }
    else if (test == "description") {
        model->setQuery("SELECT * from REGLEMENT order by DESCRIPTION asc");
    }
    else if (test == "date") {
        model->setQuery("SELECT * from REGLEMENT order by DATE_REGLEMENT asc");
    }
    else if (test == "validation") {
        model->setQuery("SELECT * from REGLEMENT order by VALIDATION asc");
    }

    return model;
}

QSqlQueryModel * Reglement::rechercherReglement(QString chaine)
{ //like =filtrage
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * from REGLEMENT where ( ID_REGLEMENT LIKE'%"+chaine+"%' OR TYPE LIKE'%"+chaine+"%' OR VALIDATION LIKE'%"+chaine+"%' OR DATE_REGLEMENT LIKE'%"+chaine+"%' OR DESCRIPTION LIKE'%"+chaine+"%') ");


    return model ;



}//historique+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
QSqlQueryModel * Reglement::afficher_his()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from HISTORIQUE ORDER BY DATE_HISTORIQUE ");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("N°:"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("ACTION :"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("BY :"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DATE :"));

    return model;
}

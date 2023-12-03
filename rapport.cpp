#include "rapport.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include <QDate>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
Rapport::Rapport()
{
    ID_RAPPORT="";
    ID_AUDITEUR="";
    OBJET_RAPPORT="";
    RESULTAT="";
    RECOMMENDATION="";
    DATE_CREATION= "";
    NOM_ENTREPRISE="";
}

Rapport::Rapport(QString ID_RAPPORT,QString ID_AUDITEUR,QString DATE_CREATION,QString OBJET_RAPPORT, QString RESULTAT,QString RECOMMENDATION,QString NOM_ENTREPRISE)
{
    this->ID_RAPPORT=ID_RAPPORT;this->ID_AUDITEUR=ID_AUDITEUR;this->DATE_CREATION=DATE_CREATION;this->OBJET_RAPPORT=OBJET_RAPPORT;this->RESULTAT=RESULTAT;this->RECOMMENDATION=RECOMMENDATION;this->NOM_ENTREPRISE=NOM_ENTREPRISE;
}
QString Rapport:: getid_rap()
    {return ID_RAPPORT;}
QString Rapport:: getid_audit()
    {return ID_AUDITEUR;}
QString Rapport:: getdate()
    {return DATE_CREATION;}
QString Rapport:: getresult()
    {return RESULTAT;}
QString Rapport:: getreclamation()
    {return RECOMMENDATION;}
QString Rapport:: getobjet()
    {return OBJET_RAPPORT;}
QString Rapport:: getnomE()
    {return NOM_ENTREPRISE;}
void Rapport:: setid_rap(QString ID_RAPPORT)
{this->ID_RAPPORT=ID_RAPPORT;}
void Rapport:: setid_audit(QString ID_AUDITEUR)
    {this->ID_AUDITEUR=ID_AUDITEUR;}
void Rapport:: setdate(QString DATE_CREATION)
    {this->DATE_CREATION=DATE_CREATION;}
void Rapport:: setobjet(QString OBJET_RAPPORT)
    {this->OBJET_RAPPORT=OBJET_RAPPORT;}
void Rapport:: setresult(QString RESULTAT)
    {this->RESULTAT=RESULTAT;}
void Rapport:: setreclamation(QString RECOMMENDATION)
    {this->RECOMMENDATION=RECOMMENDATION;}
void Rapport:: setnomE(QString NOM_ENTREPRISE)
    {this->NOM_ENTREPRISE=NOM_ENTREPRISE;}

bool Rapport::ajouter()
{
    QSqlQuery query;
    //QString id_string=QString::number(id_rap);
    //QString datestring=date.toString("yyyy-MM-dd");
          query.prepare("INSERT INTO RAPPORTS_AUDITS (ID_RAPPORT,OBJET_RAPPORT,ID_AUDITEUR ,DATE_CREATION,RESULTAT,RECOMMENDATION,NOM_ENTREPRISE ) "
                        "VALUES (:ID_RAPPORT,:OBJET_RAPPORT,:ID_AUDITEUR,:DATE_CREATION,:RESULTAT,:RECOMMENDATION,:NOM_ENTREPRISE)");
          //QString id_string=QString::number(id_rap);

          query.bindValue(0, ID_RAPPORT);
          query.bindValue(1, OBJET_RAPPORT);
          query.bindValue(2, ID_AUDITEUR);
          query.bindValue(3, DATE_CREATION);
          query.bindValue(4, RESULTAT);
          query.bindValue(5, RECOMMENDATION);
          query.bindValue(6, NOM_ENTREPRISE);
          return query.exec();
}

QSqlQueryModel* Rapport::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("select * from RAPPORTS_AUDITS");
    model->setHeaderData(0,Qt:: Horizontal, QObject::tr("ID RAPPORT"));
    model->setHeaderData(1,Qt:: Horizontal, QObject::tr("OBJET"));
    model->setHeaderData(2,Qt:: Horizontal, QObject::tr("ID AUDITEUR"));
    model->setHeaderData(3,Qt:: Horizontal, QObject::tr("DATE DE CREATION"));
    model->setHeaderData(4,Qt:: Horizontal, QObject::tr("RESULTAT"));
    model->setHeaderData(5,Qt:: Horizontal, QObject::tr("RECOMMENDATION"));
    model->setHeaderData(6,Qt:: Horizontal, QObject::tr("NOM_ENTREPRISE"));



    return model;
}
bool Rapport::supprimer(QString ID_RAPPORT)
{
    QSqlQuery query;
    //QString res=QString::number(id_rap);
    query.prepare("Delete from RAPPORTS_AUDITS where ID_RAPPORT= :ID_RAPPORT");
    query.bindValue(0,ID_RAPPORT);
    return query.exec();
}

bool Rapport::update(QString ID_RAPPORT,QString ID_AUDITEUR,QString DATE_CREATION,QString OBJET_RAPPORT, QString RESULTAT,QString RECOMMENDATION,QString NOM_ENTREPRISE )
{
    QSqlQuery query;

    //QString datestring=date.toString("yyyy-MM-dd");
    query.prepare("UPDATE RAPPORTS_AUDITS SET ID_RAPPORT= :ID_RAPPORT ,OBJET_RAPPORT = :OBJET_RAPPORT,ID_AUDITEUR = :ID_AUDITEUR, DATE_CREATION = :DATE_CREATION, RESULTAT = :RESULTAT, RECOMMENDATION = :RECOMMENDATION, NOM_ENTREPRISE = :NOM_ENTREPRISE WHERE ID_RAPPORT = :ID_RAPPORT");
    query.bindValue(":ID_RAPPORT", ID_RAPPORT);
    query.bindValue(":OBJET_RAPPORT", OBJET_RAPPORT);
    query.bindValue(":ID_AUDITEUR", ID_AUDITEUR);
    query.bindValue(":DATE_CREATION", DATE_CREATION);
    query.bindValue(":RESULTAT", RESULTAT);
    query.bindValue(":RECOMMENDATION", RECOMMENDATION);
    query.bindValue(":NOM_ENTREPRISE", NOM_ENTREPRISE);

    return query.exec();
}
bool Rapport::checkid(QString ID_RAPPORT)
{
    QSqlQuery query;
    query.prepare("SELECT ID_RAPPORT FROM RAPPORTS_AUDITS WHERE ID_RAPPORT = :ID_RAPPORT");
    query.bindValue(":ID_RAPPORT", ID_RAPPORT);

    if (query.exec() && query.next()) {
        return true;
    } else
        return false;
}
int Rapport::checkinput(QString ID_RAPPORT,QString ID_AUDITEUR, QString RESULTAT)
{
    int test;

    if (ID_RAPPORT.length()!=8)
        test=1;
    if (ID_AUDITEUR.length()!=8)
        test=2;
    if (RESULTAT!="valide" && RESULTAT!="semi valide" && RESULTAT!="non valide")
        test=3;

    return test;
}

QString Rapport::getDetailsByID(QString ID_RAPPORT)
{
    QString details;

    QSqlQuery query;
    query.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE ID_RAPPORT = :ID_RAPPORT");
    query.bindValue(":ID_RAPPORT", ID_RAPPORT);

    if (query.exec() && query.next()) {
        details += "ID_RAPPORT: " + query.value(0).toString() + "\n";
        details += "OBJET_RAPPOORT: " + query.value(1).toString() + "\n";
        details += "ID_AUDITEUR: " + query.value(2).toString() + "\n";
        details += "DATE_CREATION: " + query.value(3).toString() + "\n";
        details += "RESULTAT: " + query.value(4).toString() + "\n";
        details += "RECOMMENDATION: " + query.value(5).toString() + "\n";
        details += "NOM_ENTREPRISE: " + query.value(5).toString() + "\n";
    }

    return details;
}

void Rapport::exportToPDF(QString ID_RAPPORT)
{
    QString rapportInfo = getDetailsByID(ID_RAPPORT);

    if (!rapportInfo.isEmpty()) {
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        QString fileName = "rapportInfo.pdf";
        printer.setOutputFileName(fileName);

        QPainter painter;
        painter.begin(&printer);

        painter.drawText(100, 100, rapportInfo);

        painter.end();
        // Close the printer after use
        printer.setOutputFileName("");

        QMessageBox::information(nullptr, QObject::tr("Export Successful"),
                                 QObject::tr("Details exported to %1").arg(fileName),
                                 QMessageBox::Ok);
    } else {
        qDebug() << "Error: Rapport not found or an error occurred.";
        QMessageBox::critical(nullptr, QObject::tr("Export Error"),
                              QObject::tr("Employee not found or an error occurred."),
                              QMessageBox::Ok);
    }
}


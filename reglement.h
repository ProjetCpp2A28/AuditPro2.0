#ifndef REGLEMENT_H
#define REGLEMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QDate>



class Reglement
{
public:
    Reglement();
    Reglement(int,QString,QString,QDate,QString);
    int getid();
    QDate getdate();
    QString getType();
    QString getdescription();
    QString getvalidation();
    void setid(int);
    void setdate(QDate);
    void setType(QString);
    void setdescription(QString);
    void setvalidation(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QDate,QString);


    QSqlQueryModel * trierReglement(QString);
    QSqlQueryModel * rechercherReglement(QString);
    QSqlQueryModel * afficher_his();

private:
    int ID_REGLEMENT;
    QDate date;
    QString Type,description,validation;








};

#endif // REGLEMENT_H

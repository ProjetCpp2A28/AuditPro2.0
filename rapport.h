#ifndef RAPPORT_H
#define RAPPORT_H
#include <QSqlQueryModel>
#include <QString>
#include <QDate>
#include <QRegularExpression>
#include <QString>


class Rapport
{
public:

    Rapport();
    Rapport(QString,QString,QString,QString,QString,QString,QString);
    QString getid_rap();
    QString getid_audit();
    QString getobjet();
    QString getresult();
    QString getreclamation();
    QString getdate();
    QString getnomE();
    void setid_rap(QString);
    void setid_audit(QString);
    void setobjet(QString);
    void setresult(QString);
    void setreclamation(QString);
    void setdate(QString);
    void setnomE(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool update(QString,QString,QString,QString,QString,QString,QString);
    bool checkid(QString);
    void remplirmodifier(QString);
    int checkinput(QString,QString,QString);
    void exportToPDF(QString ID_RAPPORT);
    QString getDetailsByID(QString ID_RAPPORT);

private:

    //int id_rap;
    //QDate date;
    QString ID_RAPPORT,OBJET_RAPPORT,RESULTAT,RECOMMENDATION,ID_AUDITEUR,DATE_CREATION,NOM_ENTREPRISE;

};

#endif // RAPPORT_H

#ifndef RECLAMATION_H
#define RECLAMATION_H
#include <QString>
#include<QSqlQueryModel>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>



class Reclamation
{
public:
    Reclamation();
    Reclamation(QString,QString,QString,QString,QString);
    QString getid_reclamation();
    QString gettype_reclamation();
    QString getexpediteur();
    QString getdestinateur();
    QString getnbr_reclamation();

    QString getmessage();

    void setid_reclamation(QString);
    void settype_reclamation(QString);
    void setexpediteur(QString);
    void setdestinateur(QString);
    void setnbr_reclamation(QString);
    void setmessage(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool suprimer(QString);
    bool update(QString,QString,QString,QString,QString);
    bool addMessage(QString id_reclamation, QString message);
    void exportToPDF(QString id_reclamation);
    QString getDetailsByID(QString ID);

private:
    QString id_reclamation;
    QString type_reclamation, expediteur,destinateur;
    QString nbr_reclamation;

};

#endif // RECLAMATION_H

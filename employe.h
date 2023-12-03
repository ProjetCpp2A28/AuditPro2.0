#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQueryModel>
#include <QString>
class employe
{

public:
    employe();
    employe(QString,QString,QString,QString,QString,QString);
    QString getID();
    QString getNUM();
    QString getMDP();
    QString getNOM();
    QString getADR();
    QString getDEP();

    void setid(QString);
    void setnum(QString);
    void setmdp(QString);
    void setnom(QString);
    void setadr(QString);
    void setdep(QString);

    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString );
    bool update(QString,QString,QString,QString,QString,QString);
    bool authenticate(QString enteredID, QString enteredMDP);
    int getLoginAttempts() const;
    void resetLoginAttempts();

    void exportToPDF(QString id);
    QString getDetailsByID(QString id);

private:

    QString  ID, NUMERO_TELEPHONE, MDP;
    QString NOM,ADRESSE_MAIL,DEPARTEMENT;

    int loginAttempts;

};

#endif // EMPLOYE_H

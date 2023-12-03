#ifndef ENTREPRISE_H
#define ENTREPRISE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


#include <QDialog>
#include <QDate>
//mail
#include <QByteArray>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslSocket>

#include <QtCore/QTextStream>

#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>

class entreprise
{
private:
    QString nom, email, localisation;
    QString id_entreprise, num_telephone;
public:
    entreprise();
    entreprise(QString,QString,QString,QString,QString); //sans nbr_rapport

    QString getnom(){return nom;}
    QString getemail(){return email;}
    QString getlocalisation(){return localisation;}
    QString getid_entreprise(){return id_entreprise;}
    QString getnum_telephone(){return num_telephone;}

    void setnom(QString n){nom=n;}
    void setemail(QString e){email=e;}
    void setlocalisation(QString l){localisation=l;}
    void setid_entreprise(QString id_entreprise){this->id_entreprise=id_entreprise;}
    void setnum_telephone(QString nt){num_telephone=nt;}

    //Fonctionnalite CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString, QString , QString  , QString , QString );
    bool checkid(QString);

    QString getDetail_id_entreprise(QString);
    void exportToPDF(QString);

    bool isValidEmail(QString);

    int countRows();


};

#endif // ENTREPRISE_H

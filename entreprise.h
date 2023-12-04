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
    int id_entreprise, nombre_rapport, num_telephone;
public:
    entreprise();
    entreprise(int,QString,int,QString,QString); //sans nbr_rapport
    entreprise(int,QString,int,int,QString,QString); //avec nbr_rapport

    QString getnom(){return nom;}
    QString getemail(){return email;}
    QString getlocalisation(){return localisation;}
    int getid_entreprise(){return id_entreprise;}
    int getnombre_rapport(){return nombre_rapport;}
    int getnum_telephone(){return num_telephone;}

    void setnom(QString n){nom=n;}
    void setemail(QString e){email=e;}
    void setlocalisation(QString l){localisation=l;}
    void setid_entreprise(int id_entreprise){this->id_entreprise=id_entreprise;}
    void setnombre_rapport(int nr){nombre_rapport=nr;}
    void setnum_telephone(int nt){num_telephone=nt;}

    //Fonctionnalite CRUD
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int, QString , int  , QString , QString );
    bool checkid(int);

    QString getDetail_id_entreprise(int);
    void exportToPDF(int);

    bool isValidEmail(QString);

    int countRows();


};

#endif // ENTREPRISE_H

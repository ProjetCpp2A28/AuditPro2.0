#include "entreprise.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QRegularExpression>



entreprise::entreprise(int id_entreprise,QString nom,int num_telephone,QString email,QString localisation)
{
    this->id_entreprise=id_entreprise;
    this->nom=nom;
    this->num_telephone=num_telephone;
    this->email=email;
    this->localisation=localisation;
}

entreprise::entreprise(int id_entreprise,QString nom,int nombre_rapport,int num_telephone,QString email,QString localisation)
{
    this->id_entreprise=id_entreprise;
    this->nom=nom;
    this->nombre_rapport=nombre_rapport;
    this->num_telephone=num_telephone;
    this->email=email;
    this->localisation=localisation;
}
entreprise::entreprise()
{
    id_entreprise=0;
    nombre_rapport=0;
    num_telephone=0;
    nom="";
    email="";
    localisation="";
}

bool entreprise::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id_entreprise);

    query.prepare("INSERT INTO ENTREPRISES (ID_ENTREPRISE, NOM, NOMBRE_RAPPORT, NUM_TELEPHONE, EMAIL, LOCALISATION) "
                        "VALUES (:ID_ENTREPRISE, :NOM,:NOMBRE_RAPPORT, :NUM_TELEPHONE, :EMAIL, :LOCALISATION)");

    query.bindValue(":ID_ENTREPRISE",res);
    query.bindValue(":NOM",nom);
    query.bindValue(":NOMBRE_RAPPORT",nombre_rapport);
    query.bindValue(":NUM_TELEPHONE",num_telephone);
    query.bindValue(":EMAIL",email);
    query.bindValue(":LOCALISATION",localisation);

    return query.exec();
}
QSqlQueryModel * entreprise::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM ENTREPRISES");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nombre de rapport"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numero de telephone"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse email"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Localisation"));

    return model;
}
bool entreprise::supprimer(int id_entreprise)
{
    QSqlQuery query;
    QString res=QString::number(id_entreprise);

    query.prepare("Delete from ENTREPRISES where id_entreprise= :id_entreprise");
    query.bindValue(":id_entreprise",res);

    if (!query.exec()) {
            return false;  // Failed to execute the query
        }
        if (query.numRowsAffected() == 0) {
            return false;  // No rows were affected
        }
        return true;
 }

bool entreprise::checkid(int id_entreprise)
{
    QSqlQuery query;
    QString ID_ENTREPRISE = QString::number(id_entreprise); // Convert int to QString
    query.prepare("SELECT ID_ENTREPRISE FROM ENTREPRISES WHERE ID_ENTREPRISE = :ID_ENTREPRISE");
    query.bindValue(":ID_ENTREPRISE", ID_ENTREPRISE);

    if (query.exec() && query.next()) {
        qDebug() << "ID existant trouvé dans la base de données.";
        return true;
    } else {
        qDebug() << "ID non existant ou erreur SQL :";
        if (!query.exec()) {
            qDebug() << "Erreur SQL :";
        }
        return false;
    }
}

bool entreprise::modifier(int id_entreprise, QString nom, int num_telephone , QString email, QString localisation)
{
    QSqlQuery query;

    query.prepare("UPDATE ENTREPRISES  set ID_ENTREPRISE=:ID_ENTREPRISE, NOM =:NOM, NUM_TELEPHONE=:NUM_TELEPHONE ,EMAIL=:EMAIL ,LOCALISATION=:LOCALISATION  where ID_ENTREPRISE=:ID_ENTREPRISE");
    query.bindValue(":ID_ENTREPRISE", id_entreprise);
    query.bindValue(":NOM",nom);
    query.bindValue(":NUM_TELEPHONE",num_telephone);
    query.bindValue(":EMAIL",email);
    query.bindValue(":LOCALISATION", localisation);


    return    query.exec();
}
QString entreprise::getDetail_id_entreprise(int ID_ENTREPRISE)
{
    QString details;

    QSqlQuery query;
    query.prepare("SELECT * FROM ENTREPRISES WHERE ID_ENTREPRISE = :ID_ENTREPRISE");
    query.bindValue(":ID_ENTREPRISE", ID_ENTREPRISE);

    if (query.exec() && query.next()) {
        details += "ID_ENTREPRISE: " + query.value(0).toString() + "\n";
        details += "NOM: " + query.value(1).toString() + "\n";
        details += "NOMBRE_RAPPORT: " + query.value(2).toString() + "\n";
        details += "NUM_TELEPHONE: " + query.value(3).toString() + "\n";
        details += "EMAIL: " + query.value(4).toString() + "\n";
        details += "LOCALISATION: " + query.value(5).toString() + "\n";
    }

    return details;
}
void entreprise::exportToPDF(int id_entreprise)
{
    QString entrepriseInfo = getDetail_id_entreprise(id_entreprise);

        if (!entrepriseInfo.isEmpty()) {
            QPrinter printer;
            printer.setOutputFormat(QPrinter::PdfFormat);
            QString fileName = "employee_info.pdf";
            printer.setOutputFileName(fileName);

            QPainter painter;
            painter.begin(&printer);

            painter.drawText(100, 100, entrepriseInfo);

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

//-------------------- checks mail validation done
bool entreprise::isValidEmail(QString email) {
    QRegularExpression regex("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}");

       // We use QRegularExpressionMatch to test if the email matches the regex pattern
       QRegularExpressionMatch match = regex.match(email);

       // If the match is valid, return true. Otherwise, return false.
       return match.hasMatch();
}

int entreprise::countRows() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM ENTREPRISES");
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return -1;  // Return -1 in case of an error
}

#include "mainwindow_entreprises.h"
#include "ui_mainwindow_entreprises.h"
#include "entreprise.h"
#include "stat_combo.h"
#include "smtp.h"

#include "stardelegate.h"
#include "stareditor.h"
#include "starrating.h"

#include <QtWidgets>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDebug>
#include <QSortFilterProxyModel>

#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>

#include <QIntValidator>
#include <QApplication>
#include <QPrinter>
#include <QTextStream>
#include <QPrintDialog>
#include <QSqlQuery>
#include <QComboBox>
#include <QSaveFile>
#include <QBuffer>
#include <QFileDialog>
#include <QFile>
#include <QDesktopServices>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>
#include <QTime>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QTableWidgetItem>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QDateEdit>
#include <QPixmap>
#include <QTabWidget>
#include <QObject>
#include <QDialog>
#include <QValidator>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QSequentialAnimationGroup>
#include <QState>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPainter>
#include <QString>
#include <QStatusBar>
#include <QTimer>
#include <QDateTime>



MainWindow_Entreprises::MainWindow_Entreprises(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow_Entreprises)
{

    ui->setupUi(this);
    //ui->Table_entreprise->setModel(E.afficher());
    show_table();
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));


}

MainWindow_Entreprises::~MainWindow_Entreprises()
{
    delete ui;
}


void MainWindow_Entreprises::on_B_ajouter_clicked()
{

    QString id_entreprise_string = ui->id_Entreprise->text();
    QString num_telephone_string = ui->num_tel->text();
    QString email = ui->email->text();
            bool ok_id;
            bool ok_tel;

            int id_entreprise = id_entreprise_string.toInt(&ok_id);
            int num_telephone = num_telephone_string.toInt(&ok_tel);
            QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

            if ((!ok_id) || (!ok_tel) || (num_telephone_string.length() < 8) || (!emailRegex.match(email).hasMatch())) {

               QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for ID ENTREPRISE or NUMERO TELEPHONE (at least 8 digits) and a valid email address.");
               return;
            }
    //int id_entreprise=ui->id_Entreprise->text().toInt();
    QString nom=ui->nom_entreprise->text();
    int nombre_rapport=0;
    //int num_telephone=ui->num_tel->text().toInt();
    //QString email=ui->email->text();
    QString localisation=ui->loc->text();

    entreprise e(id_entreprise, nom, nombre_rapport, num_telephone, email, localisation);

    bool test=e.ajouter();

    QMessageBox msgBox;

    if(test)
     {
        msgBox.setText("Ajout avec succes.");
        //ui->Table_entreprise->setModel(E.afficher());
        show_table();
    }
    else
        msgBox.setText("Echec d'ajout.");
    msgBox.exec();

}

void MainWindow_Entreprises::on_B_supp_clicked()
{
    entreprise e1; e1.setid_entreprise(ui->id_supp_2->text().toInt());
    bool test=e1.supprimer(e1.getid_entreprise());

    QMessageBox msgBox;

    if(test)
    {
        msgBox.setText("Suppression avec succes.");
        //ui->Table_entreprise->setModel(E.afficher());
        show_table();
    }
    else
        msgBox.setText("Echec de suppression.");
    msgBox.exec();
}

void MainWindow_Entreprises::on_B_modifier_clicked()
{
    int id_entreprise=ui->id_Entreprise_2->text().toInt();
    QString nom=ui->nom_entreprise_2->text();
    QString localisation=ui->loc_2->text();

    QString num_telephone_string = ui->num_tel_2->text();
    QString email = ui->email_2->text();

    bool ok_tel;

    int num_telephone = num_telephone_string.toInt(&ok_tel);
    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

    if ((!ok_tel) || (num_telephone_string.length() < 8) || (!emailRegex.match(email).hasMatch())) {

       QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for NUMERO TELEPHONE (at least 8 digits) and a valid email address.");
       return;
    }

    entreprise E(id_entreprise, nom, num_telephone,  email, localisation);

    bool test = E.modifier(id_entreprise, nom, num_telephone , email, localisation);

    QMessageBox msgBox;

        if (test)
        {
            msgBox.setText("Modification avec succès.");
            //ui->Table_entreprise->setModel(E.afficher());
            show_table();
        }
        else
        {
            msgBox.setText("Échec de la modification.");
        }
        msgBox.exec();
}

void MainWindow_Entreprises::on_B_CheckID_clicked()
{
    int id_entreprise=ui->id_Entreprise_2->text().toInt();
        bool test=E.checkid(id_entreprise);
        if (test)
        {
            QSqlQuery query;
            query.prepare("select * from ENTREPRISES where ID_ENTREPRISE= :ID_ENTREPRISE ");
            query.bindValue(":ID_ENTREPRISE", id_entreprise);
            if (query.exec() && query.next())
            {
                QSqlRecord record = query.record();
                ui->id_Entreprise_2->setText(query.value(record.indexOf("ID_ENTREPRISE")).toString());
                ui->nom_entreprise_2->setText(query.value(record.indexOf("NOM")).toString());
                ui->num_tel_2->setText(query.value(record.indexOf("NUM_TELEPHONE")).toString());
                ui->email_2->setText(query.value(record.indexOf("EMAIL")).toString());
                ui->loc_2->setText(query.value(record.indexOf("LOCALISATION")).toString());

            }
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not OK"),
                        QObject::tr("L'ID n'existe pas.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow_Entreprises::show_table()
{
    proxy = new QSortFilterProxyModel();
    ////tableau source
    proxy->setSourceModel(E.afficher());
    /// recherche
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(-1);
        ui->Table_entreprise->setModel(proxy);
}


void MainWindow_Entreprises::on_lineEdit_textChanged(const QString &text)
{
    proxy->setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::FixedString));
}

void MainWindow_Entreprises::on_comboBox_recherche_currentIndexChanged(int index)
{
    proxy->setFilterKeyColumn(index);
}

void MainWindow_Entreprises::on_comboBox_trie_currentIndexChanged(int index)
{
    Qt::SortOrder sortOrder = (ui->checkBox_descendant->checkState() == Qt::Checked) ? Qt::DescendingOrder : Qt::AscendingOrder;
        proxy->sort(index, sortOrder);
}


void MainWindow_Entreprises::on_pushButton_stat_clicked()
{
    s = new stat_combo();

    // Effectuer le calcul ici pour garantir que c1 et c2 sont corrects
    qreal tot = 0, c1 = 0, c2 = 0;

    QSqlQuery q1, q2, q3;
    q1.prepare("SELECT * FROM RAPPORTS_AUDITS");
    q1.exec();

    q2.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide'");
    q2.exec();

    q3.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='non valide'");
    q3.exec();

    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }

    c1 = (c1 / tot) * 100;
    c2 = (c2 / tot) * 100;

    // Passer les valeurs correctes à la classe stat_combo
    s->setPourcentageValide(c1);
    s->setPourcentageNonValide(c2);

    // Maintenant, appeler la fonction choix_pie
    s->setWindowTitle("statistique Nombre Rapport");
    s->choix_pie();
    s->show();
}


void MainWindow_Entreprises::on_pushButton_stat_2_clicked()
{
    s = new stat_combo();

    // Effectuer le calcul ici pour garantir que c1 et c2 sont corrects
    qreal tot = 0, c1 = 0, c2 = 0;

    QSqlQuery q1, q2, q3;
    q1.prepare("SELECT * FROM RAPPORTS_AUDITS");
    q1.exec();

    q2.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide'");
    q2.exec();

    q3.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='non valide'");
    q3.exec();

    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }

    c1 = (c1 / tot) * 100;
    c2 = (c2 / tot) * 100;

    // Passer les valeurs correctes à la classe stat_combo
    s->setPourcentageValide(c1);
    s->setPourcentageNonValide(c2);

    // Maintenant, appeler la fonction choix_bar
    s->setWindowTitle("statistique Nombre Rapport");
    s->choix_bar();
    s->show();
}

void MainWindow_Entreprises::on_pushButton_stat_3_clicked()
{
    s = new stat_combo();
    s->setWindowTitle("statistique Localisation");
      s->choix_pie_loc();
      s->show();

}




void MainWindow_Entreprises::on_pushButton_clicked()
{
    int idToExport = ui->lineEdit_2->text().toInt();
    entreprise E;
    QString details = E.getDetail_id_entreprise(idToExport);
    QString idToExport2 = QString::number(idToExport); // Corrected this line

    if (!details.isEmpty()) {
        QString fileName = "entreprise_details_" + idToExport2 + ".pdf"; // Corrected this line

        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QTextStream stream(&file);
            stream << details;
            file.close();

            QMessageBox::information(nullptr, QObject::tr("Export Successful"),
                                     QObject::tr("Details exported to %1").arg(fileName),
                                     QMessageBox::Ok);
        } else {
            qDebug() << "Error: Unable to create or write to the PDF file.";
            QMessageBox::critical(nullptr, QObject::tr("Export Error"),
                                  QObject::tr("Unable to create or write to the PDF file."),
                                  QMessageBox::Ok);
        }
    } else {
        qDebug() << "Error: Entreprise not found or an error occurred.";
        QMessageBox::critical(nullptr, QObject::tr("Export Error"),
                              QObject::tr("Entreprise not found or an error occurred."),
                              QMessageBox::Ok);
    }
}


void MainWindow_Entreprises::on_send_mail_2_clicked()
{
    entreprise c;

       smtp* ssmtp = new smtp("asmanegra@gmail.com", "oyejlywzffgybuat", "smtp.gmail.com", 587);

               connect(ssmtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

               QString email=ui->client_mail_to_send_2->text();

               QString b=ui->client_mail_to_subject_2->text();

               QString ob=ui->client_mail_text_2->toPlainText();

                if(email!="" && b!="" && ob!="" )
                   {
                                 if(c.isValidEmail(email))
                                 {
                                     ssmtp->sendMail("asma.negra@esprit.tn", email , b,ob);
                                     QMessageBox::information(nullptr, QObject::tr("EMAIL"),
                                     QObject::tr("Email Envoyé avec succees.\n"
                                     "click Cancel to exit"),QMessageBox::Cancel);
                                 }
                                 else
                                 {
                                     QMessageBox::critical(nullptr, QObject::tr("EMAIL"),
                                     QObject::tr("Email is wrong in.\n"
                                     "click Cancel to exit."),QMessageBox::Cancel);
                                 }
                   }
                else
                   {
                           QMessageBox::critical(nullptr, QObject::tr("EMAIL"),
                           QObject::tr("something is empty.\n"
                           "click Cancel to exit."),QMessageBox::Cancel);
                   }
}

/*void MainWindow_Entreprises::on_Button_Star_Rating_clicked()
{
    int n=E.countRows();
    QTableWidget* tableWidget = new QTableWidget(5, n);
        tableWidget->setItemDelegate(new StarDelegate);
        tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked
                                      | QAbstractItemView::SelectedClicked);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        QStringList headerLabels;
        headerLabels << "Nom entreprise" << "Etat Accreditation" << "Resultat Rapport d'audit" << "Validation Reglement" << "Rating" ;
        tableWidget->setHorizontalHeaderLabels(headerLabels);

        populateTableWidget(tableWidget);

        tableWidget->resizeColumnsToContents();
        tableWidget->resize(500, 300);
        tableWidget->show();
}*/

/*oui je peux utiliser cet exemple comme guide, maintenant est ce que vous pouver m aider pour l'exctraction de donnees voici ce que je veux faire:
tout d'abord le nombre de colonnes affichees dependra du nombre d'entreprises trouvees dans la data base le nom de la table est ENTREPRISES , il aura 3 criteres a evaluer : résultat, validation, accreditation. La reponse pour chaque criteres sera trouve dans la data base comme suis:
table RAPPORTS_AUDITS attribut RESULTAT donnees "valide" ou "non valide"
table REGLEMENT attribut VALIDATION donnees "valide" ou "non valide"
table ACCREDITATION attribut ETAT donnees "accrede" ou "non accrede"
sachant que les id de toutes les tables que j ai appele ici doivent avoir le meme id que "ID_ENTREPRISE" (ID_ACCREDITATION= ID_RAPPORT =  ID_REGLEMENT)
si tout est valide l'entreprise aura 3 etoiles sinon 2 sinon 1 (c'est logique)
implemnter la focntion  qui me permettra de faire ceci avant d'appuyer sur le bouton et avoir l affichage des etoiles

*/

/*void MainWindow_Entreprises::on_B_CheckID_2_clicked()
{
    int id_entreprise = ui->id_Entreprise_3->text().toInt();
    qDebug() << "Requête SQL exécutée : " << query.lastQuery();
    bool exists = E.checkid(id_entreprise);
    if (exists)
        {
            QMessageBox::information(nullptr, QObject::tr("ID Existence Check"),
                                     QObject::tr("L'ID existe."), QMessageBox::Ok);
        }
        else
        {
            QMessageBox::warning(nullptr, QObject::tr("ID Existence Check"),
                                 QObject::tr("L'ID n'existe pas."), QMessageBox::Cancel);

        }
}*/

void MainWindow_Entreprises::on_B_CheckID_2_clicked()
{
    int id_entreprise = ui->id_Entreprise_3->text().toInt();

    bool exists = E.checkid(id_entreprise);

    qDebug() << "La valeur retournée par checkid : " << exists;

    if (exists)
    {
        QMessageBox::information(nullptr, QObject::tr("ID Existence Check"),
                                 QObject::tr("L'ID existe."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(nullptr, QObject::tr("ID Existence Check"),
                             QObject::tr("L'ID n'existe pas."), QMessageBox::Cancel);
    }
}



void MainWindow_Entreprises::on_B_arduino_clicked()
{
    QString id_entreprise = ui->id_Entreprise_3->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM ACCREDITATION WHERE ID_ACCREDITATION = :ID_ACCREDITATION");
    query.bindValue(":ID_ACCREDITATION", id_entreprise);

    if (query.exec() && query.next()) {
        QString dateString = query.value("DATE_ACCREDITATION").toString();
        QDate dateAccreditation = QDate::fromString(dateString, "yyyy-MM-dd");

        int periode = query.value("PERIODE").toInt();

        QDate expirationDate = dateAccreditation.addYears(periode);

        QDate currentDate = QDate::currentDate();
        if (currentDate > expirationDate) {

            QMessageBox::warning(this, "Accreditation Expired", "Accreditation has expired!");
            A.write_to_arduino("3");
        } else {
            QMessageBox::warning(this, "Accreditation Not Expired", "Accreditation has not expired!");
            A.write_to_arduino("0");
        }
    } else {

        QMessageBox::warning(this, "Invalid ID", "ID not found in ACCREDITATION table!");

    }
}

void MainWindow_Entreprises::update_label() {
    if (!codeExecuted) {
        data = A.read_from_arduino2();
        data=data.left(1);
        qDebug() << "Received data from Arduino: " << data;

        if (data != "" && data != "Firmware Version: 0x92 = v2.0\r\n" && data!="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"){
            ui->etat->setText(data);
    //        int id = data.toInt();

            if (data=="1") {
                qDebug() << "ok access";
                A.write_to_arduino2("1");
            } else {
                qDebug() << "pas d'acces";
                A.write_to_arduino2("2");

            }
        }

        // Set the boolean variable to true, indicating the code has been executed
        codeExecuted = true;
    }

}

void MainWindow_Entreprises::on_pushButton_2_clicked()
{
    codeExecuted = false;

}

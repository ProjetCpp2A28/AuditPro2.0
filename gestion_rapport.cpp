#include "gestion_rapport.h"
#include "ui_gestion_rapport.h"

#include "rapport.h"

#include <QMessageBox>
#include <QObject>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QMainWindow>
#include <QLayout>
#include <QRegularExpression>
#include <QInputDialog>
#include <QThread>

Gestion_Rapport::Gestion_Rapport(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gestion_Rapport)
{
    ui->setupUi(this);
    chartView=nullptr;
    chart=nullptr;
    chartView1=nullptr;
    chart1=nullptr;

    show_table();
    
    ui->lineEdit_3idauditeur->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_idrapport_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_2idrapport->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_idauditeur_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_check->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_supp->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_id->setValidator(new QIntValidator(0, 99999999, this));

    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
}

Gestion_Rapport::~Gestion_Rapport()
{
    delete ui;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////arduino
void Gestion_Rapport::on_pushButton_changer_clicked()
{
    QString ID_RAPPORT=ui->lineEdit_id->text();
    QString RESULTAT="valide";
    key =A.read_from_arduino() ;
    QString key1=QString::fromUtf8(key);
    if (key1=="8")
    {
        QSqlQuery query;
        query.prepare("UPDATE RAPPORTS_AUDITS SET RESULTAT = :RESULTAT WHERE ID_RAPPORT = :ID_RAPPORT");
        query.bindValue(":RESULTAT", RESULTAT);
        query.bindValue(":ID_RAPPORT", ID_RAPPORT);
        query.exec();
        A.write_to_arduino("9");
    }
    ui->lineEdit_id->clear();


}
void Gestion_Rapport::on_pushButton_valide_clicked()
{
    QString ID_RAPPORT=ui->lineEdit_id->text();
    QString RESULTAT;
    QSqlQuery query;
    query.prepare("SELECT RESULTAT FROM RAPPORTS_AUDITS WHERE ID_RAPPORT = :ID_RAPPORT");
    query.bindValue(":ID_RAPPORT", ID_RAPPORT);
    if (query.exec() && query.next()) {
        RESULTAT = query.value(0).toString();
        if (RESULTAT=="valide")
        {
            A.write_to_arduino("2");
            ui->lineEdit_id->clear();
        }
        else if (RESULTAT=="semi valide")
        {
            A.write_to_arduino("3");
        }
        else if (RESULTAT=="non valide")
        {
            A.write_to_arduino("4");
            ui->lineEdit_id->clear();
        }
    } else
    {
        A.write_to_arduino("0");
        ui->lineEdit_id->clear();
    }
}
void Gestion_Rapport::on_arduino_clicked()
{
    enteredID =A.read_from_arduino() ;
    QString ID_RAPPORT=QString::fromUtf8(enteredID);

    ui->lineEdit_id->setText(ID_RAPPORT);
    QSqlQuery query;
    query.prepare("SELECT ID_RAPPORT FROM RAPPORTS_AUDITS WHERE ID_RAPPORT = :ID_RAPPORT");
    query.bindValue(":ID_RAPPORT", ID_RAPPORT);
    if (query.exec() && query.next()) {
        A.write_to_arduino("1");

    } else
    {
        A.write_to_arduino("0");
        ui->lineEdit_id->clear();
    }
}
/*void Gestion_Rapport::id_existe()
{
    enteredID =A.read_from_arduino() ;
    QString ID_RAPPORT=QString::fromUtf8(enteredID);
    QString RESULTAT;
    QString RESULTAT2="valide";

    ui->lineEdit_id->setText(ID_RAPPORT);
    QSqlQuery query;
    query.prepare("SELECT ID_RAPPORT FROM RAPPORTS_AUDITS WHERE ID_RAPPORT = :ID_RAPPORT");
    query.bindValue(":ID_RAPPORT", ID_RAPPORT);
    if (query.exec() && query.next()) {
        A.write_to_arduino("1");
        QThread::msleep(5000);
        RESULTAT = query.value(0).toString();
        if (RESULTAT=="valide")
        {
            A.write_to_arduino("2");
            ui->lineEdit_id->clear();
        }
        else if (RESULTAT=="semi valide")
        {
            A.write_to_arduino("3");
            QThread::msleep(10000);
            key =A.read_from_arduino() ;
            QString key1=QString::fromUtf8(key);
            if (key1=="8")
            {
                QSqlQuery query;
                query.prepare("UPDATE RAPPORTS_AUDITS SET RESULTAT = :RESULTAT2 WHERE ID_RAPPORT = :ID_RAPPORT");
                query.bindValue(":RESULTAT", RESULTAT2);
                query.bindValue(":ID_RAPPORT", ID_RAPPORT);
                query.exec();
                A.write_to_arduino("9");
            }
        }
        else if (RESULTAT=="non valide")
        {
            A.write_to_arduino("4");
            ui->lineEdit_id->clear();
        }
    } else
    {
        A.write_to_arduino("0");
        ui->lineEdit_id->clear();
    }
}*/

////---------------------------TableView-------------------------------////
void Gestion_Rapport::show_table()
{

    proxy = new QSortFilterProxyModel();
    proxy->setSourceModel(r.afficher());
    proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy->setFilterKeyColumn(-1);
    ui->tableView->setModel(proxy);
}

void Gestion_Rapport::clear_form( )
{
    ui->lineEdit_date->clear();
    ui->lineEdit_3idauditeur->clear();
    ui->lineEdit_2idrapport->clear();
    ui->lineEdit_5objet->clear();
    ui->lineEdit_result->clear();
    ui->lineEdit_recommendation->clear();
    ui->lineEdit_1nomentrep->clear();
    ui->lineEdit_check->clear();
    ui->lineEdit_nomentrep_2->clear();
    ui->lineEdit_idrapport_2->clear();
    ui->lineEdit_idauditeur_2->clear();
    ui->lineEdit_objet_2->clear();
    ui->lineEdit_result_2->clear();
    ui->lineEdit_recommendation_2->clear();
    ui->lineEdit_date_2->clear();

}

/////////////////////////////////////*********************CRUD***********************//////////////////////////////////////////
////////////////Create
void Gestion_Rapport::on_pushButton_ajouter_clicked()
{

    QRegularExpression numericRegex("^[0-9]+$");
    QString ID_RAPPORT=ui->lineEdit_3idauditeur->text();
    QString ID_AUDITEUR=ui->lineEdit_2idrapport->text();
    QString RESULTAT=ui->lineEdit_result->text();
    QString OBJET_RAPPORT=ui->lineEdit_5objet->text();
    QString RECOMMENDATION=ui->lineEdit_recommendation->text();
    QString DATE_CREATION=ui->lineEdit_1nomentrep->text();
    QString NOM_ENTREPRISE=ui->lineEdit_date->text();

    int test=r.checkinput(ID_RAPPORT,ID_AUDITEUR,RESULTAT);
        if (test==1)
        {
            QMessageBox::warning(this, "invalide","Non valid ID RAPPORT.\n"
                                                  "Please enter a valid integer for ID RAPPORT containing 8 caracters \n"
                                                  "Click Cancel to exit.");
        return;
        }
        if (test==2)
        {
            QMessageBox::warning(this, "invalide","Non valid ID AUDITEUR.\n"
                                                  "Please enter a valid integer for ID AUDITEUR containing 8 caracters \n"
                                                  "Click Cancel to exit.");
        return;
        }
        if (test==3)
        {
            QMessageBox::warning(this, "invalide","Non valid RESULT.\n"
                                                  "(valide/semi valide/non valide) \n"
                                                  "Click Cancel to exit.");
        return;
        }
        if (!numericRegex.match(ID_RAPPORT).hasMatch())
        {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for ID RAPPORT containing only numbers.");
            return;
        }
        if (!numericRegex.match(ID_AUDITEUR).hasMatch())
        {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for ID AUDITEUR containing only numbers.");
            return;
        }

    Rapport r(ID_RAPPORT,ID_AUDITEUR,DATE_CREATION,OBJET_RAPPORT,RESULTAT,RECOMMENDATION,NOM_ENTREPRISE);
    bool test2=r.ajouter();
    if(test2)
    {
        show_table();
        clear_form();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("Ajout not successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

////////////////Read
void Gestion_Rapport::on_pushButton_afficher_clicked()
{
    show_table();
}

////////////////Update
void Gestion_Rapport::on_pushButton_check_clicked()
{
    QString ID_RAPPORT=ui->lineEdit_check->text();
    bool test=r.checkid(ID_RAPPORT);
    if (test)
    {
        QSqlQuery query;
        query.prepare("select * from RAPPORTS_AUDITS where ID_RAPPORT= :ID_RAPPORT ");
        query.bindValue(":ID_RAPPORT", ID_RAPPORT);
        if (query.exec() && query.next())
        {
            QSqlRecord record = query.record();
            ui->lineEdit_idrapport_2->setText(query.value(record.indexOf("ID_RAPPORT")).toString());
            ui->lineEdit_idauditeur_2->setText(query.value(record.indexOf("ID_AUDITEUR")).toString());
            ui->lineEdit_objet_2->setText(query.value(record.indexOf("OBJET_RAPPORT")).toString());
            ui->lineEdit_result_2->setText(query.value(record.indexOf("RESULTAT")).toString());
            ui->lineEdit_recommendation_2->setText(query.value(record.indexOf("RECOMMENDATION")).toString());
            ui->lineEdit_date_2->setText(query.value(record.indexOf("DATE_CREATION")).toString());
            ui->lineEdit_nomentrep_2->setText(query.value(record.indexOf("NOM_ENTREPRISE")).toString());
        }
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("L'ID n'existe pas.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Gestion_Rapport::on_pushButton_modifier_clicked()
{
    QRegularExpression numericRegex("^[0-9]+$");

   //QString test=ui->lineEdit_idrapport_2->text();

        //int id_rap=ui->lineEdit_idrapport_2->text().toInt();
    QString ID_RAPPORT=ui->lineEdit_idrapport_2->text();
    QString ID_AUDITEUR=ui->lineEdit_idauditeur_2->text();
    QString OBJET_RAPPORT=ui->lineEdit_objet_2->text();
    QString RESULTAT=ui->lineEdit_result_2->text();
    QString RECOMMENDATION=ui->lineEdit_recommendation_2->text();
    QString DATE_CREATION=ui->lineEdit_date_2->text();
    QString NOM_ENTREPRISE=ui->lineEdit_nomentrep_2->text();

    int test=r.checkinput(ID_RAPPORT,ID_AUDITEUR,RESULTAT);;
        if (test==1)
        {
          QMessageBox::warning(this, "invalide","Non valid ID RAPPORT.\n"
                                                 "Please enter a valid integer for ID RAPPORT containing 8 caracters \n"
                                                 "Click Cancel to exit.");
            return;
        }
        if (test==2)
        {
            QMessageBox::warning(this, "invalide","Non valid ID AUDITEUR.\n"
                                                  "Please enter a valid integer for ID AUDITEUR containing 8 caracters \n"
                                                  "Click Cancel to exit.");
            return;
        }
        if (test==3)
        {
            QMessageBox::warning(this, "invalide","Non valid RESULT.\n"
                                                      "(valide/semi valide/non valide) \n"
                                                      "Click Cancel to exit.");
             return;
        }                               
        if (!numericRegex.match(ID_RAPPORT).hasMatch())
        {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for ID RAPPORT containing only numbers.");
            return;
        }
        if (!numericRegex.match(ID_AUDITEUR).hasMatch())
        {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for ID AUDITEUR containing only numbers.");
            return;
        }

    Rapport r(ID_RAPPORT,ID_AUDITEUR,DATE_CREATION,OBJET_RAPPORT,RESULTAT,RECOMMENDATION,NOM_ENTREPRISE);
    bool test2=r.update(ID_RAPPORT,ID_AUDITEUR,DATE_CREATION,OBJET_RAPPORT,RESULTAT,RECOMMENDATION,NOM_ENTREPRISE);
        if(test2)
        {
            show_table();
            clear_form();
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("update successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not OK"),
                        QObject::tr("update not successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

////////////////Delete
void Gestion_Rapport::on_pushButton_supprimer_clicked()
{
    //int id_rap = ui ->lineEdit_supp->text().toInt();
    QString ID_RAPPORT=ui->lineEdit_supp->text();
    bool test=r.checkid(ID_RAPPORT);
    if(test)
    {
        bool test2=r.supprimer(ID_RAPPORT);
        if(test2)
        {
            show_table();
            QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectuée\n" "Click cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::information(nullptr,QObject::tr("not OK"),QObject::tr("Suppression non effectuée\n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("L'ID n'existe pas.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}




/////////////////////////////////////*********************Metiers***********************//////////////////////////////////////////
///////////Recherche
void Gestion_Rapport::on_rech_textChanged(const QString &text)
{
    proxy->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
}

void Gestion_Rapport::on_comboBox_rech_currentIndexChanged(int index)
{
    proxy->setFilterKeyColumn(index);
}

///////////Trier
void Gestion_Rapport::on_comboBox_trie_currentIndexChanged(int index)
{
    Qt::SortOrder sortOrder = (ui->checkBox->checkState() == Qt::Checked) ? Qt::DescendingOrder : Qt::AscendingOrder;
    proxy->sort(index, sortOrder);

}


///////////Statistique
/// Bar chart
void Gestion_Rapport::on_pushButton_stat_resultat_clicked()
{

    QSqlQuery q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12;
    qreal /*tot1=0,*/c1=0,c2=0,c3=0;
    qreal /*tot2=0,*/c4=0,c5=0,c6=0;
    qreal /*tot3=0,*/c7=0,c8=0,c9=0;
    qreal totmax;
     ///// Janvier
    q1.prepare("SELECT * FROM RAPPORTS_AUDITS where DATE_CREATION LIKE '%/01/%'");
    q1.exec();

    q2.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' and DATE_CREATION LIKE '%/01/%'");
    q2.exec();

    q3.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='semi valide' and DATE_CREATION LIKE '%/01/%'");
    q3.exec();

    q4.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='non valide' and DATE_CREATION LIKE '%/01/%' ");
    q4.exec();

    ///February
    q5.prepare("SELECT * FROM RAPPORTS_AUDITS where DATE_CREATION LIKE '%/02/%'");
    q5.exec();

    q6.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' and DATE_CREATION LIKE '%/02/%'");
    q6.exec();

    q7.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='semi valide' and DATE_CREATION LIKE '%/02/%'");
    q7.exec();

    q8.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='non valide' and DATE_CREATION LIKE '%/02/%' ");
    q8.exec();

    ////March
    q9.prepare("SELECT * FROM RAPPORTS_AUDITS where DATE_CREATION LIKE '%/03/%'");
    q9.exec();

    q10.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' and DATE_CREATION LIKE '%/03/%'");
    q10.exec();

    q11.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='semi valide' and DATE_CREATION LIKE '%/03/%'");
    q11.exec();

    q12.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='non valide' and DATE_CREATION LIKE '%/03/%' ");
    q12.exec();

    //while (q1.next()){tot1++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
   // while (q5.next()){tot2++;}
    while (q6.next()){c4++;}
    while (q7.next()){c5++;}
    while (q8.next()){c6++;}
    //while (q9.next()){tot3++;}
    while (q10.next()){c7++;}
    while (q11.next()){c8++;}
    while (q12.next()){c9++;}

    totmax=std::max({c1,c2,c3,c4,c5,c6,c7,c8,c9});

    /*c1=c1/tot1;
    c2=c2/tot1;
    c3=c3/tot1;
    c4=c4/tot2;
    c5=c5/tot2;
    c6=c6/tot2;
    c7=c7/tot3;
    c8=c8/tot3;
    c9=c9/tot3;*/

            QBarSet *set0 = new QBarSet("valide");
            QBarSet *set1 = new QBarSet("semi valide");
            QBarSet *set2 = new QBarSet("non valide");

            *set0 << c1 << c4 << c7;
            *set1 << c2 << c5 << c8;
            *set2 << c3 << c6 << c9;


            QBarSeries *series = new QBarSeries();
            series->append(set0);
            series->append(set1);
            series->append(set2);


            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Bilan de 1/2 Semestre");
            QFont titleFont("Bell MT", 18, QFont::Bold);
            chart->setTitleFont(titleFont);
            chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignBottom);


            QStringList categories;
            categories << "Jan" << "Feb" << "Mar" ;
            QBarCategoryAxis *axisX = new QBarCategoryAxis();
            QFont titleFontX("Bell MT", 13, QFont::Bold);
            axisX->append(categories);
            axisX->setTitleText("Months");
            axisX->setTitleFont(titleFontX);
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);

            QValueAxis *axisY = new QValueAxis();
            QFont titleFontY("Bell MT", 13, QFont::Bold);
            axisY->setTitleText("Numbers");
            axisY->setTitleFont(titleFontY);
            axisY->setRange(0,totmax+1);
            axisY->setTickCount(totmax+2);
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);

    if (!chartView)
    {
        chartView = new QChartView(chart,ui->label_stat);
        chartView->chart()->setTheme(QChart::ChartThemeBlueIcy);
        chartView->chart()->legend()->setFont(QFont("Bell MT", 12));
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(400,400);
        QVBoxLayout *layout = new QVBoxLayout(ui->label_stat);
        layout->addWidget(chartView, 0, Qt::AlignCenter);
        chartView->show();
    }
    else
    {
        //chartView->setChart(chart);
        chartView->chart()->setTheme(QChart::ChartThemeBlueIcy);
        chartView->chart()->legend()->setFont(QFont("Bell MT", 12));
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(400,400);
        QVBoxLayout *layout = new QVBoxLayout(ui->label_stat);
        layout->addWidget(chartView, 0, Qt::AlignCenter);
        chartView->update();

    }

    if (chartView1) {
        chartView1->hide();
        chartView1=nullptr;
    }
}

void Gestion_Rapport::on_pushButton_stat_entreprise_clicked()
{

    QSqlQuery q1,q2,q3,q4,q5,q6;
    qreal tot=0,c1=0,c2=0,c3=0,c4=0,c5=0;


    q1.prepare("SELECT * FROM RAPPORTS_AUDITS where RESULTAT='valide'");
    q1.exec();

    q2.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' and NOM_ENTREPRISE ='rubanerie'");
    q2.exec();

    q3.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' and NOM_ENTREPRISE ='conformatex'");
    q3.exec();

    q4.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' and NOM_ENTREPRISE ='azurex'");
    q4.exec();

    q5.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' and NOM_ENTREPRISE ='sartex'");
    q5.exec();

    q6.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' and NOM_ENTREPRISE ='medianet'");
    q6.exec();


    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    while (q5.next()){c4++;}
    while (q6.next()){c5++;}

    c1 = (c1 / tot) * 100.0;
    c2 = (c2 / tot) * 100.0;
    c3 = (c3 / tot) * 100.0;
    c4 = (c4 / tot) * 100.0;
    c5 = (c5 / tot) * 100.0;

    QPieSeries *series = new QPieSeries();
    series->append("rubanerie " + QString::number(c1, 'f', 2) + "%", c1);
    series->append("conformatex " + QString::number(c2, 'f', 2) + "%", c2);
    series->append("azurex " + QString::number(c3, 'f', 2) + "%", c3);
    series->append("sartex " + QString::number(c4, 'f', 2) + "%", c4);
    series->append("medianet " + QString::number(c5, 'f', 2) + "%", c5);

    if (!chartView1)
    {
        QChart *chart1 = new QChart();
        chart1->addSeries(series);
        chart1->setTitle("Best enteprise");
        QFont titleFont("Bell MT", 18, QFont::Bold);
        chart1->setTitleFont(titleFont);
        chart1->setAnimationOptions(QChart::SeriesAnimations);
        chart1->legend()->setVisible(true);
        chart1->legend()->setAlignment(Qt::AlignRight);


        chartView1 = new QChartView(chart1,ui->label_stat);
        chartView1->chart()->setTheme(QChart::ChartThemeBlueIcy);
        chartView1->chart()->legend()->setFont(QFont("Bell MT", 12));
        chartView1->setRenderHint(QPainter::Antialiasing);
        QVBoxLayout *layout = new QVBoxLayout(ui->label_stat);
        layout->addWidget(chartView, 0, Qt::AlignCenter);
        chartView1->setMinimumSize(400,400);
        chartView1->show();
    }else
    {
        //chartView1->setChart(chart1);
        chartView1->chart()->setTheme(QChart::ChartThemeBlueIcy);
        chartView1->chart()->legend()->setFont(QFont("Bell MT", 12));
        chartView1->setRenderHint(QPainter::Antialiasing);
        QVBoxLayout *layout = new QVBoxLayout(ui->label_stat);
        layout->addWidget(chartView, 0, Qt::AlignCenter);
        chartView1->setMinimumSize(400,400);
        chartView1->update();
    }
    if (chartView)
    {
        chartView->hide();
        chartView=nullptr;
    }
}
/////////////export pdf
void Gestion_Rapport::on_pushButton_pdf_clicked()
{
        QString idToExport = ui->lineEdit_pdf->text();
        Rapport r;
        QString details = r.getDetailsByID(idToExport);

        if (!details.isEmpty()) {
            QString fileName = "Rapport_details_" + idToExport + ".pdf";

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
            qDebug() << "Error: Rapport not found or an error occurred.";
            QMessageBox::critical(nullptr, QObject::tr("Export Error"),
                                  QObject::tr("Rapport not found or an error occurred."),
                                  QMessageBox::Ok);
        }

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Cryptage
void Gestion_Rapport::showPasswordDialog()
{
        bool passwordCorrect = false;

        while (!passwordCorrect)
        {
            QString password = getPasswordFromUser();
            if (password.isEmpty())
            {
                close();
                return;
            }
            if (checkPassword(password))
            {
                show();
                passwordCorrect = true;
            }
            else
            {
                QMessageBox::warning(this, "Mot de passe incorrect", "Le mot de passe est incorrect. Veuillez réessayer.");
            }
        }
}
bool Gestion_Rapport::checkPassword(const QString &password)
{
        QString storedPassword = "123456";
        return (password == storedPassword);
}
QString Gestion_Rapport::getPasswordFromUser()
{
        return QInputDialog::getText(this, "Mot de passe", "Entrez votre mot de passe :", QLineEdit::Password);
}
QByteArray Gestion_Rapport::encrypt(const QByteArray &data,QByteArray key)
{
        QByteArray encryptedData = data;
        for (int i = 0; i < encryptedData.size(); ++i)
        {
            encryptedData[i] = encryptedData[i] ^ key[i % key.size()];
        }
        return encryptedData;
}

QByteArray Gestion_Rapport::decrypt(const QByteArray &data, const QByteArray &key)
{
        QByteArray decryptedData = data;
        for (int i = 0; i < decryptedData.size(); ++i)
        {
            decryptedData[i] = decryptedData[i] ^ key[i % key.size()];
        }
        return decryptedData;
}


void Gestion_Rapport::on_pushButton_cryptage_clicked()
{
        QString password = getPasswordFromUser();
        if (!password.isEmpty())
        {
            QByteArray key = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
            if (key.isEmpty())
            {
                qDebug() << "Erreur lors de la génération de la clé à partir du mot de passe.";
                return;
            }
            if(proxy)
            {
                QStandardItemModel* standardModel = new QStandardItemModel();

                int rowCount = proxy->rowCount();
                int columnCount = proxy->columnCount();
                standardModel->setRowCount(rowCount);
                standardModel->setColumnCount(columnCount);

                for (int row = 0; row < rowCount; ++row)
                {
                    for (int col = 0; col < columnCount; ++col)
                    {
                        QModelIndex proxyIndex = proxy->index(row, col);
                        QModelIndex standardIndex = standardModel->index(row, col);
                        QVariant data = proxy->data(proxyIndex);
                        standardModel->setData(standardIndex, data);
                    }
                }

                ui->tableView->setModel(standardModel);
                delete proxy;
                proxy = nullptr;

                if (!standardModel)
                {
                    return;
                }
                for (int row = 0; row < standardModel->rowCount(); ++row)
                {
                    for (int col = 0; col < standardModel->columnCount(); ++col)
                    {
                        QModelIndex index = standardModel->index(row, col);
                        QByteArray originalData = standardModel->data(index).toByteArray();
                        QByteArray encryptedData = encrypt(originalData, key);
                        standardModel->setData(index, encryptedData);
                    }
                }
            }
            /*if (proxy)
            {
                for (int row = 0; row < standardModel->rowCount(); ++row)
                {
                    for (int col = 0; col < standardModel->columnCount(); ++col)
                    {
                        QModelIndex index = standardModel->index(row, col);
                        QByteArray originalData = standardModel->data(index).toByteArray();
                        QByteArray encryptedData = encrypt(originalData, key);
                        standardModel->setData(index, encryptedData);
                    }
                }
                QSortFilterProxyModel* proxy = new QSortFilterProxyModel();
                proxy->setSourceModel(standardModel);
                ui->tableView->setModel(proxy);
                delete standardModel;
                standardModel = nullptr;

            }*/
        }
        /*
         * QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(ui->tableView->model());
        if (!proxyModel) {
            return; // Handle the case where the proxy model is not set
        }

        QAbstractItemModel *sourceModel = proxyModel->sourceModel();
        if (!sourceModel) {
            return; // Handle the case where the source model is not set
        }
        QByteArray key = motDePasseStockeHash;

        // Iterate through the items of the source model and encrypt each cell
        for (int row = 0; row < sourceModel->rowCount(); ++row) {
            for (int col = 0; col < sourceModel->columnCount(); ++col) {
            QModelIndex index = sourceModel->index(row, col);
            QString cellData = sourceModel->data(index).toString();
            QByteArray encryptedData = encrypt(cellData.toUtf8(), key);
            sourceModel->setData(index, encryptedData);
            }
        }*/
}


void Gestion_Rapport::on_pushButton_decryptage_clicked()
{
        QString password = getPasswordFromUser();
        if (!password.isEmpty())
        {
            QByteArray key = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
            if (key.isEmpty())
            {
                qDebug() << "Erreur lors de la génération de la clé à partir du mot de passe.";
                return;
            }
            if(standardModel)
            {
                for (int row = 0; row < standardModel->rowCount(); ++row)
                {
                    for (int col = 0; col < standardModel->columnCount(); ++col)
                    {
                        QModelIndex index = standardModel->index(row, col);
                        QByteArray encryptedData = standardModel->data(index).toByteArray();
                        QByteArray decryptedData = decrypt(encryptedData, key);
                        standardModel->setData(index, decryptedData);

                    }
                }
                /*QSortFilterProxyModel* proxy = new QSortFilterProxyModel();
                proxy->setSourceModel(standardModel);
                ui->tableView->setModel(proxy);
                delete standardModel;
                standardModel = nullptr;*/


            }
        }
        /*QString password = getPasswordFromUser();
        if (!password.isEmpty()) {
            // Utilisez la clé dérivée du mot de passe pour le chiffrement
            QByteArray key = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

            QStandardItemModel* sourceModel = qobject_cast<QStandardItemModel*>(proxy->sourceModel());
            if (!sourceModel) {
            return; // Handle the case where the source model is not set
            }
            for (int row = 0; row < sourceModel->rowCount(); ++row) {
            for (int col = 0; col < sourceModel->columnCount(); ++col) {
                QModelIndex index = sourceModel->index(row, col);
                QByteArray encryptedData = sourceModel->data(index).toByteArray();
                QByteArray decryptedData = decrypt(encryptedData, key);
                sourceModel->setData(index, decryptedData);
                if (!sourceModel->setData(index, encryptedData)) {
                    qDebug() << "Error setting encrypted data at index: " << index;
                }
            }
            }
        }*/
        /*
         * bool ok;
        QString motDePasse = QInputDialog::getText(this, "Vérification du mot de passe", "Entrez votre mot de passe :", QLineEdit::Password, "", &ok);

            if (ok && !motDePasse.isEmpty()) {
            QByteArray motDePasseHash = QCryptographicHash::hash(motDePasse.toUtf8(), QCryptographicHash::Sha256);

            // Use the hashed password as the decryption key
            QByteArray key = motDePasseHash;

            if (motDePasseHash == motDePasseStockeHash) {
            QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(ui->tableView->model());
            if (!proxyModel) {
                return;
            }

            QAbstractItemModel *sourceModel = proxyModel->sourceModel();
            if (!sourceModel) {
                return;
            }

            // Iterate through the items of the source model and decrypt each cell
            for (int row = 0; row < sourceModel->rowCount(); ++row) {
                for (int col = 0; col < sourceModel->columnCount(); ++col) {
                    QModelIndex index = sourceModel->index(row, col);
                    QByteArray encryptedData = sourceModel->data(index).toByteArray();
                    QByteArray decryptedData = decrypt(encryptedData, key);
                    sourceModel->setData(index, decryptedData);
                }
            }
            ui->tableView->viewport()->update();
            } else {
            QMessageBox::warning(this, "Mot de passe incorrect", "Mot de passe incorrect. Veuillez réessayer.");
            }
        }*/
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////drillDown piechart
/*void Gestion_Rapport::show_chart(){
    chart ch;
    DrilldownChart *chart = new DrilldownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QPieSeries *numberSeries = new QPieSeries();
    numberSeries->setName("Accreditation par ID Entreprise - All");
    const QStringList names = ch.getEntrepriseIDs();
    const QMap<QString,QString>nbr_accred =ch.getNumbreAccreditations();
    const QStringList etats=ch.getEtats();
    for (auto it = nbr_accred.begin(); it != nbr_accred.end(); ++it) {
        const QString &name = it.key();
        const QString &accreditation = it.value();

        *numberSeries << new DrilldownSlice(accreditation.toDouble(),"ID : "+name, numberSeries);
    }

    chart->changeSeries(numberSeries);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
}
void Gestion_Rapport::on_pushButton_stat_entreprise_clicked()
{
    QSqlQuery q;
    qreal tot = 0;
    QMap<QString, QMap<QString, qreal>> data;  // Entreprise -> Résultat -> Count

    q.prepare("SELECT NOM_ENTREPRISE, RESULTAT, COUNT(*) FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' GROUP BY NOM_ENTREPRISE, RESULTAT");
    q.exec();

    while (q.next()) {
        QString entreprise = q.value(0).toString();
        QString resultat = q.value(1).toString();
        qreal count = q.value(2).toDouble();

        data[entreprise][resultat] = count;
        tot += count;
    }

    QPieSeries *series = new QPieSeries();

    for (const QString &entreprise : data.keys()) {
        qreal totalEntreprise = 0;

        // Create a series for each entreprise
        QPieSeries *entrepriseSeries = new QPieSeries();

        for (const QString &resultat : data[entreprise].keys()) {
            qreal count = data[entreprise][resultat];
            qreal percentage = (count / tot) * 100.0;

            entrepriseSeries->append(resultat + " " + QString::number(percentage, 'f', 2) + "%", count);
            totalEntreprise += count;
        }

        qreal percentageEntreprise = (totalEntreprise / tot) * 100.0;

        series->append(entreprise + " " + QString::number(percentageEntreprise, 'f', 2) + "%", totalEntreprise);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Best enterprise");
    QFont titleFont("Bell MT", 18, QFont::Bold);
    chart->setTitleFont(titleFont);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    chartView = new QChartView(chart, ui->label_stat);
    chartView->chart()->setTheme(QChart::ChartThemeBlueIcy);
    chartView->chart()->legend()->setFont(QFont("Bell MT", 12));
    chartView->setRenderHint(QPainter::Antialiasing);
    QVBoxLayout *layout = new QVBoxLayout(ui->label_stat);
    layout->addWidget(chartView, 0, Qt::AlignCenter);
    chartView->setMinimumSize(400, 400);

    connect(series, &QPieSeries::clicked, this, &Gestion_Rapport::on_handlePieSeries_Clicked);
    chartView->show();
}

void Gestion_Rapport::on_handlePieSeries_Clicked(const QString &label)
{

    // Split the label to extract entreprise and percentage
        QStringList parts = label.split(" ");
        QString entreprise = parts[0];

        // Execute another query to get more detailed data for the selected entreprise
        QSqlQuery detailedQuery;
        detailedQuery.prepare("SELECT RESULTAT, COUNT(*) FROM RAPPORTS_AUDITS WHERE RESULTAT='valide' AND NOM_ENTREPRISE=:entreprise GROUP BY RESULTAT");
        detailedQuery.bindValue(":entreprise", entreprise);
        detailedQuery.exec();

        QPieSeries *detailedSeries = new QPieSeries();

        while (detailedQuery.next()) {
            QString resultat = detailedQuery.value(0).toString();
            qreal count = detailedQuery.value(1).toDouble();
            detailedSeries->append(resultat, count);
        }

        // Create a new chart for the detailed series
        QChart *detailedChart = new QChart();
        detailedChart->addSeries(detailedSeries);
        detailedChart->setTitle("Details for " + entreprise);
        QFont titleFont("Bell MT", 18, QFont::Bold);
        detailedChart->setTitleFont(titleFont);
        detailedChart->setAnimationOptions(QChart::AllAnimations);
        detailedChart->legend()->setVisible(true);
        detailedChart->legend()->setAlignment(Qt::AlignRight);

        // Create a new QChartView for the detailed chart
        QChartView *detailedChartView = new QChartView(detailedChart);
        detailedChartView->setRenderHint(QPainter::Antialiasing);
        detailedChartView->setMinimumSize(400, 400);

        // Replace the existing chartView with the detailedChartView
        ui->label_stat->layout()->replaceWidget(chartView, detailedChartView);
        chartView = detailedChartView;

        // Connect the series in the detailed chart to handle further drilldown
        connect(detailedSeries, &QPieSeries::clicked, this, &Gestion_Rapport::on_handlePieSeries_Clicked);
}*/










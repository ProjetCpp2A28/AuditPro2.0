#include "welcome.h"
#include "ui_welcome.h"
#include "smtp.h"
#include "sms.h"
#include "chart.h"

#include <QMessageBox>
#include <QIntValidator>
#include <QtDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QDialog>
#include <iostream>
#include <QSerialPort>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QLayout>
#include <QRegularExpression>
#include <QInputDialog>
#include <QThread>
#include <QUrlQuery>


welcome::welcome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    show_table_rap();
    ui->widget_employee->setVisible(false);
    ui->widget_rapport->setVisible(false);
    ui->widget_entreprise->setVisible(false);
    ui->widget_reclamation->setVisible(false);
    ui->widget_reglement->setVisible(false);
    //ui->widget_accreditation->setVisible(false);
    //////////////////////////////////////////////////////////////////////////////////////employee
    ui->le_id->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_mdp->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_num->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_id_sup->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_id_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_mdp_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_num_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_export_emp->setValidator(new QIntValidator(0, 99999999, this));
    //////////////////////////////////////////////////////////////////////////////////////Rapport
    show_table_emp();
    chartView=nullptr;
    chartt=nullptr;
    chartView1=nullptr;
    chartt1=nullptr;

    ui->lineEdit_idrapport->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_idrapport_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_idauditeur->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_idauditeur_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_check->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_supp->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_id->setValidator(new QIntValidator(0, 99999999, this));
    ///////////////////////////////////////////////////////////////////////////////////Entreprise
    show_table_ent();
    ui->id_Entreprise->setValidator(new QIntValidator(0, 99999999, this));
    ui->num_tel->setValidator(new QIntValidator(0, 99999999, this));
    ui->id_Entreprise_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->num_tel_2->setValidator(new QIntValidator(0, 99999999, this));
    //////////////////////////////////////////////////////////////////////////////////Reclamation
    show_table_rec();
    ui->le_id_rec->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_id_rec_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->id_supp->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_export_rec->setValidator(new QIntValidator(0, 99999999, this));
    //////////////////////////////////////////////////////////////////////////////////Reclamation
    ui->table->setModel(Reg.afficher());
    for(int col=0;col<7;col++)
        ui->table->setColumnWidth(col,120);
    ui->historique_view->setModel(Reg.afficher_his());

    ui->id-> setValidator (new QIntValidator(0,999999, this ));

    ui->type->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z]*")));
    ui->description->setValidator(new QRegularExpressionValidator(QRegularExpression("[A-Za-z]*")));


    ui->comboBox_validation->addItem("oui");
    ui->comboBox_validation->addItem("non");
    ui->TricomboBoxReglement->addItem("id");
    ui->TricomboBoxReglement->addItem("type");
    ui->TricomboBoxReglement->addItem("description");
    ui->TricomboBoxReglement->addItem("date");
    ui->TricomboBoxReglement->addItem("validation");

    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }

}

welcome::~welcome()
{
    delete ui;
}

void welcome::on_pushButton_rapport_clicked()
{
    ui->widget_rapport->setVisible(true);
    ui->widget_employee->setVisible(false);
    ui->widget_entreprise->setVisible(false);
    ui->widget_reglement->setVisible(false);
    //ui->widget_accreditation->setVisible(false);
    ui->widget_reclamation->setVisible(false);

}

void welcome::on_pushButton_employee_clicked()
{
    ui->widget_rapport->setVisible(false);
    ui->widget_employee->setVisible(true);
    ui->widget_entreprise->setVisible(false);
    ui->widget_reglement->setVisible(false);
    //ui->widget_accreditation->setVisible(false);
    ui->widget_reclamation->setVisible(false);
}


void welcome::on_pushButton_entreprise_clicked()
{
    ui->widget_rapport->setVisible(false);
    ui->widget_employee->setVisible(false);
    ui->widget_entreprise->setVisible(true);
    ui->widget_reglement->setVisible(false);
    //ui->widget_accreditation->setVisible(false);
    ui->widget_reclamation->setVisible(false);
}

void welcome::on_pushButton_reglement_clicked()
{
    ui->widget_rapport->setVisible(false);
    ui->widget_employee->setVisible(false);
    ui->widget_entreprise->setVisible(false);
    ui->widget_reglement->setVisible(true);
    //ui->widget_accreditation->setVisible(false);
    ui->widget_reclamation->setVisible(false);
}

void welcome::on_pushButton_accred_clicked()
{
    ui->widget_rapport->setVisible(false);
    ui->widget_employee->setVisible(false);
    ui->widget_entreprise->setVisible(false);
    ui->widget_reglement->setVisible(false);
    //ui->widget_accreditation->setVisible(true);
    ui->widget_reclamation->setVisible(false);
}

void welcome::on_pushButton_reclamation_clicked()
{
    ui->widget_rapport->setVisible(false);
    ui->widget_employee->setVisible(false);
    ui->widget_entreprise->setVisible(false);
    ui->widget_reglement->setVisible(false);
    //ui->widget_accreditation->setVisible(false);
    ui->widget_reclamation->setVisible(true);
}


void welcome::on_pushButton_changer_clicked()
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
void welcome::on_pushButton_valide_clicked()
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
void welcome::on_arduino_clicked()
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
/*void welcome::id_existe()
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
void welcome::show_table_rap()
{

    proxy_rap = new QSortFilterProxyModel();
    proxy_rap->setSourceModel(r.afficher());
    proxy_rap->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_rap->setFilterKeyColumn(-1);
    ui->tableView->setModel(proxy_rap);
}

void welcome::clear_form( )
{
    ui->lineEdit_nomentrep->clear();
    ui->lineEdit_idrapport->clear();
    ui->lineEdit_idauditeur->clear();
    ui->lineEdit_objet->clear();
    ui->lineEdit_result->clear();
    ui->lineEdit_recommendation->clear();
    ui->lineEdit_date->clear();
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
void welcome::on_pushButton_ajouter_clicked()
{

    QRegularExpression numericRegex("^[0-9]+$");
    QString ID_RAPPORT=ui->lineEdit_idrapport->text();
    QString ID_AUDITEUR=ui->lineEdit_idauditeur->text();
    QString RESULTAT=ui->lineEdit_result->text();
    QString OBJET_RAPPORT=ui->lineEdit_objet->text();
    QString RECOMMENDATION=ui->lineEdit_recommendation->text();
    QString DATE_CREATION=ui->lineEdit_date->text();
    QString NOM_ENTREPRISE=ui->lineEdit_nomentrep->text();

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
        show_table_rap();
        clear_form();
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Ajout successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(this, QObject::tr("not OK"),
                              QObject::tr("Ajout not successful.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

}

////////////////Read
void welcome::on_pushButton_afficher_clicked()
{
    show_table_rap();
}

////////////////Update
void welcome::on_pushButton_check_clicked()
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
        QMessageBox::critical(this, QObject::tr("not OK"),
                              QObject::tr("L'ID n'existe pas.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

void welcome::on_pushButton_modifier_clicked()
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
        show_table_rap();
        clear_form();
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("update successful.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(this, QObject::tr("not OK"),
                              QObject::tr("update not successful.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}

////////////////Delete
void welcome::on_pushButton_supprimer_clicked()
{
    //int id_rap = ui ->lineEdit_supp->text().toInt();
    QString ID_RAPPORT=ui->lineEdit_supp->text();
    bool test=r.checkid(ID_RAPPORT);
    if(test)
    {
        bool test2=r.supprimer(ID_RAPPORT);
        if(test2)
        {
            show_table_rap();
            QMessageBox::information(this,QObject::tr("OK"),QObject::tr("Suppression effectuée\n" "Click cancel to exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::information(this,QObject::tr("not OK"),QObject::tr("Suppression non effectuée\n" "Click cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(this, QObject::tr("not OK"),
                              QObject::tr("L'ID n'existe pas.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}




/////////////////////////////////////*********************Metiers***********************//////////////////////////////////////////
///////////Recherche
void welcome::on_rech_textChanged(const QString &text)
{
    proxy_rap->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    proxy_emp->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    proxy_ent->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));
    proxy_rec->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));

}
void welcome::on_comboBox_rech_currentIndexChanged(int index)
{
    proxy_rap->setFilterKeyColumn(index);
}

///////////Trier
void welcome::on_comboBox_trie_currentIndexChanged(int index)
{
    Qt::SortOrder sortOrder = (ui->checkBox->checkState() == Qt::Checked) ? Qt::DescendingOrder : Qt::AscendingOrder;
    proxy_rap->sort(index, sortOrder);

}


///////////Statistique
/// Bar chart
void welcome::on_pushButton_stat_resultat_clicked()
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


    QChart *chartt = new QChart();
    chartt->addSeries(series);
    chartt->setTitle("Bilan de 1/2 Semestre");
    QFont titleFont("Bell MT", 18, QFont::Bold);
    chartt->setTitleFont(titleFont);
    chartt->setAnimationOptions(QChart::SeriesAnimations);
    chartt->legend()->setVisible(true);
    chartt->legend()->setAlignment(Qt::AlignBottom);


    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" ;
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    QFont titleFontX("Bell MT", 13, QFont::Bold);
    axisX->append(categories);
    axisX->setTitleText("Months");
    axisX->setTitleFont(titleFontX);
    chartt->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    QFont titleFontY("Bell MT", 13, QFont::Bold);
    axisY->setTitleText("Numbers");
    axisY->setTitleFont(titleFontY);
    axisY->setRange(0,totmax+1);
    axisY->setTickCount(totmax+2);
    chartt->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    if (!chartView)
    {
        chartView = new QChartView(chartt,ui->label_stat);
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

void welcome::on_pushButton_stat_entreprise_clicked()
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
        QChart *chartt1 = new QChart();
        chartt1->addSeries(series);
        chartt1->setTitle("Best enteprise");
        QFont titleFont("Bell MT", 18, QFont::Bold);
        chartt1->setTitleFont(titleFont);
        chartt1->setAnimationOptions(QChart::SeriesAnimations);
        chartt1->legend()->setVisible(true);
        chartt1->legend()->setAlignment(Qt::AlignRight);


        chartView1 = new QChartView(chartt1,ui->label_stat);
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
void welcome::on_pushButton_pdf_clicked()
{

    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    filePath = QDir(filePath).filePath("pdf/listeRapport.pdf");
    QPdfWriter pdf(filePath);

    QPainter painter(&pdf);
    int i = 4100;


    QColor dateColor(0x4a5bcf);
    painter.setPen(dateColor);

    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();
    painter.drawText(8400,250,cd.toString("Tunis"));
    painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

    QColor titleColor(0x341763);
    painter.setPen(titleColor);
    painter.setFont(QFont("Montserrat SemiBold", 25));

    painter.drawText(3000,2700,"Liste des Rapports");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    //painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3300,9400,500);

    painter.setFont(QFont("Montserrat SemiBold", 10));

    painter.drawText(500,3600,"ID_RAPPORT");
    painter.drawText(1800,3600,"OBJET_RAPPORT");
    painter.drawText(3500,3600,"ID_AUDITEUR");
    painter.drawText(4800,3600,"DATE_CREATION");
    painter.drawText(6500,3600,"RESULTAT");
    painter.drawText(8000,3600,"ENTREPRISE");

    painter.setFont(QFont("Montserrat", 10));
    painter.drawRect(100,3300,9400,9000);

    QSqlQuery query;
    query.prepare("select * from RAPPORTS_AUDITS");
    query.exec();
    int y=4300;
    while (query.next())
    {
        painter.drawLine(100,y,9490,y);
        y+=500;
        painter.drawText(500,i,query.value(0).toString());
        painter.drawText(1800,i,query.value(1).toString());
        painter.drawText(3500,i,query.value(2).toString());
        painter.drawText(4800,i,query.value(3).toString());
        painter.drawText(6500,i,query.value(4).toString());
        painter.drawText(8000,i,query.value(6).toString());



        i = i + 500;
    }
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                             QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);


}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Cryptage
void welcome::showPasswordDialog()
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
bool welcome::checkPassword(const QString &password)
{
    QString storedPassword = "123456";
    return (password == storedPassword);
}
QString welcome::getPasswordFromUser()
{
    return QInputDialog::getText(this, "Mot de passe", "Entrez votre mot de passe :", QLineEdit::Password);
}
QByteArray welcome::encrypt(const QByteArray &data,QByteArray key)
{
    QByteArray encryptedData = data;
    for (int i = 0; i < encryptedData.size(); ++i)
    {
        encryptedData[i] = encryptedData[i] ^ key[i % key.size()];
    }
    return encryptedData;
}

QByteArray welcome::decrypt(const QByteArray &data, const QByteArray &key)
{
    QByteArray decryptedData = data;
    for (int i = 0; i < decryptedData.size(); ++i)
    {
        decryptedData[i] = decryptedData[i] ^ key[i % key.size()];
    }
    return decryptedData;
}


void welcome::on_pushButton_cryptage_clicked()
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
        if(proxy_rap)
        {
            QStandardItemModel* standardModel = new QStandardItemModel();

            int rowCount = proxy_rap->rowCount();
            int columnCount = proxy_rap->columnCount();
            standardModel->setRowCount(rowCount);
            standardModel->setColumnCount(columnCount);

            for (int row = 0; row < rowCount; ++row)
            {
                for (int col = 0; col < columnCount; ++col)
                {
                    QModelIndex proxyIndex = proxy_rap->index(row, col);
                    QModelIndex standardIndex = standardModel->index(row, col);
                    QVariant data = proxy_rap->data(proxyIndex);
                    standardModel->setData(standardIndex, data);
                }
            }

            ui->tableView->setModel(standardModel);
            delete proxy_rap;
            proxy_rap = nullptr;

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


void welcome::on_pushButton_decryptage_clicked()
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
//***************************************************************************************************************************************************************
//*************************************************************************************************************************************************  Employe ****
//***************************************************************************************************************************************************************

void welcome::show_table_emp()
{

    proxy_emp = new QSortFilterProxyModel();
    proxy_emp->setSourceModel(E.afficher());
    proxy_emp->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_emp->setFilterKeyColumn(-1);
    ui->tab_emp->setModel(proxy_emp);
}

void welcome::on_le_adresse_editingFinished()
{


    QString ADRESSE_MAIL = ui->la_adresse->text();


    if (!ADRESSE_MAIL.endsWith("@gmail.com", Qt::CaseInsensitive))
    {

        QMessageBox::critical(this, QObject::tr("Invalid Email"),
                              QObject::tr("Please enter a valid Gmail email address."),
                              QMessageBox::Cancel);
        ui->la_adresse->clear();
    }
}

void welcome::on_pb_ajouter_clicked()
{

    QString ID = ui->le_id->text();
    QString NUMERO_TELEPHONE = ui->le_num->text();
    QString MDP = ui->le_mdp->text();
    QString NOM = ui->le_nom->text();
    QString ADRESSE_MAIL = ui->la_adresse->text();
    QString DEPARTEMENT = ui->comboBox->currentText();


    if (!ADRESSE_MAIL.endsWith("@gmail.com", Qt::CaseInsensitive))
    {

        QMessageBox::critical(this, QObject::tr("Invalid Email"),
                              QObject::tr("Please enter a valid Gmail email address."),
                              QMessageBox::Cancel);
        ui->la_adresse->clear();
        return;
    }


    employe E(ID, NUMERO_TELEPHONE, MDP, NOM, ADRESSE_MAIL, DEPARTEMENT);
    bool test = E.ajouter();

    if (test)
    {
        show_table_emp();
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Ajout effectue\n"
                                             "click cancel to exit."));

    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectue\n"
                                          "click cancel to exit."));
    }

}

void welcome::on_pb_sup_clicked()
{
    employe E1; E1.setid(ui->le_id_sup->text());
    bool test=E1.supprimer(E1.getID());
    QMessageBox msgBox;
    if (test)
    {
        QMessageBox::information(this, QObject::tr("Suppression"),
                              QObject::tr("Suppression avec succes\n"
                                          "click cancel to exit."));
        show_table_emp();
    }
    else
        QMessageBox::critical(this, QObject::tr("Suppression"),
                              QObject::tr("Echec de suppresion\n"
                                          "click cancel to exit."));


}

void welcome::on_pb_modifier_clicked()
{

    QString ID = ui->le_id_2->text();
    QString NUMERO_TELEPHONE = ui->le_num_2->text();
    QString MDP = ui->le_mdp_2->text();
    QString NOM = ui->le_nom_2->text();
    QString ADRESSE_MAIL = ui->la_adresse_2->text();
    QString DEPARTEMENT = ui->comboBox_2->currentText();


    employe E;
    bool test = E.update(ID, NUMERO_TELEPHONE, MDP, NOM, ADRESSE_MAIL, DEPARTEMENT);

    if (test)
    {
        show_table_emp();
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Modifier effectue\n"
                                             "click cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Modifier non effectue\n"
                                          "click cancel to exit."), QMessageBox::Cancel);
    }
}


void welcome::on_reach_currentIndexChanged(int index)
{
     proxy_emp->setFilterKeyColumn(index);
}

/*void welcome::on_lineEdit_textChanged(const QString &text)
{
     proxy->setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::FixedString));
}
*/
void welcome::on_reach_2_currentIndexChanged(int index)
{
    Qt::SortOrder sortOrder = (ui->checkBox->checkState() == Qt::Checked) ? Qt::DescendingOrder : Qt::AscendingOrder;
    proxy_emp->sort(index, sortOrder);

}



/*void welcome::on_pushButton_clicked()
{
    QString enteredID = ui->le_id_5->text();
    QString enteredMDP = ui->le_id_6->text();

    if (E.authenticate(enteredID, enteredMDP)) {

        E.resetLoginAttempts();
        QMessageBox::information(nullptr, QObject::tr("Login Successful"),
                                 QObject::tr("Welcome!"), QMessageBox::Ok);

        alogin a;
        a.setModal(true);
        a.exec();


    } else {

        QMessageBox::critical(nullptr, QObject::tr("Login Failed"),
                              QObject::tr("Invalid ID or password. Please try again."), QMessageBox::Ok);
        qDebug() << "Failed login attempts: " << E.getLoginAttempts();
    }
}*/



void welcome::on_pushButton_2_clicked()
{
    QSqlQuery q1,q2,q3,q4, q5,q6, q7;
    qreal tot=0,c1=0,c2=0,c3=0, c4=0, c5=0, c6=0;

    q1.prepare("SELECT * FROM EMPLOYES");
    q1.exec();

    q2.prepare("SELECT * FROM EMPLOYES WHERE DEPARTEMENT='g.employee'");
    q2.exec();

    q3.prepare("SELECT * FROM EMPLOYES WHERE DEPARTEMENT='g.rapports'");
    q3.exec();

    q4.prepare("SELECT * FROM EMPLOYES WHERE DEPARTEMENT='g.entreprises'");
    q4.exec();

    q5.prepare("SELECT * FROM EMPLOYES WHERE DEPARTEMENT='g.reglement'");
    q5.exec();

    q6.prepare("SELECT * FROM EMPLOYES WHERE DEPARTEMENT='g.accreditation'");
    q6.exec();

    q7.prepare("SELECT * FROM EMPLOYES WHERE DEPARTEMENT='g.reclamations'");
    q7.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    while (q5.next()){c4++;}
    while (q6.next()){c5++;}
    while (q7.next()){c6++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;
    c4=c4/tot;
    c5=c5/tot;
    c6=c6/tot;


    // Assign names to the set of bars used
    QBarSet *set0 = new QBarSet("g.employee");
    QBarSet *set1 = new QBarSet("g.rapports");
    QBarSet *set2 = new QBarSet("g.entreprises");
    QBarSet *set3 = new QBarSet("g.reglement");
    QBarSet *set4 = new QBarSet("g.l'accreditation ");
    QBarSet *set5 = new QBarSet("g.reclamations");


    // Assign values for each bar
    *set0 << c1;
    *set1 << c2;
    *set2 << c3;
    *set3 << c4;
    *set4 << c5;
    *set5 << c6;



    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);


    // Used to define the bar chart to display, title
    // legend,
    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);


    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();



    // 1. Bar chart
    chart->setAxisX(axis, series);

    // Used to change the palette
    QPalette pal = qApp->palette();

    // Change the color around the chart widget and text
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));

    // Apply palette changes to the application
    qApp->setPalette(pal);


    // Used to display the chart
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400,400);

    chartView->show();
}
void welcome::on_pushButton_3_clicked()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    filePath = QDir(filePath).filePath("pdf/listeEmployee.pdf");
    QPdfWriter pdf(filePath);

    QPainter painter(&pdf);
    int i = 4100;


    QColor dateColor(0x4a5bcf);
    painter.setPen(dateColor);

    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();
    painter.drawText(8400,250,cd.toString("Tunis"));
    painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

    QColor titleColor(0x341763);
    painter.setPen(titleColor);
    painter.setFont(QFont("Montserrat SemiBold", 25));

    painter.drawText(3000,2700,"Liste des Employes");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    //painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3300,9400,500);

    painter.setFont(QFont("Montserrat SemiBold", 10));

    painter.drawText(500,3600,"ID");
    painter.drawText(1800,3600,"NOM");
    painter.drawText(3000,3600,"ADRESSE MAIL");
    painter.drawText(5000,3600,"MDP");
    painter.drawText(6500,3600,"DEPARTEMENT");
    painter.drawText(8000,3600,"N°TELEPHONE");

    painter.setFont(QFont("Montserrat", 10));
    painter.drawRect(100,3300,9400,9000);

    QSqlQuery query;
    query.prepare("select * from EMPLOYES");
    query.exec();
    int y=4300;
    while (query.next())
    {
        painter.drawLine(100,y,9490,y);
        y+=500;
        painter.drawText(500,i,query.value(0).toString());
        painter.drawText(1800,i,query.value(1).toString());
        painter.drawText(3000,i,query.value(2).toString());
        painter.drawText(5000,i,query.value(3).toString());
        painter.drawText(6500,i,query.value(4).toString());
        painter.drawText(8000,i,query.value(5).toString());



        i = i + 500;
    }
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                             QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);


}



//***************************************************************************************************************************************************************
//********************************************************************************************************************************************  Entreptise ******
//***************************************************************************************************************************************************************

void welcome::on_B_ajouter_clicked()
{

    QString id_entreprise = ui->id_Entreprise->text();
    QString num_telephone = ui->num_tel->text();
    QString email = ui->email->text();
    QString nom=ui->nom_entreprise->text();
    QString localisation=ui->loc->text();


    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

    if (!emailRegex.match(email).hasMatch()) {

        QMessageBox::critical(this, "Invalid Input", "Please enter a valid email address.");
        return;
    }

    entreprise e(id_entreprise, nom, num_telephone, email, localisation);

    bool test=e.ajouter();

    if(test)
    {
        QMessageBox::information(this, QObject::tr("OK"),
                             QObject::tr("Ajout effectue\n"
                                         "click cancel to exit."));
        show_table_ent();
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectue\n"
                                          "click cancel to exit."));
    }

}

void welcome::on_B_supp_clicked()
{
    entreprise e1; e1.setid_entreprise(ui->id_supp_2->text());
    bool test=e1.supprimer(e1.getid_entreprise());


    if(test)
    {
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Suppression effectue\n"
                                             "click cancel to exit."));
        show_table_ent();
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectue\n"
                                          "click cancel to exit."));
    }
}

void welcome::on_B_modifier_clicked()
{
    QString id_entreprise=ui->id_Entreprise_2->text();
    QString nom=ui->nom_entreprise_2->text();
    QString localisation=ui->loc_2->text();
    QString num_telephone = ui->num_tel_2->text();
    QString email = ui->email_2->text();


    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

    if (!emailRegex.match(email).hasMatch()) {

        QMessageBox::critical(this, "Invalid Input", "Please enter a valid email address.");
        return;
    }

    entreprise En(id_entreprise, nom, num_telephone,  email, localisation);

    bool test = En.modifier(id_entreprise, nom, num_telephone , email, localisation);


    if(test)
    {
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Modification effectue\n"
                                             "click cancel to exit."));
        show_table_ent();
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectue\n"
                                          "click cancel to exit."));
    }
}

void welcome::on_B_CheckID_clicked()
{
    QString id_entreprise=ui->id_Entreprise_2->text();
    bool test=En.checkid(id_entreprise);
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
        QMessageBox::critical(this, QObject::tr("not OK"),
                              QObject::tr("L'ID n'existe pas.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

}

void welcome::show_table_ent()
{
    proxy_ent = new QSortFilterProxyModel();
    ////tableau source
    proxy_ent->setSourceModel(En.afficher());
    /// recherche
    proxy_ent->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_ent->setFilterKeyColumn(-1);
    ui->Table_entreprise->setModel(proxy_ent);
}


void welcome::on_comboBox_recherche_currentIndexChanged(int index)
{
    proxy_ent->setFilterKeyColumn(index);
}

void welcome::on_comboBox_triee_currentIndexChanged(int index)
{
    Qt::SortOrder sortOrder = (ui->checkBox_descendant->checkState() == Qt::Checked) ? Qt::DescendingOrder : Qt::AscendingOrder;
    proxy_ent->sort(index, sortOrder);
}


void welcome::on_pushButton_stat_clicked()
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


void welcome::on_pushButton_stat_2_clicked()
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

void welcome::on_pushButton_stat_3_clicked()
{
    s = new stat_combo();
    s->setWindowTitle("statistique Localisation");
    s->choix_pie_loc();
    s->show();

}




void welcome::on_pushButton_export_clicked()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    filePath = QDir(filePath).filePath("pdf/listeEntreprise.pdf");
    QPdfWriter pdf(filePath);

    QPainter painter(&pdf);
    int i = 4100;


    QColor dateColor(0x4a5bcf);
    painter.setPen(dateColor);

    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();
    painter.drawText(8400,250,cd.toString("Tunis"));
    painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

    QColor titleColor(0x341763);
    painter.setPen(titleColor);
    painter.setFont(QFont("Montserrat SemiBold", 25));

    painter.drawText(3000,2700,"Liste des Entreprises");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    //painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3300,9400,500);

    painter.setFont(QFont("Montserrat SemiBold", 10));

    painter.drawText(500,3600,"ID");
    painter.drawText(1800,3600,"NOM");
    painter.drawText(3200,3600,"N°TELEPHONE");
    painter.drawText(5000,3600,"ADRESSE MAIL");
    painter.drawText(7300,3600,"LOCALISATION");

        painter.setFont(QFont("Montserrat", 10));
    painter.drawRect(100,3300,9400,9000);

    QSqlQuery query;
    query.prepare("select * from ENTREPRISES");
    query.exec();
    int y=4300;
    while (query.next())
    {
        painter.drawLine(100,y,9490,y);
        y+=500;
        painter.drawText(500,i,query.value(0).toString());
        painter.drawText(1800,i,query.value(1).toString());
        painter.drawText(3200,i,query.value(2).toString());
        painter.drawText(5000,i,query.value(3).toString());
        painter.drawText(7350,i,query.value(4).toString());



        i = i + 500;
    }
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                             QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);


}


void welcome::on_send_mail_2_clicked()
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
            QMessageBox::information(this, QObject::tr("EMAIL"),
                                     QObject::tr("Email Envoyé avec succees.\n"
                                                 "click Cancel to exit"),QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(this, QObject::tr("EMAIL"),
                                  QObject::tr("Email is wrong in.\n"
                                              "click Cancel to exit."),QMessageBox::Cancel);
        }
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("EMAIL"),
                              QObject::tr("something is empty.\n"
                                          "click Cancel to exit."),QMessageBox::Cancel);
    }
}

/*void welcome::on_Button_Star_Rating_clicked()
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

void welcome::on_B_CheckID_2_clicked()
{
    /*int id_entreprise=ui->id_Entreprise_3->text().toInt();
        bool test=E.checkid(id_entreprise);
        if (test)
        {
            QSqlQuery query;
            query.prepare("select * from ENTREPRISES where ID_ENTREPRISE= :ID_ENTREPRISE ");
            query.bindValue(":ID_ENTREPRISE", id_entreprise);
            if (query.exec() && query.next())
            {
                QSqlRecord record = query.record();
                ui->id_Entreprise_3->setText(query.value(record.indexOf("ID_ENTREPRISE")).toString());
                ui->nom_entreprise_2->setText(query.value(record.indexOf("NOM")).toString());
                ui->num_tel_2->setText(query.value(record.indexOf("NUM_TELEPHONE")).toString());
                ui->email_2->setText(query.value(record.indexOf("EMAIL")).toString());
                ui->loc_2->setText(query.value(record.indexOf("LOCALISATION")).toString());

            }
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not OK"),
                        QObject::tr("L'ID n'existe pas.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);*/
    QString id_entreprise = ui->id_Entreprise_3->text();
    bool exists = En.checkid(id_entreprise);
    if (exists)
    {
        QMessageBox::information(this, QObject::tr("ID Existence Check"),
                                 QObject::tr("L'ID existe."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, QObject::tr("ID Existence Check"),
                             QObject::tr("L'ID n'existe pas."), QMessageBox::Cancel);

    }
}


void welcome::on_B_arduino_clicked()
{
    int id_entreprise = ui->id_Entreprise_3->text().toInt();

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

void welcome::update_label2() {
    if (!codeExecuted) {
        data = A.read_from_arduino();
        data=data.left(1);
        qDebug() << "Received data from Arduino: " << data;

        if (data != "" && data != "Firmware Version: 0x92 = v2.0\r\n" && data!="\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"){
            ui->etat->setText(data);
            //        int id = data.toInt();

            if (data=="1") {
                qDebug() << "ok access";
                A.write_to_arduino("1");
            } else {
                qDebug() << "pas d'acces";
                A.write_to_arduino("2");

            }
        }

        // Set the boolean variable to true, indicating the code has been executed
        codeExecuted = true;
    }

}

//***************************************************************************************************************************************************************
//***************************************************************************************************************************************  Reclamation ******
//***************************************************************************************************************************************************************
void welcome::on_pb_ajouter_rec_clicked()
{
    QString id_reclamation=ui->le_id_rec->text();
    QString type_reclamation=ui->le_type_rec->text();
    QString expediteur=ui->le_expediteur_rec->text();
    QString destinateur=ui->le_destinateur_rec->text();
    QString nbr_reclamation=ui->le_nbr_rec->text();
    Reclamation REC(id_reclamation,type_reclamation,expediteur,destinateur,nbr_reclamation);

    bool test=REC.ajouter();

    if(test)
    {
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Ajout effectue\n"
                                             "click cancel to exit."));
        show_table_rec();
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectue\n"
                                          "click cancel to exit."));
    }


}



void welcome::on_bd_sup_clicked()
{
    //Reclamation r1; r1.setid_reclamation(ui->id_supp->text());
    QString id_reclamation=ui->id_supp->text();

    bool test=REC.suprimer(id_reclamation);

    if(test)
    {
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Suppression effectue\n"
                                             "click cancel to exit."));
        show_table_rec();
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectue\n"
                                          "click cancel to exit."));
    }
}

void welcome::on_pb_modifier_rec_clicked()
{

    QString id_reclamation=ui->le_id_rec_2->text();
    QString type_reclamation=ui->le_type_rec_2->text();
    QString expediteur=ui->le_expediteur_rec_2->text();
    QString destinateur=ui->le_destinateur_rec_2->text();
    QString nbr_reclamation=ui->le_nbr_rec_2->text();

    bool test=REC.update(id_reclamation,type_reclamation,expediteur ,destinateur,nbr_reclamation);

    QMessageBox msgBox;
    if(test)
    {
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Modification effectue\n"
                                             "click cancel to exit."));
        show_table_rec();
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Modification non effectue\n"
                                          "click cancel to exit."));
    }

}


void welcome::on_comboBox_trie_rec_currentIndexChanged(int index)
{
    Qt::SortOrder sortOrder = (ui->checkBox->checkState() == Qt::Checked) ? Qt::DescendingOrder : Qt::AscendingOrder;
    proxy_rec->sort(index, sortOrder);

}

/*void welcome::on_lineEdit_textChanged(const QString &text)
{
    proxy_rec->setFilterRegularExpression(QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));

}*/

void welcome::on_comboBox_rech_rec_currentIndexChanged(int index)
{
    proxy_rec->setFilterKeyColumn(index);

}
void welcome::show_table_rec()
{

    proxy_rec = new QSortFilterProxyModel();
    ////tableau source
    proxy_rec->setSourceModel(REC.afficher());
    /// recherche
    proxy_rec->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_rec->setFilterKeyColumn(-1);
    ui->tab_reclamation->setModel(proxy_rec);
}

void welcome::on_btn_envoyer_clicked()
{

    QString id_reclamation = ui->id_reclamation->text();
    QString message = ui->message->text();


    show_table_rec();



    bool test=REC.addMessage(id_reclamation,message);

    QMessageBox msgBox;
    if(test)
    {
        QMessageBox::information(this, QObject::tr("OK"),
                                 QObject::tr("Envoi effectue\n"
                                             "click cancel to exit."));
        show_table_rec();
    }
    else
    {
        QMessageBox::critical(this, QObject::tr("Not OK"),
                              QObject::tr("Envoi non effectue\n"
                                          "click cancel to exit."));
    }

}

void welcome::on_afficherStatistique_clicked()
{
    //QVector<int> reclamationsData;
    //statistique *statDialog = new statistique(this, reclamationsData);
    //statDialog->exec();
    //Statistique = new statistique(this);
    //Statistique->show();
    show_chart();

}


void welcome::on_pushButton_export_rec_clicked()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    filePath = QDir(filePath).filePath("pdf/listeReclamation.pdf");
    QPdfWriter pdf(filePath);

    QPainter painter(&pdf);
    int i = 4100;


    QColor dateColor(0x4a5bcf);
    painter.setPen(dateColor);

    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();
    painter.drawText(8400,250,cd.toString("Tunis"));
    painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

    QColor titleColor(0x341763);
    painter.setPen(titleColor);
    painter.setFont(QFont("Montserrat SemiBold", 25));

    painter.drawText(3000,2700,"Liste des RECLAMATION");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    //painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3300,9400,500);

    painter.setFont(QFont("Montserrat SemiBold", 10));

    painter.drawText(500,3600,"ID");
    painter.drawText(1800,3600,"TYPE");
    painter.drawText(3200,3600,"EXPEDITEUR");
        painter.drawText(5000,3600,"DESTINATEUR");
    painter.drawText(7300,3600,"NBR RECLAMATION");

    painter.setFont(QFont("Montserrat", 10));
    painter.drawRect(100,3300,9400,9000);

    QSqlQuery query;
    query.prepare("select * from RECLAMATION");
    query.exec();
    int y=4300;
    while (query.next())
    {
        painter.drawLine(100,y,9490,y);
        y+=500;
        painter.drawText(500,i,query.value(0).toString());
        painter.drawText(1800,i,query.value(1).toString());
        painter.drawText(3200,i,query.value(2).toString());
        painter.drawText(5000,i,query.value(3).toString());
        painter.drawText(7350,i,query.value(4).toString());



        i = i + 500;
    }
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                             QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);



}
void welcome::show_chart(){
    chart ch;
    DrilldownChart *chart = new DrilldownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QPieSeries *numberSeries = new QPieSeries();
    numberSeries->setName("Nbr accreditation - All");
    const QStringList names = ch.getnbrReclamations();
    for (int i = 0 ; i < names.size();++i) {
        *numberSeries << new DrilldownSlice(names[i].toDouble()," ", numberSeries);
    }

    chart->changeSeries(numberSeries);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);
}
QString currentID;
/*void MainWindow::on_pb_checkID_clicked()
{
    data = A.read_from_arduino();
        currentID = QString::fromUtf8(data);

        ui->lineEdit_id->setText(data);
        QSqlQuery query;
        query.prepare("SELECT ID, MDP FROM EMPLOYE WHERE ID = :ID");
        query.bindValue(":ID", currentID);

        if (query.exec() && query.next())
        {
            // ID exists, prompt for password
            A.write_to_arduino("1");
        }
        else
        {
            // ID does not exist
            A.write_to_arduino("0");
            ui->lineEdit_id->clear();
        }
}
*/
void welcome::on_pb_checkmdp_clicked()
{
    data = A.read_from_arduino();



    QString enteredMDP = QString::fromUtf8(data);

    QSqlQuery query;
    query.prepare("SELECT MDP, NOM FROM EMPLOYE WHERE ID = :ID");
    query.bindValue(":ID", currentID);

    if (query.exec() && query.next())
    {
        QString storedMDP = query.value("MDP").toString();
        QString employeeName = query.value("NOM").toString();
        QByteArray nom = employeeName.toUtf8();
        if (enteredMDP == storedMDP)
        {
            A.write_to_arduino("2");
        }
        else
        {
            A.write_to_arduino("3");  // Password is incorrect

        }
    }
    else
    {
        A.write_to_arduino("0");  // ID not found (should not happen if previous check passed)

    }
    idRead=false;

}

void welcome::update_label() {
    // Assuming data is a member variable
    if(idRead==false){
        data += A.read_from_arduino();  // Accumulate the received data

        // Check if we have at least 5 characters in the accumulated data
        if (data.length() >= 5) {
            currentID = data.left(5);  // Extract the first 5 characters as the ID
            qDebug() << "Complete ID:" << currentID;

            ui->label_15->setText(currentID);
            QSqlQuery query;
            query.prepare("SELECT ID, MDP FROM EMPLOYE WHERE ID = :ID");
            query.bindValue(":ID", currentID);

            if (query.exec() && query.next()) {
                // ID exists, prompt for password
                A.write_to_arduino("1");


            } else {
                // ID does not exist
                A.write_to_arduino("0");
            }

            // Reset the data variable for the next ID
            data.clear();
            idRead=true;
        }
    }
    data2 = A.read_from_arduino();  // Accumulate the received data

    QString enteredMDP = QString::fromUtf8(data2);
    qDebug()<<"mdp"<<data2;
    QSqlQuery query;
    query.prepare("SELECT MDP, NOM FROM EMPLOYE WHERE ID = :ID");
    query.bindValue(":ID", currentID);

    if (query.exec() && query.next())
    {
        QString storedMDP = query.value("MDP").toString();
        QString employeeName = query.value("NOM").toString();
        QByteArray nom = employeeName.toUtf8();
        if (enteredMDP == storedMDP)
        {
            A.write_to_arduino("2");
            idRead=true;
        }
        else
        {
            A.write_to_arduino("3");  // Password is incorrect
            idRead=false;
        }
    }
    else
    {
        A.write_to_arduino("0");  // ID not found (should not happen if previous check passed)
    }
}

//***************************************************************************************************************************************************************
//********************************************************************************************************************************************  Reglement *******
//***************************************************************************************************************************************************************

void welcome::on_ajouter_clicked()
{
    QString id_r_string = ui->id->text();
    bool ok;
    int id_r = id_r_string.toInt(&ok);
    if (!ok) {

        QMessageBox::warning(this, "Invalid Input", "Please enter a valid integer for ID.");
        return;
    }

    QString type = ui->type->text();
    QString description = ui->description->text();
    QDate date = ui->date->date();
    QString validation = ui->comboBox_validation->currentText();

    Reglement tr(id_r,type, validation,date,description);
    bool test = tr.ajouter();

    QMessageBox msgBox;
    if (test) {
        QMessageBox::information(this, QObject::tr("Ok"),
                                 QObject::tr("Ajout effectuée.\n"
                                             "Click Ok to exit."), QMessageBox::Ok);

    } else {
        QMessageBox::critical(this, QObject::tr("Not ok"),
                              QObject::tr("Échec de l'ajout.\n"
                                          "Click cancel to exit"),QMessageBox::Cancel);
    }

    ui->historique_view->setModel(Reg.afficher_his());
    ui->table->setModel(tr.afficher());
    ui->id->clear();
    ui->type->clear();
    ui->date->clear();
    ui->description->clear();

}



void welcome::on_supprimer_clicked()
{

    int id_r = ui->supp->text().toInt();
    bool test = Reg.supprimer(id_r);
    if (test) {
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Suppression effectuée.\n"
                                             "Click Ok to exit."), QMessageBox::Ok);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                              QObject::tr("Échec de la suppression.\n"
                                          "Le reglement n'existe pas dans la base de données."),
                              QMessageBox::Cancel);
    }
    ui->table->setModel(Reg.afficher());
    ui->historique_view->setModel(Reg.afficher_his());
    ui->supp->clear();
}
void welcome::on_modifier_clicked()
{

    int id_r=ui->id->text().toInt();
    QString type=ui->type->text();
    QString validation=ui->comboBox_validation->currentText();
    QDate date=ui->date->date();
    QString description=ui->description->text();

    Reglement Reg(id_r,type,validation,date,description);



    bool test=Reg.modifier(id_r,type,validation,date,description);

    if(test)

    {ui->table->setModel(Reg.afficher());
        ui->historique_view->setModel(Reg.afficher_his());
        QMessageBox::information(nullptr, QObject::tr("Modifier avec succées "),

                                 QObject::tr("reglement modifiée.\n"

                                             "Click ok to exit."), QMessageBox::Ok);



    }

    else

    QMessageBox::critical(nullptr, QObject::tr("Modifier a echoué"),

                          QObject::tr("echec d'ajout !.\n"

                                      "Click Cancel to exit."), QMessageBox::Cancel);

}

void welcome::on_input_Rechercher_textChanged(const QString &arg1)
{
    QString chaine_c=ui->input_Rechercher->text();


    if(chaine_c !="")
    {
        ui->table->setModel(Reg.rechercherReglement(chaine_c));
    }
    else
    {
        QString trieOption=ui->TricomboBoxReglement->currentText();
        ui->table->setModel(Reg.trierReglement(trieOption));

    }
}

void welcome::on_PDF_Btn_clicked()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    filePath = QDir(filePath).filePath("pdf/listeReglement.pdf");
    QPdfWriter pdf(filePath);

    QPainter painter(&pdf);
    int i = 4100;
    /*  const QImage image(":/new/icons/icons/logo.png");
                const QPoint imageCoordinates(155,0);
                int width1 = 1600;
                int height1 = 1600;
                QImage img=image.scaled(width1,height1);
                painter.drawImage(imageCoordinates, img );*/


    QColor dateColor(0x4a5bcf);
    painter.setPen(dateColor);

    painter.setFont(QFont("Montserrat SemiBold", 11));
    QDate cd = QDate::currentDate();
    painter.drawText(8400,250,cd.toString("Tunis"));
    painter.drawText(8100,500,cd.toString("dd/MM/yyyy"));

    QColor titleColor(0x341763);
    painter.setPen(titleColor);
    painter.setFont(QFont("Montserrat SemiBold", 25));

    painter.drawText(3000,2700,"Liste des Reglement");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Time New Roman", 15));
    //painter.drawRect(100,100,9400,2500);
    painter.drawRect(100,3300,9400,500);

    painter.setFont(QFont("Montserrat SemiBold", 10));

    painter.drawText(500,3600,"ID_R");
    painter.drawText(2000,3600,"TYPE");
    painter.drawText(3300,3600,"VALIDATION");
    painter.drawText(5000,3600,"DATE_REGLEMENT");
    painter.drawText(7700,3600,"DESCRIPTION");

    painter.setFont(QFont("Montserrat", 10));
    painter.drawRect(100,3300,9400,9000);

    QSqlQuery query;
    query.prepare("select * from REGLEMENT");
    query.exec();
    int y=4300;
    while (query.next())
    {
        painter.drawLine(100,y,9490,y);
        y+=500;
        painter.drawText(500,i,query.value(0).toString());
        painter.drawText(2000,i,query.value(1).toString());
        painter.drawText(3300,i,query.value(2).toString());
        painter.drawText(5000,i,query.value(3).toString());
        painter.drawText(7700,i,query.value(4).toString());



        i = i + 500;
    }
    QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
                             QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);

}


void welcome::on_Stat_miseAjour_clicked()
{QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM REGLEMENT");

    int countOui = 0;
    int countNon = 0;

    while (model->canFetchMore()) {
        model->fetchMore();
    }

    int validationIndex = model->record().indexOf("validation");

    for (int i = 0; i < model->rowCount(); ++i) {
        QString validation = model->record(i).value(validationIndex).toString();
        if (validation.toLower() == "oui") {
            countOui++;
        } else if (validation.toLower() == "non") {
            countNon++;
        }
    }

    int total = countOui + countNon;

    QString a = QString("Oui \t" + QString::number(countOui) + " (" + QString::number((countOui * 100.0) / total, 'f', 2) + "%)");
    QString b = QString("Non \t" + QString::number(countNon) + " (" + QString::number((countNon * 100.0) / total, 'f', 2) + "%)");

    QPieSeries *series = new QPieSeries();
    series->append(a, countOui);
    series->append(b, countNon);

    // Le reste du code pour afficher le graphique reste inchangé
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->setBackgroundVisible(false);
    chart->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QPalette pal = qApp->palette();
    chartView->setMaximumWidth(731);
    chartView->setMaximumHeight(381);
    chartView->setMinimumWidth(411);
    chartView->setMinimumHeight(251);
    chartView->setParent(ui->stat_label);
    chartView->show();

}

void welcome::on_Aj_Client_pushButton_clicked()
{
    ui->stackedWidget_Reglement->setCurrentIndex(0);
}

void welcome::on_Aj_Client_pushButton_2_clicked()
{
    ui->stackedWidget_Reglement->setCurrentIndex(1);
}



void welcome::on_TricomboBoxReglement_currentTextChanged(const QString &arg1)
{
    QString trieOption=ui->TricomboBoxReglement->currentText();
    ui->table->setModel(Reg.trierReglement(trieOption));
}

void welcome::on_send_clicked()
{

    sms s;
    const QString msg = ui->msg->text();
    const QString recipient_phone_number = "+216"+ ui->phone->text();
    s.sendSMS(recipient_phone_number, msg);
}




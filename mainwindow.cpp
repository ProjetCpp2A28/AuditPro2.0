#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "alogin.h"
#include "employe.h"
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

QT_CHARTS_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)



{
    ui->setupUi(this);


    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }

    ui->le_id->setValidator(new QIntValidator(0, 99999, this));
    ui->le_mdp->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_num->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_id_sup->setValidator(new QIntValidator(0, 99999, this));
    ui->le_id_2->setValidator(new QIntValidator(0, 99999, this));
    ui->le_mdp_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_num_2->setValidator(new QIntValidator(0, 99999999, this));
    ui->le_id_5->setValidator(new QIntValidator(0, 99999, this));
    ui->le_id_6->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_2->setValidator(new QIntValidator(0, 99999, this));

    show_table();
 }

MainWindow::~MainWindow()
{
    delete ui;

}



QString currentID;

void MainWindow::on_pb_checkID_clicked()
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

void MainWindow::on_pb_checkmdp_clicked()
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
}



void MainWindow::on_le_adresse_editingFinished()
{


    QString ADR = ui->la_adresse->text();


    if (!ADR.endsWith("@gmail.com", Qt::CaseInsensitive))
    {

        QMessageBox::critical(nullptr, QObject::tr("Invalid Email"),
            QObject::tr("Please enter a valid Gmail email address."),
            QMessageBox::Cancel);
        ui->la_adresse->clear();
    }
}

void MainWindow::on_pb_ajouter_clicked()
{



        QString ID = ui->le_id->text();
        QString NUM = ui->le_num->text();
        QString MDP = ui->le_mdp->text();
        QString NOM = ui->le_nom->text();
        QString ADR = ui->la_adresse->text();
        QString DEP = ui->le_dep->text();


        if (!ADR.endsWith("@gmail.com", Qt::CaseInsensitive))
        {

            QMessageBox::critical(nullptr, QObject::tr("Invalid Email"),
                QObject::tr("Please enter a valid Gmail email address."),
                QMessageBox::Cancel);
            ui->la_adresse->clear();
            return;
        }


        employe E(ID, NUM, MDP, NOM, ADR, DEP);
        bool test = E.ajouter();

        if (test)
        {
            show_table();
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectue\n"
                            "click cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout non effectue\n"
                            "click cancel to exit."), QMessageBox::Cancel);
        }

}

void MainWindow::on_pb_sup_clicked()
{
    employe E1; E1.setid(ui->le_id_sup->text());
    bool test=E1.supprimer(E1.getID());
    QMessageBox msgBox;
    if (test)
       { msgBox.setText("Suppression avec succes.");
        show_table();
        }
        else
        msgBox.setText("Echec de suppresion.");
        msgBox.exec();

}

void MainWindow::on_pb_modifier_clicked()
{

    QString ID = ui->le_id_2->text();
        QString NUM = ui->le_num_2->text();
        QString MDP = ui->le_mdp_2->text();
        QString NOM = ui->le_nom_2->text();
        QString ADR = ui->la_adresse_2->text();
        QString DEP = ui->le_dep_2->text();


        employe E;
        bool test = E.update(ID, NUM, MDP, NOM, ADR, DEP);

        if (test)
        {
            show_table();
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Modifier effectue\n"
                            "click cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Modifier non effectue\n"
                            "click cancel to exit."), QMessageBox::Cancel);
}
}
void MainWindow::show_table()
{

proxy = new QSortFilterProxyModel();

proxy->setSourceModel(E.afficher());

proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
proxy->setFilterKeyColumn(-1);
    ui->tab_emp->setModel(proxy);
}




void MainWindow::on_reach_currentIndexChanged(int index)
{
     proxy->setFilterKeyColumn(index);
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
     proxy->setFilterRegExp(QRegExp(text, Qt::CaseInsensitive, QRegExp::FixedString));
}

void MainWindow::on_reach_2_currentIndexChanged(int index)
{
    Qt::SortOrder sortOrder = (ui->checkBox->checkState() == Qt::Checked) ? Qt::DescendingOrder : Qt::AscendingOrder;
    proxy->sort(index, sortOrder);

}



void MainWindow::on_pushButton_clicked()
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
   }



void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery q1,q2,q3,q4, q5,q6, q7;
    qreal tot=0,c1=0,c2=0,c3=0, c4=0, c5=0, c6=0;

    q1.prepare("SELECT * FROM EMPLOYE");
    q1.exec();

    q2.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.employee'");
    q2.exec();

    q3.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.rapports'");
    q3.exec();

    q4.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.entreprises'");
    q4.exec();

    q5.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.reglement'");
    q5.exec();

    q6.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.accreditation'");
    q6.exec();

    q7.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.reclamations'");
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
void MainWindow::on_pushButton_3_clicked()
{
    QString idToExport = ui->lineEdit_2->text();
        employe E;
        QString details = E.getDetailsByID(idToExport);

        if (!details.isEmpty()) {
            QString fileName = "employee_details_" + idToExport + ".pdf";

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
            qDebug() << "Error: Employee not found or an error occurred.";
            QMessageBox::critical(nullptr, QObject::tr("Export Error"),
                                  QObject::tr("Employee not found or an error occurred."),
                                  QMessageBox::Ok);
}
}







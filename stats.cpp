/*#include "stats.h"
#include "ui_stats.h"
#include <QMainWindow>
stats::stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stats)
{
    ui->setupUi(this);
}

stats::~stats()
{
    delete ui;
}

//bar chart
void stats::choix_bar()
{
QSqlQuery q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,q11,q12;
qreal tot1=0,c1=0,c2=0,c3=0;
qreal tot2=0,c4=0,c5=0,c6=0;
qreal tot3=0,c7=0,c8=0,c9=0;
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




while (q1.next()){tot1++;}
while (q2.next()){c1++;}
while (q3.next()){c2++;}
while (q4.next()){c3++;}
while (q5.next()){tot2++;}
while (q6.next()){c4++;}
while (q7.next()){c5++;}
while (q8.next()){c6++;}
while (q9.next()){tot3++;}
while (q10.next()){c7++;}
while (q11.next()){c8++;}
while (q12.next()){c9++;}


c1=c1/tot1;
c2=c2/tot1;
c3=c3/tot1;
c4=c4/tot2;
c5=c5/tot2;
c6=c6/tot2;
c7=c7/tot3;
c8=c8/tot3;
c9=c9/tot3;



// Assign names to the set of bars used
        QBarSet *set0 = new QBarSet("valide");
        QBarSet *set1 = new QBarSet("semi valide");
        QBarSet *set2 = new QBarSet("non valide");


        // Assign values for each bar
        *set0 << c1 << c4 << c7 ;
        *set1 << c2 << c5 << c8;
        *set2 << c3 << c6 << c9;


////////



        // Add all sets of data to the chart as a whole
        // 1. Bar Chart
        QBarSeries *series = new QBarSeries();

        // 2. Stacked bar chart
        series->append(set0);
        series->append(set1);
        series->append(set2);



        // Used to define the bar chart to display, title
        // legend,
        QChart *chart = new QChart();

        // Add the chart
        chart->addSeries(series);
        chart->setTitle("Bilan de 1/4 Semestre");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

//////////
        QStringList categories;
        categories << "Jan" << "Feb" << "Mar" ;
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Numbers");
        axisY->setRange(0,3);
        //axisY->setTickCount(series->count());
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);




        // Used to change the palette
        QPalette pal = qApp->palette();

        // Change the color around the chart widget and text
        pal.setColor(QPalette::Window, QRgb(0xffffff));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));

        // Apply palette changes to the application
        qApp->setPalette(pal);


// Used to display the chart
chartView = new QChartView(chart,ui->label_stat);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setMinimumSize(400,400);
chartView->show();

//
}*/


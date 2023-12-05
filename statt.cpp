/*#include "statt.h"
#include "ui_statt.h"

statt::statt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statt)
{
    ui->setupUi(this);
}

statt::~statt()
{
    delete ui;
}

void statt::choix_bar()
{
QSqlQuery q1,q2,q3,q4, q5,q6, q7;
qreal tot=0,c1=0,c2=0,c3=0, c4=0, c5=0, c6=0;

q1.prepare("SELECT * FROM EMPLOYE");
q1.exec();

q2.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.employee'");
q2.exec();

q3.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.rapports '");
q3.exec();

q4.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.entreprises ' ");
q4.exec();

q5.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.reglement' ");
q5.exec();

q6.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.l'accreditation ' ");
q6.exec();

q7.prepare("SELECT * FROM EMPLOYE WHERE DEP='g.reclamations ' ");
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
chartView = new QChartView(chart,ui->label_stat);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setMinimumSize(400,400);

chartView->show();
}*/

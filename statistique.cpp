#include "statistique.h"
#include "ui_statistique.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

statistique::statistique(QWidget *parent):
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);

    QBarSet *set0 = new QBarSet("nbr_reclamation");

    *set0 << 30 << 40 << 10 << 20 << 10 << 60;


    QBarSeries *series = new QBarSeries();
    series->append(set0);


    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("BarChart Exemple In QT5 c++");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "jan" << "feb" << "mar";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    QChartView *chartView = new QChartView(chart);
    chartView->setParent(ui->horizontalFrame);

}
statistique::~statistique()
{
    delete ui;
}

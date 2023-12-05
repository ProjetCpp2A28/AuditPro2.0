#ifndef STAT_H
#define STAT_H

#include <QDialog>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class stat;
}

class stat : public QDialog
{
    Q_OBJECT

public:
    explicit stat(QWidget *parent = nullptr);
    ~stat();
    QChartView *chartView ;
    void choix_bar();
private:
    Ui::stat *ui;
};

#endif // STAT_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include "employe.h"
#include <QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QTableWidget>
#include <QSerialPort>
#include<QPushButton>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include"arduino.h"
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

#include <QLabel>
QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSortFilterProxyModel *proxy;

        void show_table();
QChartView *chartView ;
private slots:
    void on_pb_ajouter_clicked();

    void on_pb_sup_clicked();

    void on_pb_modifier_clicked();

    void on_reach_currentIndexChanged(int index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_reach_2_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_le_adresse_editingFinished();
    void on_pushButton_3_clicked();






    void on_pb_checkID_clicked();

    void on_pb_checkmdp_clicked();

private:
    Ui::MainWindow *ui;
    employe E;
    QSerialPort serial;
    QByteArray data,mdparduino; // variable contenant les données reçues

    Arduino A; // objet temporaire



};
#endif // MAINWINDOW_H

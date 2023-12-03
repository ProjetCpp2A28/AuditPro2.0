#include "stat_combo.h"
#include "ui_stat_combo.h"
#include <QTextStream>
#include <QDebug>

stat_combo::stat_combo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat_combo)
{
    ui->setupUi(this);
}

stat_combo::~stat_combo()
{
    delete ui;
}

void stat_combo::setPourcentageValide(double pourcentage)
{
    pourcentageValide = pourcentage;
    QString text = QString("Valide: %1%").arg(pourcentage);
    ui->labelPourcentageValide->setText(text);
}

void stat_combo::setPourcentageNonValide(double pourcentage)
{
    pourcentageNonValide = pourcentage;
    QString text = QString("Non Valide: %1%").arg(pourcentage);
    ui->labelPourcentageNonValide->setText(text);
}

void stat_combo::choix_bar()
{
    QSqlQuery q1, q2, q3, q4, q5;
    qreal tot = 0, c1 = 0, c2 = 0;

    q1.prepare("SELECT * FROM RAPPORTS_AUDITS");
    q1.exec();

    q2.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide'");
    q2.exec();

    q3.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='non valide'");
    q3.exec();

    // Ajoutez d'autres requêtes pour les autres conditions si nécessaire

    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }

    // Calculez les pourcentages
    c1 = (c1 / tot) * 100;
    c2 = (c2 / tot) * 100;


    setPourcentageValide(c1);
    setPourcentageNonValide(c2);

    QString percentageC1 = QString::number(c1, 'f', 2) + "%";
    QString percentageC2 = QString::number(c2, 'f', 2) + "%";

    QBarSet *set0 = new QBarSet("Valide");
    QBarSet *set1 = new QBarSet("Non Valide");

    *set0 << c1;
    *set1 << c2;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);

    QChart *chart = new QChart();
    chart->addSeries(series);

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    chart->setAxisX(axis, series);

    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);

    chartView = new QChartView(chart, ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(500, 400);
    chartView->show();
}

void stat_combo::choix_pie()
{
    QSqlQuery q1, q2, q3;
    qreal tot = 0, c1 = 0, c2 = 0;

    q1.prepare("SELECT * FROM RAPPORTS_AUDITS");
    q1.exec();

    q2.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='valide'");
    q2.exec();

    q3.prepare("SELECT * FROM RAPPORTS_AUDITS WHERE RESULTAT='non valide'");
    q3.exec();

    // Ajoutez d'autres requêtes pour les autres conditions si nécessaire

    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }

    // Calculez les pourcentages
    c1 = (c1 / tot) * 100;
    c2 = (c2 / tot) * 100;

    setPourcentageValide(c1);
    setPourcentageNonValide(c2);


    QString percentageC1 = QString::number(c1, 'f', 2) + "%";
    QString percentageC2 = QString::number(c2, 'f', 2) + "%";

    QPieSeries *series = new QPieSeries();
    series->append("Valide", c1);
    series->append("Non Valide", c2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();

    chartView = new QChartView(chart, ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(500, 400);
    chartView->show();
}




void stat_combo::choix_pie_loc()
{
    QSqlQuery query;
    query.prepare("SELECT DISTINCT UPPER(LOCALISATION) FROM ENTREPRISES");
    query.exec();

    qreal total = 0;  // Initialisation du total

    QPieSeries *series = new QPieSeries();

    while (query.next()) {
        QString localisation = query.value(0).toString();

        QSqlQuery localisationQuery;
        localisationQuery.prepare("SELECT COUNT(*) FROM ENTREPRISES WHERE UPPER(LOCALISATION) = :localisation");
        localisationQuery.bindValue(":localisation", localisation);
        localisationQuery.exec();

        if (localisationQuery.next()) {
            qreal count = localisationQuery.value(0).toDouble();
            total += count;  // Ajout à total

            qreal percentage = (count / total) * 100;

            series->append(localisation, percentage);
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->show();

    chartView = new QChartView(chart, ui->label_stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(500, 400);
    chartView->show();
}


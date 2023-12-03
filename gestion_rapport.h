#ifndef GESTION_RAPPORT_H
#define GESTION_RAPPORT_H

#include "arduino.h"
#include "rapport.h"
#include "stat.h"

#include "QByteArray"

#include <QCryptographicHash>
#include <QStandardItemModel>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>


#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QSqlTableModel>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QRegularExpression>


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

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class Gestion_Rapport; }
QT_END_NAMESPACE

class Gestion_Rapport : public QMainWindow
{
    Q_OBJECT

public:
    Gestion_Rapport(QWidget *parent = nullptr);
    ~Gestion_Rapport();

    QSortFilterProxyModel *proxy;
    QStandardItemModel *standardModel;
    QStandardItemModel *sourceModel;
    void id_existe();

    void show_table();
    void clear_form();
    void stat_res();
    //void show_chart();
    /*void setPasswordHash(const QByteArray &hash);
    QByteArray getPasswordHash() const;
    void setUserPassword(const QString &password);*/
private slots:

    void on_pushButton_ajouter_clicked();
    void on_pushButton_afficher_clicked();
    void on_pushButton_check_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();

    void on_rech_textChanged(const QString &text);
    void on_comboBox_rech_currentIndexChanged(int);

    void on_comboBox_trie_currentIndexChanged(int index);

    void on_pushButton_stat_resultat_clicked();
    void on_pushButton_stat_entreprise_clicked();
    //void on_handlePieSeries_Clicked(const QString &label);
    //void on_pushButton_stat_entreprise_2_clicked();

    void on_pushButton_cryptage_clicked();
    void on_pushButton_decryptage_clicked();
    void showPasswordDialog();

    void on_pushButton_pdf_clicked();




    void on_arduino_clicked();

    void on_pushButton_valide_clicked();

    void on_pushButton_changer_clicked();

private:
    Ui::Gestion_Rapport *ui;
    Rapport r;
    QChartView *chartView;
    QChart *chart;
    QChartView *chartView1;
    QChart *chart1;
    QByteArray encrypt(const QByteArray &data, const QByteArray key);
    QByteArray decrypt(const QByteArray &data, const QByteArray &key);
    QString getPasswordFromUser();
    bool checkPassword(const QString &password);

    QByteArray enteredID; // variable contenant les données reçues
    QByteArray key;
    Arduino A; // objet temporaire


};
#endif // GESTION_RAPPORT_H

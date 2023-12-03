/*#ifndef INTERFACE_RAPPORT_H
#define INTERFACE_RAPPORT_H

#include <QMainWindow>
#include "arduino.h"
#include "rapport.h"

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

namespace Ui {
class Interface_rapport;
}

class Interface_rapport : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interface_rapport(QWidget *parent = nullptr);
    ~Interface_rapport();
    QSortFilterProxyModel *proxy;
    QStandardItemModel *standardModel;
    QStandardItemModel *sourceModel;
    void id_existe();

    void show_table();
    void clear_form();
    void stat_res();

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

    void on_pushButton_cryptage_clicked();
    void on_pushButton_decryptage_clicked();
    void showPasswordDialog();

    void on_pushButton_pdf_clicked();

    void on_arduino_clicked();

    void on_pushButton_valide_clicked();

    void on_pushButton_changer_clicked();

    //void on_pushButton_2_clicked();

    void on_pushButton_Employee_clicked();

    void on_pushButton_rapport_clicked();

private:
    Ui::Interface_rapport *ui;
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
    //Interface_employee *employee;
};

#endif // INTERFACE_RAPPORT_H

*/

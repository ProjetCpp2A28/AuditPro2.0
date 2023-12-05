#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>

#include "arduino.h"
#include "rapport.h"
#include "employe.h"
#include "entreprise.h"
#include "stat_combo.h"
#include "smtp.h"
#include "statistique.h"
#include "reclamation.h"
#include "chart.h"
#include "reglement.h"
#include "drilldownchart.h"
#include "drilldownslice.h"


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


#include <QByteArray>

#include <QCryptographicHash>
#include <QStandardItemModel>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QObject>
#include <QTableWidget>
#include <QSerialPort>
#include <QPushButton>
#include <QLabel>


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
class welcome;
}

class welcome : public QMainWindow
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = nullptr);
    ~welcome();
    QSortFilterProxyModel *proxy_rap, *proxy_emp,*proxy_ent,*proxy_rec,*proxy_acc,*proxy_reg;
    QStandardItemModel *standardModel;
    QStandardItemModel *sourceModel;
    void id_existe();

    void show_table_rap();
    void show_table_emp();
    void show_table_ent();
    void show_table_rec();
    void show_table_acc();
    void show_table_reg();

    void show_chart();

    void clear_form();
    void stat_res();

private slots:

    void on_pushButton_employee_clicked();
    void on_pushButton_rapport_clicked();
    void on_pushButton_entreprise_clicked();

    //////////////////////////////////////////////////////////////////////////////////////rapport
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

    //////////////////////////////////////////////////////////////////////////////////////employe
    void on_pb_ajouter_clicked();
    void on_pb_sup_clicked();
    void on_pb_modifier_clicked();

    void on_reach_currentIndexChanged(int index);
    //void on_lineEdit_textChanged(const QString &arg1);
    void on_reach_2_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_le_adresse_editingFinished();
    void on_pushButton_3_clicked();

   // void on_pb_checkID_clicked();
   // void on_pb_checkmdp_clicked();
    ///////////////////////////////////////////////////////////////////////////////////////Entrepise
    void on_B_ajouter_clicked();
    void on_B_supp_clicked();
    void on_B_modifier_clicked();
    void on_B_CheckID_clicked();

    void on_comboBox_recherche_currentIndexChanged(int index);
    void on_comboBox_triee_currentIndexChanged(int index);

    void on_pushButton_stat_clicked();
    void on_pushButton_stat_2_clicked();
    void on_pushButton_stat_3_clicked();

    void on_pushButton_export_clicked();
    void on_send_mail_2_clicked();
    // void on_pushButton_2_clicked();
    //void on_Button_Star_Rating_clicked();
    void update_label2();
    void on_B_CheckID_2_clicked();
    void on_B_arduino_clicked();
    /////////////////////////////////////////////////////////////////////////////////////reclamation
    void on_pb_ajouter_rec_clicked();  //
    void on_bd_sup_clicked();
    void on_pb_modifier_rec_clicked();//

    void on_comboBox_rech_rec_currentIndexChanged(int index);
    //void on_lineEdit_textChanged(const QString &arg1);
    void on_comboBox_trie_rec_currentIndexChanged(int index);

    void on_btn_envoyer_clicked();
    void on_afficherStatistique_clicked();
    void on_pushButton_export_rec_clicked();  //
    //void on_pb_checkID_clicked();
    void on_pb_checkmdp_clicked();
    void update_label();

    void on_pushButton_accred_clicked();

    void on_pushButton_reclamation_clicked();

    void on_pushButton_reglement_clicked();
    /////////////////////////////////////////////////////////////////////////////////////reglement
    void on_ajouter_clicked();

    void on_modifier_clicked();
    void on_supprimer_clicked();

    void on_input_Rechercher_textChanged(const QString &arg1);


    void on_PDF_Btn_clicked();


    void on_Stat_miseAjour_clicked();

    void on_Aj_Client_pushButton_clicked();

    void on_Aj_Client_pushButton_2_clicked();


    void on_TricomboBoxReglement_currentTextChanged(const QString &arg1);

    void on_send_clicked();


private:
    Ui::welcome *ui;
    Arduino A;
    ///////////////////////////////////////////////////////////////////////////////////////Rapport
    Rapport r;
    QChartView *chartView;
    QChart *chartt;
    QChartView *chartView1;
    QChart *chartt1;
    QByteArray encrypt(const QByteArray &data, const QByteArray key);
    QByteArray decrypt(const QByteArray &data, const QByteArray &key);
    QString getPasswordFromUser();
    bool checkPassword(const QString &password);
    QByteArray enteredID;
    QByteArray key;
    ///////////////////////////////////////////////////////////////////////////////////////employe
    employe E;
    QSerialPort serial;
    //QByteArray data,mdparduino;
    ///////////////////////////////////////////////////////////////////////////////////////entreprise
    entreprise En;
    stat_combo *s;
    double c1,c2;
    bool codeExecuted=false;

    QStringList files;

    QString mnomemp="localhost";
    quint16 mport=3333;
    QTcpSocket *mSocket;
    QByteArray data2;
    //////////////////////////////////////////////////////////////////////////////////////reclamation
    bool idRead=false;
    Reclamation REC;
    statistique *Statistique;
    QByteArray data,mdparduino,data3;
    QSerialPort*Serial;
    //////////////////////////////////////////////////////////////////////////////////////Reglement
    Reglement Reg;

};

#endif // WELCOME_H

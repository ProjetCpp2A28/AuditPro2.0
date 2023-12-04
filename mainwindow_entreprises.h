#ifndef MAINWINDOW_ENTREPRISES_H
#define MAINWINDOW_ENTREPRISES_H
#include "entreprise.h"
#include "stat_combo.h"
#include "arduino.h"
#include <QMainWindow>
#include <QSortFilterProxyModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow_Entreprises; }
QT_END_NAMESPACE

class MainWindow_Entreprises : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow_Entreprises(QWidget *parent = nullptr);
    ~MainWindow_Entreprises();

    QSortFilterProxyModel *proxy;

    void show_table();


private slots:
    void update_label();
    void on_B_ajouter_clicked();

    void on_B_supp_clicked();

    void on_B_modifier_clicked();

    void on_B_CheckID_clicked();

    void on_lineEdit_textChanged(const QString &text);

    void on_comboBox_recherche_currentIndexChanged(int index);

    void on_comboBox_trie_currentIndexChanged(int index);

    void on_pushButton_stat_clicked();

    void on_pushButton_stat_2_clicked();

    void on_pushButton_stat_3_clicked();

    void on_pushButton_clicked();



    void on_send_mail_2_clicked();

    void on_pushButton_2_clicked();

    void on_Button_Star_Rating_clicked();

    void on_B_CheckID_2_clicked();

    void on_B_arduino_clicked();

private:
    Ui::MainWindow_Entreprises *ui;

    entreprise E;
    stat_combo *s;
    double c1,c2;
    bool codeExecuted = false;
    QStringList files;

      QString mnomemp="localhost";
      quint16 mport=3333;
      QTcpSocket *mSocket;

     //Arduino

      QByteArray data; // variable contenant les données reçues

      Arduino A; // objet temporaire


};
#endif // MAINWINDOW_ENTREPRISES_H

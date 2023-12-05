#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"

#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_email->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_mdp->setValidator(new QIntValidator(0,99999999,this));
    setWindowFlag(Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_login_clicked()
{
    QString enteredID = ui->lineEdit_email->text();
    QString enteredMDP = ui->lineEdit_mdp->text();

    if (E.authenticate(enteredID, enteredMDP)) {

        E.resetLoginAttempts();

        QMessageBox::information(nullptr, QObject::tr("Login Successful"),
                                 QObject::tr("Welcome!"), QMessageBox::Ok);

        welcomee = new welcome(this);
        this->hide();
        welcomee ->show();


    } else {

        QMessageBox::critical(nullptr, QObject::tr("Login Failed"),
                              QObject::tr("Invalid ID or password. Please try again."), QMessageBox::Ok);
        qDebug() << "Failed login attempts: " << E.getLoginAttempts();
    }

}


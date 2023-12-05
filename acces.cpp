#include "acces.h"
#include "ui_acces.h"
#include "employe.h"
#include "mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QMainWindow>
acces::acces(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::acces)
{
    ui->setupUi(this);
}

acces::~acces()
{
    delete ui;
}

void acces::on_pushButton_clicked()
{     QString ID = ui->lineEdit->text();
      QString MDP= ui->lineEdit_2->text();

      // Check access in the database
      if (employeManager->login(ID, MDP))
      {
          // Successful login
          QMessageBox::information(this, "Login", "Login successful");

          // Show the main window after successful login
          this->show();
      }
      else
      {
          // Login failed
          QMessageBox::warning(this, "Login", "Login failed");
      }

}

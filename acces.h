#ifndef ACCES_H
#define ACCES_H
#include <QMainWindow>
#include <QDialog>
#include "employe.h"
namespace Ui {
class acces;
}

class acces : public QDialog
{
    Q_OBJECT

public:
    explicit acces(QWidget *parent = nullptr);
    ~acces();

private slots:

    void on_pushButton_clicked();

private:
    Ui::acces *ui;
    employe *employeManager;
};

#endif // ACCES_H

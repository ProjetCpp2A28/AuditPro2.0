#include "alogin.h"
#include "ui_alogin.h"

alogin::alogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alogin)
{
    ui->setupUi(this);
}

alogin::~alogin()
{
    delete ui;
}

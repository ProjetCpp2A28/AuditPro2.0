#ifndef ALOGIN_H
#define ALOGIN_H

#include <QDialog>

namespace Ui {
class alogin;
}

class alogin : public QDialog
{
    Q_OBJECT

public:
    explicit alogin(QWidget *parent = nullptr);
    ~alogin();

private:
    Ui::alogin *ui;
};

#endif // ALOGIN_H

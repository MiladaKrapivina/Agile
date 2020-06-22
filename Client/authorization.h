#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include "registration.h"
namespace Ui {
class authorization;
}

class authorization : public QDialog
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = nullptr);
    ~authorization();
QString name;
QString pass;
bool chec=false;
bool regi=false;

private slots:
void on_enter_clicked();
void on_reg_clicked();

private:
    Ui::authorization *ui;
    QString data;
};

#endif // AUTHORIZATION_H

#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include <QDebug>
namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT
public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();
    QString name;
    QString pass;
    bool chec;
private slots:
void on_reg_clicked();
private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H

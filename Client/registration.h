#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

QString get_data();

private slots:
void on_reg_clicked();

private:
    Ui::Registration *ui;
    QString data;
};

#endif // REGISTRATION_H

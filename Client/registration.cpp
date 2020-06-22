#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}


void Registration::on_reg_clicked()
{
    name =ui->login->text();
    pass =ui->pass1->text();
    if(!pass.isEmpty()&&!name.isEmpty())
    {
        if(ui->pass1->text()==ui->pass2->text())
        {
            chec=true;
        }else chec=false;

    }else{
        chec=false;
    }
    close();
}

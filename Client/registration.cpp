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

QString Registration::get_data()
{    QString name =ui->login->text();
     QString mail =ui->mail->text();
     QString pass =ui->pass1->text();
    if(!pass.isEmpty()||!name.isEmpty()||!mail.isEmpty()){
    if(ui->pass1->text()==ui->pass2->text()){ 
    data="{ \"method\" : \"1\", \"name\" :\"" +name+ "\", \"email\" : \""+mail+"\", \"password\" : \"" +pass+"\" }";
}else data="no matching";
}
    return data;
}

void Registration::on_reg_clicked()
{
    get_data();
    close();
}

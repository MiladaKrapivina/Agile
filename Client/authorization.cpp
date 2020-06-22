#include "authorization.h"
#include "ui_authorization.h"

authorization::authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
}

authorization::~authorization()
{
    delete ui;
}



void authorization::on_enter_clicked()
{
    name=ui->login->text();
    pass=ui->password->text();
    if(pass.isEmpty()||name.isEmpty()){
    chec=false;
    }else{
          chec=true;
    }
    close();
}

void authorization::on_reg_clicked()
{
    hide();
    Registration* reg= new Registration;
    regi=true;
    reg->setModal(true);
    reg->setWindowTitle("Регистрация");
    reg->exec();
    if(reg->chec){
    name=reg->name;
    pass=reg->pass;
    chec=true;
}
    close();
}





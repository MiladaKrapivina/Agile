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

QString authorization::get_data()
{
    return data;
}

void authorization::on_enter_clicked()
{
    QString name=ui->login->text();
    QString pass=ui->password->text();
    if(!pass.isEmpty()||!name.isEmpty()){
    data="{ \"method\" : \"2\", \"name\" :\"" +name+ "\", \"password\" : \"" +pass+"\" }";
    }
    close();
}

void authorization::on_reg_clicked()
{
    hide();
    Registration* reg= new Registration;
    reg->setModal(true);
    reg->setWindowTitle("Регистрация");
    reg->exec();
    data=reg->get_data();
    close();
}

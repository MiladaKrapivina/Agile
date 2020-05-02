#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void client::con_serv()
{
    socket.connectToHost(QHostAddress("127.0.0.1"), 4242);
    connect(&socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

void client::sockDisc()
{
    socket.deleteLater();
}

void client:: write(QString  data)
{
    QJsonObject text;
    text["title"]=data;
    QJsonArray t;
    t.append(text);
    QJsonDocument doc {{"sgv",t}};
    socket.write(doc.toJson());
    socket.flush();
}

void client::onReadyRead()
{
    Data = socket.readAll();
    qDebug()<<Data;
    qDebug()<<" kkk";
    socket.write(QByteArray("ok !\n"));
}

void MainWindow::on_pushButton_clicked()
{
    client y;
    y.con_serv();
}
void MainWindow::on_pushButton_2_clicked()
{
    client x;
    x.write(ui->lineEdit->text());
}


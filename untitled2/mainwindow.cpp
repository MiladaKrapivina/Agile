#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agile.h"
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


void MainWindow::on_pushButton_clicked()
{
    Agile dosth;
    dosth.connect_to_database();
    dosth.select("task_id","task");
}

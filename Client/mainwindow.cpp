#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cli = new client(QHostAddress("127.0.0.1"), 4242);
    cli->start();
    setstartui();
    connect(ui->projects, &QListView::clicked,this, &MainWindow::updateTSlist);
    connect(ui->prior, &QComboBox::currentTextChanged, this, &MainWindow::priorcolour);
    connect(ui->view, &QListWidget::clicked,this, &MainWindow::change);
    connect(cli, &client::proj,this, &MainWindow::setCurProj);
    connect(cli, &client::tasks,this, &MainWindow::setTasks_to_area);
    connect(alltask, &QListWidget::clicked, this,&MainWindow::setCurTask);
    connect(cli, &client::taskinfo,this, &MainWindow::filltaskW, Qt::DirectConnection);
    connect(ui->Done, &QPushButton::clicked, this,&MainWindow::set_done);
    connect(ui->important,&QPushButton::clicked, this,&MainWindow::set_important);
    connect(ui->update, &QPushButton::clicked, this, &MainWindow::updatePRlist);
    connect(cli, &client::impTask, this, &MainWindow::fillImp);
    connect(cli, &client::notdone, this, &MainWindow::fillNdone);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_authorization_clicked()
{
    authorization* ath=new authorization;
    ath->setWindowTitle("Авторизация");
    ath->setStyleSheet(
                "QPushButton{"
                "background-color: rgb(121, 9, 65);"
                "border-radius: 4px transparent;"
                "border-bottom: 3px transparent;"
                "border-right: 2px transparent;"
                "border-left: 2px transparent;}"
                "colour:rgb(255, 255, 255)"
                "QPushButton:hover{"
                "background-color: rgb(156,31,97);} "
                "QPushButton:pressed  {"
                "background-color: rgb(62,4,35); } "
                "QPushButton{"
                "background-color: rgb(121, 9, 65);"
                "opacity: 0;"
                );

    ath->setModal(true);
    ath->exec();
    QString data=ath->get_data();
    if(!data.isEmpty()){
    QJsonValue value =  QJsonDocument::fromJson(data.toUtf8()).object().value("name");
    ui->authorization->setText(value.toString());
    cli->Cu.name=value.toString();
    cli->write(data);

}
}

void MainWindow::change()
{
    int i=ui->view->currentRow();
    ui->workarea->setCurrentIndex(i);
    switch (i) {
    case 1:{
        setImp_to_Area();
    }break;
    case 2:{
       setnot_done();
    }break;

    }
}

void MainWindow::priorcolour()
{
    if(ui->prior->currentText()=="Нет"){
        ui->prior->setStyleSheet("background-color: rgb(255, 255, 255);");
    } else
        if(ui->prior->currentText()=="Низкий"){
            ui->prior->setStyleSheet("background-color: rgb(12, 210, 36);");
        }else
            if(ui->prior->currentText()=="Средний"){
                ui->prior->setStyleSheet("background-color: rgb(235, 240, 24);");
            }else
                if(ui->prior->currentText()=="Высокий"){
                    ui->prior->setStyleSheet("background-color: rgb(254, 103, 10);");
                } else
                    if(ui->prior->currentText()=="Крайне высокий"){
                        ui->prior->setStyleSheet("background-color: rgb(251, 13, 13);");
                    }

}

void MainWindow::setstartui()
{
    ui->view->addItem("Все задачи");
    ui->view->addItem("Важные");
    ui->view->addItem("Не выполненные");

    ui->view->addItem("Приоритеты");
    ui->view->addItem("Календарь");
    ui->view->addItem("Канбан");

    ui->prior->addItem("Нет");
    ui->prior->addItem("Низкий");
    ui->prior->addItem("Средний");
    ui->prior->addItem("Высокий");
    ui->prior->addItem("Крайне высокий");
    ui->workarea->insertWidget(0,alltask);
    ui->workarea->insertWidget(1,imptask);
    ui->workarea->insertWidget(2, notdone);
    ui->workarea->setCurrentIndex(0);
   // прописать для  workarea
}

void MainWindow::on_addproj_clicked()
{
 QString name=ui->addProjName->text();
 QString owner= cli->Cu.name;
 QString data="{ \"method\" : \"3\", \"name\" :\"" +name+ "\", \"owner\" : \"" +owner+"\" }";
 cli->Cu.proj.append(name);
 setCurProj();
 cli->write(data);
  //  updatePRlist();
}

void MainWindow::on_addtask_clicked()
{
    QString name=ui->addTaskName->text();
    QString owner= cli->Cp.name;
    QDate date = QDate::currentDate();
    QString time= date.toString();
    QString data="{ \"method\" : \"4\", \"name\" :\"" +name+ "\", \"owner\" : \"" +owner+"\" , \"time\" : \"" +time+"\"}";
    cli->write(data);
   // updateTSlist();
}


void MainWindow::setCurProj()
{
    ui->projects->clear();
    ui->projects->addItems(cli->Cu.proj);
    cli->Cu.name=ui->authorization->text();
}

void MainWindow::setCurTask()
{
    cli->Cp.task.clear();
    cli->Ct.name=alltask->currentItem()->text();
    ui->current_task_name->setText(cli->Ct.name);
    QString data="{ \"method\" : \"7\", \"name\" :\"" +cli->Ct.name+ "\",\"project\" :\"" +cli->Cp.name+ "\"  }";
    cli->write(data);
}

void MainWindow::filltaskW()
{
 cli->Cp.name=ui->projects->currentItem()->text();
    switch (cli->Ct.prior) {
    case  0:{
        ui->prior->update();
        ui->prior->setCurrentIndex(0);
    }break;
    case  1:{
        ui->prior->setCurrentIndex(1);
        ui->prior->update();
    }break;
    case  2:{
        ui->prior->setCurrentIndex(2);
        ui->prior->update();
    }break;
    case  3:{
        ui->prior->setCurrentIndex(3);
    }break;

qDebug()<<">>>>>>>>>>>>>>>>>>>>>>";


        if(cli->Ct.importance=="0"){
              ui->important->setText("Не важно");
      }
        else{
                ui->important->setText("Важно");

        }

        if(cli->Ct.done=="0")  {
            ui->Done->setText("Не выполнено");

        }
       else{
            ui->Done->setText("Выполнено");

        }
}

}

void MainWindow::setImp_to_Area()
{
    QString data="{ \"method\" : \"10\", \"name\" :\"" +cli->Cp.name+ "\" }";
    cli->write(data);
}
void MainWindow::updateTSlist()
{
cli->Cp.name=ui->projects->currentItem()->text();
    QString data="{ \"method\" : \"5\", \"name\" :\"" +cli->Cp.name+ "\" }";
    cli->write(data);
}

void MainWindow::setTasks_to_area()
{
  alltask->clear();
  alltask->addItems(cli->Cp.task);
  qDebug()<<"setTasks_to_area()";
}

void MainWindow::updatePRlist()
{
    QString  data="{ \"method\" : \"6\", \"name\" :\"" +cli->Cu.name+ "\"}";
    cli->write(data);
}



// установка тегов
void MainWindow::set_done()
{
    if(ui->Done->text()=="Не выполнено"){
         ui->Done->setText("Выполнено");
    }else{
        ui->Done->setText("Не выполнено");
    }

    QString i;
    if(ui->Done->text()=="Выполнено") {i="1"; }
   else{
         i="0";
    }
  QString data="{ \"method\" : \"8\", \"name\" :\"" +cli->Ct.name+ "\", \"i\" :\"" +i+ "\"}";
    cli->write(data);
    qDebug()<<data;
    updateTSlist();
}

void MainWindow::set_important()
{
    if(ui->important->text()=="Важно"){
         ui->important->setText("Не важно");
    }else{
        ui->important->setText("Важно");
    }
    QString i;
    if(ui->important->isChecked()) {i="1"; }
   else{
         i="0";
    }
    QString data="{ \"method\" : \"9\", \"name\" :\"" +cli->Ct.name+  "\", \"i\" :\"" +i+ "\" }";

    cli->write(data);
    qDebug()<<data;
    updateTSlist();
}



////сейчас

void MainWindow::set_priority()
{
    QString data="{ \"method\" : \"   \", \"name\" :\"" +cli->Ct.name+ "\" }";
    cli->write(data);
}

void MainWindow::setnot_done()
{
    QString data="{ \"method\" : \"11\", \"name\" :\"" +cli->Cp.name+ "\" }";
    cli->write(data);
}


void MainWindow::fillImp()
{
    imptask->clear();
    imptask->addItems(cli->ImpTask);
    qDebug()<<"fillImp()";
}

void MainWindow::fillNdone()
{
    notdone->clear();
    notdone->addItems(cli->NDoneTask);
}


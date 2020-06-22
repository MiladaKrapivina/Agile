#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cli = new client(QHostAddress("127.0.0.1"), 4242);
    cli->start();
    connect(ui->view, &QListWidget::clicked,this, &MainWindow::change);
    connect(cli, &client::updatelist,this, &MainWindow::fillLiast);//  соединяет пришедшее
    connect(cli, &client::updateTaskview,this, &MainWindow::settaskview);
    connect(ui->projects,&QListWidget::clicked,this, &MainWindow::setCurrProj);

    connect(ui->alltasks, &QListWidget::itemClicked,this, &MainWindow::setCurrTask);//все задачи
    connect(ui->imptask, &QListWidget::itemClicked,this, &MainWindow::setCurrTask);//важные задачи

    connect(ui->prW_1, &QListWidget::itemPressed,this, &MainWindow::setCurrTask);
    connect(ui->prW_2, &QListWidget::itemPressed,this, &MainWindow::setCurrTask);
    connect(ui->prW_3, &QListWidget::itemPressed,this, &MainWindow::setCurrTask);
    connect(ui->prW_4, &QListWidget::itemPressed,this, &MainWindow::setCurrTask);
    connect(ui->prW_5, &QListWidget::itemPressed,this, &MainWindow::setCurrTask);

    connect(ui->dnW_1, &QListWidget::itemPressed,this, &MainWindow::setCurrTask);
    connect(ui->dnW_2, &QListWidget::itemPressed,this, &MainWindow::setCurrTask);
    connect(ui->dnW_3, &QListWidget::itemPressed,this, &MainWindow::setCurrTask);

    connect(cli, &client::updateTaskview,this, &MainWindow::settaskview);// представление задачи
    connect(ui->imp, &QCheckBox::clicked,this,&MainWindow::set_imp);

    connect(ui->done, &QComboBox::currentTextChanged, this, &MainWindow::set_done);
    connect(ui->prior, &QComboBox::currentTextChanged, this, &MainWindow::set_prior);

    ui->projects->setContextMenuPolicy(Qt::CustomContextMenu);

    /// контекстное меню
    connect(ui->projects, &QListWidget::customContextMenuRequested, this, &MainWindow::PslotCustomMenuRequested);
    connect(ui->alltasks, &QListWidget::customContextMenuRequested, this, &MainWindow::TslotCustomMenuRequested);

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
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_authorization_clicked()
{
    ath->setWindowTitle("Авторизация");
    ath->setModal(true);
    ath->exec();
    if(ath->chec){
        cli->currentUser.name=ath->name;
        cli->currentUser.pass=ath->pass;
        ui->authorization->setText(cli->currentUser.name);
        QJsonObject obj;
        if(ath->regi){
            obj["meth"]="1";
            // отправляем для create
        }else{
            obj["meth"]="2";
            //  отправляем для check
        }
        obj["name"]=cli->currentUser.name;
        obj["password"]=cli->currentUser.pass;
        QJsonDocument    doc(obj);
        cli->write(doc.toJson());
        qDebug()<<doc.toJson();
    }
}


void MainWindow::change()
{
    // переключение страниц в зависимости от выбранного в view представления
    int i=ui->view->currentRow();
    ui->workarea->setCurrentIndex(i);
    switch (i) {
    case 1:{
        get_sp_lists("important");
    }break;
    case 2:{
        get_sp_lists("done");
    }break;
    case 3:{
        get_sp_lists("priority");
    }break;
    }
}
void MainWindow::fillLiast()
{
    //заполняет виджеты списками
    //список проектов
    ui->projects->clear();
    ui->projects->addItems(cli->currentUser.names);
    //все задачи
    ui->alltasks->clear();
    ui->alltasks->addItems(cli->currentProject.names);
    // списка важных
    ui->imptask->clear();
    ui->imptask->addItems(cli->currentProject.important);
    // списка выполнение
    ui->dnW_1->clear();
    ui->dnW_1->addItems(cli->currentProject.done0);
    ui->dnW_2->clear();
    ui->dnW_2->addItems(cli->currentProject.done1);
    ui->dnW_3->clear();
    ui->dnW_3->addItems(cli->currentProject.done2);
    // списка приоритеты
    ui->prW_1->clear();
    ui->prW_1->addItems(cli->currentProject.pr0);
    ui->prW_2->clear();
    ui->prW_2->addItems(cli->currentProject.pr1);
    ui->prW_3->clear();
    ui->prW_3->addItems(cli->currentProject.pr2);
    ui->prW_4->clear();
    ui->prW_4->addItems(cli->currentProject.pr3);
    ui->prW_5->clear();
    ui->prW_5->addItems(cli->currentProject.pr4);
}

void MainWindow::settaskview()
{
    // отвечает за провильность отображения информации о задаче
    ui->current_task_name->setText(cli->currentTask.name);
    ui->prior->update();
    ui->prior->setCurrentIndex(cli->currentTask.prior);
    ui->done->update();
    ui->done->setCurrentIndex(cli->currentTask.done);
    ui->imp->update();
    if (cli->currentTask.importance==1){
        ui->imp->setCheckState(Qt::Checked);
    } else {
        ui->imp->setCheckState(Qt::Unchecked);
    }
    ui->Comment->setPlainText(cli->currentTask.comment);

}

void MainWindow::get_List(QString param)
{
    // формирует запрос на получение всех проектов или задач
    QJsonObject obj;
    obj["meth"]="3";
    obj["param"]=param;
    if(param=="project"){
        obj["id"]=cli->currentUser.id;
    }else{
        obj["id"]=cli->currentProject.id;
    }
    QJsonDocument    doc(obj);
    cli->write(doc.toJson());
    qDebug()<<doc.toJson();
}

void MainWindow::get_TaskINFO()
{
    //формирует запрос на получение информации и задаче
    QJsonObject obj;
    obj["meth"]="4";
    obj["id"]=cli->currentTask.id;
    QJsonDocument    doc(obj);
    cli->write(doc.toJson());
    qDebug()<<doc.toJson();
}

void MainWindow::setCurrProj()
{
    // меняем значение текущего проекта
    QString temp= ui->projects->currentItem()->text();
    cli->currentProject.name= temp;
    cli->currentProject.id=cli->currentUser.proj.key(temp);
    // запрашиваем список задач
    get_List("task");
}

void MainWindow::setCurrTask()
{
    // узнаем из какого представления была взята задача
    QListWidget* senderPoiter =qobject_cast<QListWidget*>(sender());
    QString temp;
    temp = senderPoiter->currentItem()->text();

    // устанавливаем новую тек задачу
    cli->currentTask.name=temp;
    cli->currentTask.id=cli->currentProject.task.key(temp);
    // запрашиваем информацию о ней
    get_TaskINFO();

}


void MainWindow::create(QString param)
{
    QJsonObject obj;
    obj["meth"]="5";
    obj["param"]=param;
    if(param=="project"){
        obj["id"]=cli->currentUser.id;
        obj["name"]=ui->addProjName->text();
        ui->addProjName->clear();
    }
    else{
        obj["id"]=cli->currentProject.id;
        obj["name"]=ui->addTaskName->text();
        ui->addTaskName->clear();
    }
    QJsonDocument    doc(obj);
    cli->write(doc.toJson());
    qDebug()<<doc.toJson();
    get_List(param);
}

void MainWindow::on_addproj_clicked()
{
    //проверка на не пустое
    if(!ui->addproj->text().isEmpty()){
        create("project");
    }
}

void MainWindow::on_addtask_clicked()
{
    if(!ui->addtask->text().isEmpty()){
        create("task");
    }
}

void MainWindow::set(QString param)
{
    QJsonObject obj;
    obj["meth"]="6";
    obj["param"]=param;
    obj["id"]=cli->currentTask.id;

    if(param=="done"){
        obj["value"]=ui->done->currentIndex();
    }
    else
        if(param=="important"){
            if(ui->imp->isChecked()){
                obj["value"]=1;
            }else {
                obj["value"]=0;
            }
        }
        else
            if(param=="priority")
            {
                obj["value"]=ui->prior->currentIndex();
            }
            else
                if(param=="comm")
                {
                    obj["value"]=ui->Comment->toPlainText();
                    qDebug()<<doc.toJson();
                }
    QJsonDocument    doc(obj);
    cli->write(doc.toJson());
    qDebug()<<doc.toJson();
    fillLiast();
}

void MainWindow::set_imp()
{
    set("important");
}

void MainWindow::set_done()
{
    set("done");
}

void MainWindow::set_prior()
{
    set("priority");
}

void MainWindow::on_SaveText_clicked()
{
    set("comm");
}

void MainWindow::delite(QString param)
{
    QJsonObject obj;
    obj["meth"]="7";
    obj["param"]=param;
    if(param=="user"){
        obj["id"]=cli->currentUser.id;
    }
    else
        if(param=="project"){
            obj["id"]=cli->currentProject.id;
        }
        else
            if(param=="task"){
                obj["id"]=cli->currentTask.id;
            }
    QJsonDocument    doc(obj);
    cli->write(doc.toJson());
    qDebug()<<doc.toJson();
}

void MainWindow::get_sp_lists(QString param)
{
    QJsonObject obj;
    obj["meth"]="9";
    obj["param"]=param;
    obj["id"]=cli->currentProject.id;
    QJsonDocument    doc(obj);
    cli->write(doc.toJson());
}

void MainWindow::PslotCustomMenuRequested(QPoint pos)
{
    QMenu * menup = new QMenu(this);
    QAction * deletepr = new QAction(tr("Удалить проект"), this);
    connect(deletepr, SIGNAL(triggered()), this, SLOT(delpr()));
    menup->addAction(deletepr);
    menup->popup(ui->projects->viewport()->mapToGlobal(pos));
}

void MainWindow::TslotCustomMenuRequested(QPoint pos)
{
    QMenu * menut = new QMenu(this);
    QAction * deletets = new QAction(tr("Удалить задачу"), this);
    connect(deletets, SIGNAL(triggered()), this, SLOT(delts()));
    menut->addAction(deletets);
    menut->popup(ui->alltasks->viewport()->mapToGlobal(pos));
}
void MainWindow::delpr()
{
    delite("project");
    ui->projects->takeItem(ui->projects->currentRow());
}

void MainWindow::delts()
{
    delite("task");
    ui->alltasks->takeItem(ui->alltasks->currentRow());
}

void MainWindow::on_pushButton_clicked()
{
    delite("user");
}

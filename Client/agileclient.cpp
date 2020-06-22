#include "agileclient.h"

client::client(QHostAddress ip, qint32 port, QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
    , _ip (ip)
    , _port(port)
{
    connect(socket, &QTcpSocket::readyRead, this, &client::read);
    connect(socket, &QTcpSocket::connected, this, &client::connected);
    connect(socket, &QTcpSocket::disconnected, this, &client::disconnected);
}

void client::start()
{
    qDebug() << "TRY TO CONNECT";
    socket->connectToHost(_ip, _port);
}

void client::write(QString data)
{
    socket->write(data.toUtf8());
    socket->flush();
}

void client::read()
{
    qDebug() << "READ:";
    QString data = QString::fromUtf8(socket->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj =  doc.object();
    QJsonValue value = doc.object().value("meth");
    qDebug() << doc;
    int meth=value.toString().toUInt();
    switch (meth) {
    case 2: {
        QJsonArray value = doc.object().value("values").toArray();
        // смотрим какой именно список пришел
        if(doc.object().value("param").toString()=="task"){
            currentProject.task.clear();
            for(int i = 0;i != value.size();++i){
                QJsonObject temp=value[i].toObject();
                currentProject.task[temp.value("id").toString().toInt()]=temp.value("name").toString();
            }
            currentProject.names=currentProject.task.values();
            emit updatelist();
            break;
        }
        else{
            //возвращает список  проектов текущего пользователя
            currentUser.proj.clear();
            for(int i = 0;i != value.size();++i){
                QJsonObject temp=value[i].toObject();
                currentUser.proj[temp.value("id").toString().toInt()]=temp.value("name").toString();
            }
            currentUser.names =currentUser.proj.values();
            emit updatelist();
        }
    }
    case 1: {
        // проверяем пользователя при авторизации
        currentUser.id=doc.object().value("id").toInt();
   }
       break;
    case 3: {
        // информация о пользователе
        currentTask.done=doc.object().value("done").toInt();
        currentTask.importance=doc.object().value("important").toInt();
        currentTask.prior=doc.object().value("priority").toInt();
        currentTask.comment=doc.object().value("comm").toString();
        emit updateTaskview();
   }
       break;
    case 4: {
        // списки важных и тд для проекта
        if(doc.object().value("param").toString()=="done"){
            currentProject.done0.clear();
            currentProject.done1.clear();
            currentProject.done2.clear();
            currentProject.done0= doc.object().value("done_0").toVariant().toStringList();
            currentProject.done1= doc.object().value("done_1").toVariant().toStringList();
            currentProject.done2= doc.object().value("done_2").toVariant().toStringList();

            qDebug()<<"*********0"<<  currentProject.done0;
            qDebug()<<"*********1"<<  currentProject.done1;
            qDebug()<<"*********2"<<  currentProject.done2;
            emit updatelist();
            break;
        }
        else
            if(doc.object().value("param").toString()=="important"){
                currentProject.important.clear();
                currentProject.important=doc.object().value("imp").toVariant().toStringList();
                emit updatelist();
            }
            else
                if(doc.object().value("param").toString()=="priority"){
                    currentProject.pr0.clear();
                    currentProject.pr1.clear();
                    currentProject.pr2.clear();
                    currentProject.pr3.clear();
                    currentProject.pr4.clear();
                    currentProject.pr0= doc.object().value("pr0").toVariant().toStringList();
                    currentProject.pr1= doc.object().value("pr1").toVariant().toStringList();
                    currentProject.pr2= doc.object().value("pr2").toVariant().toStringList();
                    currentProject.pr3= doc.object().value("pr3").toVariant().toStringList();
                    currentProject.pr4= doc.object().value("pr4").toVariant().toStringList();

                    emit updatelist();
                }
        break;
    }
}
}

void client::connected()
{
    qDebug() << "CONNECTED!!!";
}

void client::disconnect()
{
    qDebug() << "DISCONNECTED";
}

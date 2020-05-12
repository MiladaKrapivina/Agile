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
    qDebug() << "WRITE" << data;
}

void client::read()
{
    qDebug() << "READ";
    QString data = QString::fromUtf8(socket->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj =  doc.object();
    QJsonValue value = doc.object().value("method");
    int meth=value.toString().toInt();
    switch (meth) {
    case 1: {
        // возвращается список проектов при идентификации пользователя
        QList <QString> sd= doc.object().value("project").toVariant().toStringList();
        Cu.proj.clear();
        Cu.proj =sd;
        emit proj();
    }
        break;
    case 2: {
        //возвращает список задач текущего проекта
        QJsonObject TASKS=doc.object();
        QList <QString> sd= doc.object().value("tasks").toVariant().toStringList();
        qDebug()<<"sd[1]";
        Cp.task =sd;
        emit tasks();
    }
        break;
    case 3: {
        QJsonObject task=doc.object();

        Ct.done=task.value("done").toString();
        Ct.dtime =task.value("deadline").toString();
        Ct.prior=task.value("priority").toInt();
        Ct.importance=task.value("important").toString();
        qDebug()<< Ct.done<<"_____"<<Ct.dtime<<"_____"<<Ct.prior<<"_____"<<Ct.importance<<"_____";
        emit taskinfo();
    }break;
    case 4: {
        QList <QString> sd= doc.object().value("tasks").toVariant().toStringList();
        qDebug()<<"Important]";
        ImpTask =sd;
        emit impTask();
    }break;
    case 5: {
        QList <QString> sd= doc.object().value("tasks").toVariant().toStringList();
        qDebug()<<"Not done";
       NDoneTask =sd;
        emit notdone();
    }break;
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

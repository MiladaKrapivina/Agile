#include "AgileServer.h"

socket_comp::socket_comp(qint32 socket_id, QObject *parent)
    : QThread(parent)
    , _socket_id(socket_id)
{
}

void socket_comp::write(QString data)
{
    qDebug() << "WRITE";
     qDebug() << data;
    _soc->write(data.toUtf8());
}

void socket_comp::read_data()
{
    qDebug() << "READ";
    QString data = QString::fromUtf8(_soc->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj =  doc.object();
    qDebug()<<"Prishl0::::::::::::::";
    qDebug()<<obj;
    QJsonValue value = doc.object().value("meth");
    int meth=value.toString().toUInt();
    qDebug()<<"_____"<<meth;
    switch (meth) {
    case 1:{
         dometh.createUser(obj.value("name").toString(),
                          obj.value("password").toString() );
         write(dometh.returndata());
    }break;
    case 2:{
         dometh.check_user(obj.value("name").toString(),
                           obj.value("password").toString() );
         write(dometh.returndata());
    }break;

    case 3:{
         dometh.get_all(obj.value("param").toString(),
                        obj.value("id").toInt());
         write(dometh.returndata());
    }break;
    case 4:{
         dometh.get_task_info( obj.value("id").toInt());
         write(dometh.returndata());
    }break;
    case 5:{
         dometh.create(obj.value("param").toString(),
                       obj.value("name").toString(),
                       obj.value("id").toInt());

    }break;
    case 6:{
        QString temp;
        if(obj.value("value").toString().isEmpty()){
            int i=obj.value("value").toInt();
             temp=QString::number(i);
        }else{
        temp=obj.value("value").toString();
        }
         dometh.set_(obj.value("param").toString(),
                     obj.value("id").toInt(),
                    temp);

    }break;
    case 7:{
        dometh.delete_(obj.value("param").toString(),
                       obj.value("id").toInt());
    }break;
    case 9:{
        dometh.get_tasklist(obj.value("param").toString(),
                            obj.value("id").toInt());
        write(dometh.returndata());
    }break;
}
}
void socket_comp::run()
{
_soc = new QTcpSocket();
    if (_soc->setSocketDescriptor(_socket_id))
    {
        connect(_soc, &QTcpSocket::readyRead, this, &socket_comp::read_data, Qt::DirectConnection);
        connect(_soc, &QTcpSocket::disconnected, this, &socket_comp::quit);
        connect(_soc, &QTcpSocket::disconnected, _soc, &QTcpSocket::deleteLater);
        qDebug() << "Connection started";
        exec();
        qDebug() << "Connection ends";
    } else qDebug() << "Something wrong";
}

server_comp::server_comp(QObject *parent)
    : QObject(parent)
    , _server(new QTcpServer(this))
{
    connect(_server, &QTcpServer::newConnection, this, &server_comp::on_new_connection);
}

void server_comp::on_new_connection()
{
    qDebug() << "Get new connection";
    QTcpSocket* soc = _server->nextPendingConnection();
    qint32 id = soc->socketDescriptor();
    socket_comp* socket_th = new socket_comp(id);
    connect(socket_th, &socket_comp::finished, socket_th, &socket_comp::deleteLater);
    socket_th->start();
}

void server_comp::start(qint32 port)
{
    _server->listen(QHostAddress::Any, port);
    qDebug() << "Server start at port " << port;
}

#include "AgileServer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
socket_comp::socket_comp(qint32 socket_id, QObject *parent)
    : QThread(parent)
    , _socket_id(socket_id)
{
}

void socket_comp::write(QString data)
{
    qDebug() << "\nWRITE";
    _soc->write(data.toUtf8());
}

void socket_comp::read_data()
{

    qDebug() << "\nREAD";
    QString data = QString::fromUtf8(_soc->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj =  doc.object();
     QJsonValue value = doc.object().value("method");
     int meth=value.toString().toInt();
      qDebug()<<data;
      qDebug()<<obj;
     qDebug()<<"----"<<meth<<"----";
    switch (meth) {
    case 1: {
         user twi;
        twi.create_user(  obj.value("name").toString(),
                          obj.value("email").toString(),
                          obj.value("password").toString()   );
    }
        break;
    case 2: {
         user twi;
        twi.check_user(  obj.value("name").toString(),
                          obj.value("password").toString()   );
        write(twi.returndata());
        qDebug() <<twi.returndata() ;
    }
        break;
    case 3: {
        project pr;
        pr.create_project(  obj.value("name").toString(),
                            obj.value("owner").toString()   );
    }
        break;
    case 4: {
        task ts;
        ts.create_task(obj.value("name").toString(),
                       obj.value("owner").toString(),
                       obj.value("time").toString()   );
    }
        break;
    case 5: {
       project pr;
       pr.get_all_tasks(obj.value("name").toString());
       write(pr.returndata());
       qDebug() <<pr.returndata() ;
    }
        break;

    case 6: {
        user twi;
       twi.get_all_project(obj.value("name").toString());
       write(twi.returndata());
       qDebug() <<twi.returndata();
    } break;

    case 7: {
        task ts;
      ts.get_task_info(obj.value("name").toString(),obj.value("project").toString());
       write(ts.returndata());
       qDebug() <<ts.returndata();
    } break;

    case 8: {
       task ts;
       qDebug() << "Попытка создать метку";
       ts.set_done(obj.value("name").toString(),obj.value("i").toString());
    } break;
    case 9: {
       task ts;
       ts.set_important(obj.value("name").toString(),obj.value("i").toInt());
    } break;

    case 10: {
        project pr;
        pr.get_imp_tasks(obj.value("name").toString());
        write(pr.returndata());
        qDebug() <<pr.returndata();
    } break;
    case 11: {
        project pr;
        pr.get_done_tasks(obj.value("name").toString());
        write(pr.returndata());
        qDebug() <<pr.returndata();
    } break;

    default:    qDebug() << "NO__Sorry";
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

#include "AgileServer.h"

void AServer::startServer()
{
    if (this->listen(QHostAddress::Any,5555))
    {
        qDebug()<<"Listening";
    }
    else
    {
        qDebug()<<"Not listening";
    }
   connect(this, &AServer::newConnection, this, &AServer:: incomingConnection);
}

void AServer::incomingConnection()
{
    socket= this->nextPendingConnection();

    //socket->setSocketDescriptor(socketDescriptor);

        connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
        connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    qDebug()<<" Client connected";

    socket->write("You are connect");
    qDebug()<<"Send client connect status - YES";
}
void AServer::sockReady()
{

}

void AServer::sockDisc()
{
    qDebug()<<"Disconnect";
    socket->deleteLater();
}

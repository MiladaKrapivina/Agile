#include "AgileServer.h"

void AServer::startServer()
{
    server.listen(QHostAddress::Any,4242);
    connect(&server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
    qDebug()<<"Listening";
}

void AServer::onNewConnection()
{
    QTcpSocket *clientSocket = server.nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));
     sockets.push_back(clientSocket);
     for (QTcpSocket* socket : sockets) {
         socket->write(QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
     qDebug()<<QByteArray::fromStdString(clientSocket->peerAddress().toString().toStdString()) + " connected to server !\n";
     }
}

void AServer::sockDisc()
{
    qDebug()<<"Disconnect";
    socket->deleteLater();
}

// работа с Json
void AServer::onReadyRead()
{
    QTcpSocket* client = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = client->readAll();
    for (QTcpSocket* socket : sockets) {
        if (socket != client)
            socket->write(QByteArray::fromStdString(client->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
    }

 QByteArray data = socket->readAll();
 qDebug()<< data;

}
void AServer::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        sockets.removeOne(sender);
    }
}

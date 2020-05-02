#ifndef AGILESERVER_H
#define AGILESERVER_H

#include<QTcpServer>
#include<QTcpSocket>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

class AServer: public QTcpServer
{
    Q_OBJECT

    QByteArray Data;
    QList<QTcpSocket*> sockets;
    QTcpServer  server;
    QTcpSocket* socket;
protected:
    QSqlQuery *query;
    QSqlDatabase db;
public:
    void connect_to_database();
    void startServer();

public slots:
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onNewConnection();
    void onReadyRead();
    void sockDisc();
};




#endif // AGILESERVER_H

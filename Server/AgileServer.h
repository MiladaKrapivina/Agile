#ifndef AGILESERVER_H
#define AGILESERVER_H

#include<QTcpServer>
#include<QTcpSocket>
class AServer: public QTcpServer
{
    Q_OBJECT
    public:
    AServer();
    ~AServer();
    QTcpSocket* socket;
    QByteArray Data;

public slots:
    void startServer();
    void incomingConnection(int socketDescriptor);
//  void sockReady();
    void sockDisc();
};


/*    myserver();



#endif // AGILESERVER_H

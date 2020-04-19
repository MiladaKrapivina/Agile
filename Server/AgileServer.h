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

    public:
  // AServer();
  //  ~AServer();
    QTcpSocket* socket;
    QByteArray Data;
    QSqlDatabase db;
    QSqlQuery *query;

       void connect_to_database(); // поместить в сервер

public slots:
    void startServer();
    void incomingConnection(int socketDescriptor);
//  void sockReady();
    void sockDisc();
};


/*    myserver();

*/

#endif // AGILESERVER_H

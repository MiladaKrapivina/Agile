#ifndef AGILESERVER_H
#define AGILESERVER_H

#include "Header.h"
#include "agile.h"
class socket_comp : public QThread
{
    Q_OBJECT
public:
    explicit socket_comp(qint32 socket_id, QObject *parent = nullptr);

public slots:
    void write(QString data);
    void read_data();

private:
    void run() override;
    const int _socket_id;
    QTcpSocket* _soc;
    DateBase dometh;
};

class server_comp : public QObject
{
    Q_OBJECT
public:
    explicit server_comp(QObject* parent = nullptr);

public slots:
    void on_new_connection();
    void start(qint32 port);

private:
    QTcpServer* _server;

};



#endif // AGILESERVER_H

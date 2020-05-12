#ifndef AGILECLIENT_H
#define AGILECLIENT_H

#include "Header.h"
struct _task{
  QString name;
  QString dtime;
  QString done;
  QString importance;
  int prior;
  QList <QString> under;
};

struct _project{
    QString name;
    QList <QString> task;
};

struct _user{
    QString name;
    QList <QString> proj;
    qint32 size=proj.size();
};


class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QHostAddress ip, qint32 port, QObject *parent = nullptr);

   _user Cu;
  _project Cp;
  _task Ct;
   QList <QString> ImpTask;
   QList <QString> NDoneTask;

signals:
    void proj();
    void tasks();
    void taskinfo();
    void impTask();
    void notdone();
public slots:
    void start();
    void write(QString data);

private slots:
    void read();
    void connected();
    void disconnect();

private:
    QTcpSocket* socket;
    QHostAddress _ip;
    qint32 _port;

signals:
    void disconnected();

};

#endif // AGILECLIENT_H
